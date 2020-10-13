/************************************************
* 文件描述: fdisk线程，用于执行sudo fdisk -l命令，读取
*          系统硬盘信息。
* 待完善:
* 待优化:
* 修改日期：2020.10.12
* 修改内容：
*   创建  HZH
*************************************************/
#include "fdisk_thread.h"

/************************************************
* 函数名称：FdiskThread
* 功能描述：构造函数
* 输入参数：
* 输出参数：
* 修改日期：2020.10.12
* 修改内容：
*   创建  HZH
*
*************************************************/
FdiskThread::FdiskThread(QObject *parent) : QObject(parent)
{

}

/************************************************
* 函数名称：~FdiskThread()
* 功能描述：析构函数
* 输入参数：
* 输出参数：
* 修改日期：2020.10.12
* 修改内容：
*   创建  HZH
*
*************************************************/
FdiskThread::~FdiskThread()
{
    cmdFdiskBash->deleteLater(); //这句加上会导致只关闭主界面，授权窗口一直不关闭，去掉影响未知。
    //cmdFdiskBash->close();           //销毁时结束外部程序

}

/************************************************
* 函数名称：startFdisk()
* 功能描述：执行pkexec sudo fdisk -l命令，查看硬盘信息，
*         通过pkexec提权弹出授权窗口，并获取标准输出，查
*         看回显内容，根据回显内容确定硬盘信息。
* 输入参数：QString fdiskCmd
* 输出参数：
* 修改日期：2020.10.12
* 修改内容：
*   创建  HZH
*
*************************************************/
void FdiskThread::startFdisk(QString fdiskCmd)
{
    qDebug() << "startFdisk!";

    cmdFdiskBash = new QProcess();   //创建QProcess对象并连接信号与槽

    connect(cmdFdiskBash,&QProcess::readyReadStandardOutput,this,&FdiskThread::readcmdFdiskBashInfo);
    connect(cmdFdiskBash,&QProcess::readyReadStandardError,this,&FdiskThread::readcmdFdiskBashErrorInfo);

    cmdFdiskBash->start("bash");

    cmdFdiskBash->write(fdiskCmd.toLocal8Bit() + '\n');

    cmdFdiskBash->waitForStarted();

}

/************************************************
* 函数名称：readcmdFdiskBashErrorInfo
* 功能描述：读取标准错误输出，若有错误输出，向主线程发送信
*         号，要求关闭程序。
* 输入参数：
* 输出参数：
* 修改日期：2020.10.12
* 修改内容：
*   创建  HZH
*
*************************************************/
void FdiskThread::readcmdFdiskBashErrorInfo()
{
    QByteArray cmdStdOut = cmdFdiskBash->readAllStandardError();

    qDebug() << "授权窗口被关闭";
    if(cmdStdOut.count("Error"))
    {
        qDebug() << "向主线程发送信号，关闭程序";
        emit passwordNoInput();
    }

}

/************************************************
* 函数名称：readcmdFdiskBashInfo()
* 功能描述：读取标准输出，调用处理函数startPreHandle进行
*          文字处理，提取相关信息。
* 输出参数：
* 修改日期：2020.10.12
* 修改内容：
*   创建  HZH
*
*************************************************/
void FdiskThread::readcmdFdiskBashInfo()
{
    QByteArray cmdStdOut = cmdFdiskBash->readAllStandardOutput();
    if(!cmdStdOut.isEmpty() ){
        qDebug() << cmdStdOut;
        //emit setInfo(QString::fromLocal8Bit(cmdStdOut));   //向主线程发送信息，暂无处显示，注释掉。
        startPreHandle(cmdStdOut);
    }
}

/************************************************
* 函数名称：startPreHandle
* 功能描述：处理fdisk -l命令的返回内容
* 输出参数：无
* 修改日期：2020.10.12
* 修改内容：
*   创建  HZH
*
*************************************************/
void FdiskThread::startPreHandle(QByteArray cmdOutFromFdisk)
{
    qDebug() << "startPreHandle!";
    //入参检查
    if(cmdOutFromFdisk.isEmpty())
    {
        //TODO:emit setInfo("无硬盘介质！");
    }
    else
    {
        //sudo fdisk -l的固定返回信息，最后一列为Linux 文件系统或EFI 文件系统为系统相关目录，home目录无影响，不提取。
        if(cmdOutFromFdisk.count("Linux 文件系统") || cmdOutFromFdisk.count("Linux filesystem") ||\
           cmdOutFromFdisk.count("EFI 文件系统") || cmdOutFromFdisk.count("EFI filesystem"))
        {
            qDebug() << "有Linux文件系统。";
            numOfLinuxPartion = 0;
            //优麒麟默认安装时会划分/boot/efi分区
            QStringList list = (QString::fromLocal8Bit(cmdOutFromFdisk)).split("\n");     //把输出内容按行分割成元素添加至list

            for(QString& si : list)                        //遍历list中的各行
            {
                QStringList strlist = si.split(" ");       //遍历各行str中被空格隔开的字段
                int size = strlist.size();                 //各str中被空格隔开字段个数
                //字段少于2时肯定不是分区目录相关信息列，下面使用时读取了容器中第2个成员，会导致越界，所以加以排除。
                if (size < 2)
                {
                    continue;
                }


                if(((("filesystem" == QString::fromLocal8Bit(strlist.at(size - 1).toLocal8Bit().data()))\
                    || ("文件系统" == QString::fromLocal8Bit(strlist.at(size - 1).toLocal8Bit().data())))\
                        && ("Linux" == QString::fromLocal8Bit(strlist.at(size - 2).toLocal8Bit().data())))\
                    ||  ("EFI" == QString::fromLocal8Bit(strlist.at(size - 2).toLocal8Bit().data())))
                {
                    //TODO此处可以增加限定，已有的分区不要再加入
                    allDeviceInfoStr << strlist.at(0).toLocal8Bit().data();   //将有用的信息装入string list中

                }
            }
        }
        listOfDevice = allDeviceInfoStr;//私有成员赋值，方便向外传递。

        numOfLinuxPartion = listOfDevice.size();//计算列表中分区的数量

        qDebug() << "Linux系统文件分区个数为:";
        qDebug() << QString::number(numOfLinuxPartion);

        //结束准备界面，进入修复开始界面，命令执行过程很快，增加4秒延时，防止页面一闪而过，给用户造成疑惑。
        QTimer::singleShot(4000, [=](){
            emit mainWindowChangePage();//向主窗口发送信号，执行下一流程
        });

        qDebug() << "提取硬盘信息流程结束！";

    }
}
