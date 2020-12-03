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
FdiskThread::FdiskThread(bool hasPwd, QString userPwd,QObject *parent) : QObject(parent)
{
    hasPassWord = hasPwd;
    userPassWord = userPwd;
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
    if(NULL != cmdFdiskBash)
    {
        cmdFdiskBash->close(); //这句加上会导致只关闭主界面，授权窗口一直不关闭，去掉影响未知。
        delete cmdFdiskBash;
    }
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
    qDebug() << "开始用fdisk命令获取信息" << "startFdisk!";

    cmdFdiskBash = new QProcess();   //创建QProcess对象并连接信号与槽

    connect(cmdFdiskBash,&QProcess::readyReadStandardOutput,this,&FdiskThread::readcmdFdiskBashInfo);
    connect(cmdFdiskBash,&QProcess::readyReadStandardError,this,&FdiskThread::readcmdFdiskBashErrorInfo);

    cmdFdiskBash->start("bash");

    cmdFdiskBash->write(fdiskCmd.toLocal8Bit() + '\n');
    if(hasPassWord)
    {
        qDebug() << "有密码！";
        cmdFdiskBash->write(userPassWord.toLocal8Bit() + '\n');
    }
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
    if(!cmdStdOut.isEmpty() && (cmdStdOut.contains("[sudo]")))
    {
        qDebug() << QString::fromLocal8Bit(cmdStdOut);
    }
    else
    {
        qDebug() << "读取硬盘过程出现问题！";
        qDebug() << QString::fromLocal8Bit(cmdStdOut);
//        cmdFdiskBash->kill();
//        emit failAndReturn();
    }
}

/************************************************
* 函数名称：readcmdFdiskBashInfo()
* 功能描述：读取标准输出，调用处理函数startPreHandle进行
*          文字处理，提取相关信息。
* 输出参数：
* 修改日期：2020.11.07
* 修改内容：
*   创建  HZH
*   修改  完善打印信息
*
*************************************************/
void FdiskThread::readcmdFdiskBashInfo()
{
    QString tempLine;

    fdiskTimer->stop();
    QTimer::singleShot(1000, this, [=](){
        qDebug() << "一秒后再处理文本！";
        startPreHandle(fdiskCmdStdOut);
        cmdFdiskBash->kill();
    });

    while((tempLine = cmdFdiskBash->readLine()) != "")
    {
        qDebug() << "原始返回内容：" << tempLine;
        tempLine = tempLine.left(tempLine.size() - 1);
        if((tempLine.count("Linux 文件系统") || tempLine.count("Linux filesystem") ||\
           tempLine.count("EFI 文件系统") || tempLine.count("EFI filesystem")\
                || tempLine.count("Linux") || tempLine.count("EFI"))\
                && (0 == tempLine.count("swap") && 0 == tempLine.count("SWAP") && 0 == tempLine.count("Swap")))
        {
            qDebug() << tempLine;
            fdiskCmdStdOut << tempLine;
        }
    }
    if(!fdiskCmdStdOut.isEmpty() && !(fdiskCmdStdOut.contains("[sudo]")))
    {

        fdiskTimer->start();
        qDebug() << "开始计时！";
    }
}

/************************************************
* 函数名称：startPreHandle
* 功能描述：处理fdisk -l命令的返回内容
* 输出参数：无
* 修改日期：2020.11.07
* 修改内容：
*   创建  HZH
*   兼容V10.1，其fdisk命令回显内容无系统文件字样，导致失效
*
*************************************************/
void FdiskThread::startPreHandle(QStringList cmdOutFromFdisk)
{
    qDebug() << "开始处理fdisk返回信息";
    //入参检查
    if(cmdOutFromFdisk.isEmpty())
    {
        //TODO:emit setInfo("无硬盘介质！");
        qDebug() << "！！！！！！！！！！";
        qDebug() << "错误：未能读取硬盘！";
        qDebug() << "！！！！！！！！！！";
        emit failAndReturn();
        return;
    }
    else
    {
        qDebug() << "有Linux文件系统。";
        numOfLinuxPartion = 0;
        //优麒麟默认安装时会划分/boot/efi分区
        QStringList list = cmdOutFromFdisk;//(cmdOutFromFdisk.split("\n");     //把输出内容按行分割成元素添加至list
        qDebug() << "list中有" << list.size() << "行";
        for(QString& si : list)                        //遍历list中的各行
        {
            qDebug() << si;
            QStringList strlist = si.split(" ");       //遍历各行str中被空格隔开的字段
            int size = strlist.size();                 //各str中被空格隔开字段个数
            //字段少于2时肯定不是分区目录相关信息列，下面使用时读取了容器中第2个成员，会导致越界，所以加以排除。
            if (size < 2)
            {
                continue;
            }
            qDebug() << QString::fromLocal8Bit(strlist.at(size - 1).toLocal8Bit().data());
            qDebug() << QString::fromLocal8Bit(strlist.at(size - 2).toLocal8Bit().data());
            //10.1
            if(("Linux" == QString::fromLocal8Bit(strlist.at(size - 1).toLocal8Bit().data()))\
                    || ("EFI" == QString::fromLocal8Bit(strlist.at(size - 1).toLocal8Bit().data())))
            {
                //TODO此处可以增加限定，已有的分区不要再加入
                if(!allDeviceInfoStr.count(strlist.at(0).toLocal8Bit().data()))
                {
                    allDeviceInfoStr << strlist.at(0).toLocal8Bit().data();   //将有用的信息装入string list中
                }

                continue;
                //QString deviceLocation = QString::fromLocal8Bit(strlist.at(0).toLocal8Bit().data()) ;
                //QString deviceType = QString::fromLocal8Bit(strlist.at(size - 1).toLocal8Bit().data());
                //qDebug() << deviceLocation << "为" << deviceType << "类型分区";
            }
            //2004
            else if(((("filesystem" == QString::fromLocal8Bit(strlist.at(size - 1).toLocal8Bit().data()))\
                      || ("文件系统" == QString::fromLocal8Bit(strlist.at(size - 1).toLocal8Bit().data())))\
                     && ("Linux" == QString::fromLocal8Bit(strlist.at(size - 2).toLocal8Bit().data())))\
                    ||  ("EFI" == QString::fromLocal8Bit(strlist.at(size - 2).toLocal8Bit().data())))
            {
                //TODO此处可以增加限定，已有的分区不要再加入
                if(!allDeviceInfoStr.count(strlist.at(0).toLocal8Bit().data()))
                {
                    allDeviceInfoStr << strlist.at(0).toLocal8Bit().data();   //将有用的信息装入string list中
                }
                continue;
                //QString deviceLocation = QString::fromLocal8Bit(strlist.at(0).toLocal8Bit().data()) ;
                //QString deviceType = QString::fromLocal8Bit(strlist.at(size - 1).toLocal8Bit().data());
                //qDebug() << deviceLocation << "为" << deviceType << "类型分区";
            }

        }
        listOfDevice = allDeviceInfoStr;//私有成员赋值，方便向外传递。

        numOfLinuxPartion = listOfDevice.size();//计算列表中分区的数量

        qDebug() << "Linux系统文件分区个数为:" << QString::number(numOfLinuxPartion) << "个";

        if(0 == numOfLinuxPartion)
        {
            qDebug() << "硬盘中没有Linux系统文件分区！";
            emit failAndReturn();
            return;
        }

        //结束准备界面，进入修复开始界面，命令执行过程很快，增加4秒延时，防止页面一闪而过，给用户造成疑惑。
        QTimer::singleShot(4000, [=](){
            emit changeToMainPage();//向主窗口发送信号，执行下一流程
        });

        qDebug() << "从fdisk命令回显中提取硬盘信息流程结束！";

    }
}
