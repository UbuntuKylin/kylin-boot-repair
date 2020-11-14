/************************************************
* 文件描述: 装载硬盘线程，将找到的根分区挂载，以便读取/boot
*          /efi，/root等分区路径。
* 待完善:
* 待优化:
* 修改日期：2020.10.12
* 修改内容：
*   创建  HZH
*************************************************/
#include "partion_device.h"

/************************************************
* 函数名称：PartionDevice
* 功能描述：构造函数，根据输入的硬盘分区路径字符串，初始化
*         相应命令的字符串。
* 输入参数：QString partionDeviceName, QObject *parent
* 输出参数：
* 修改日期：2020.10.12
* 修改内容：
*   创建  HZH
*
*************************************************/
PartionDevice::PartionDevice(QString partionDeviceName, QObject *parent) : QObject(parent)
{
    DeviceName = partionDeviceName;
    qDebug() << "当前分区硬盘名称为：" << DeviceName;

    isRootPartion = false;
    bootIsSeparate    = false;
    isBootPartion = false;
    isEfiParion   = false;

    //belongToRootDeviceName = "";
    selfBootDeviceName     = "";
    selfEfiDeviceName      = "";

    QString tempStr = partionDeviceName;
    cmdUmountStr = "sudo -S umount "      + tempStr;
    cmdMkdirStr  = "sudo -S mkdir /media" + tempStr.remove(0,4);
    cmdMountStr  = "sudo -S mount /dev"   + tempStr + " /media" + tempStr;
    fstabPath    = "/media"               + tempStr + "/etc/fstab";

    realRootMountStr = "";
    realBootMountStr = "";
    realEfiMountStr  = "";

//    connect(this,&PartionDevice::cmdInfo,cmdUmountBash,&CmdBash::cmdInfo,);
//    cmdMount = new QProcess();   //创建QProcess对象并连接信号与槽
//    cmdMount->start("bash");
//    cmdMount->waitForStarted();
}

/************************************************
* 函数名称：PartionDevice
* 功能描述：析构函数
* 输入参数：
* 输出参数：
* 修改日期：2020.10.12
* 修改内容：
*   创建  HZH
*
*************************************************/
PartionDevice::~PartionDevice()
{
    cmdUmountBash->deleteLater();           //拆卸硬盘线程类
    cmdMkdirBash->deleteLater();            //创建文件夹线程类
    cmdMountBash->deleteLater();            //挂载硬盘线程类
}

/************************************************
* 函数名称：prepareOfFirstMount
* 功能描述：硬盘挂载函数，为防止已挂载，先进行拆卸。并创建
*         对应的文件夹，对分区进行挂载。
* 输入参数：QString partionDeviceName, QObject *parent
* 输出参数：无
* 修改日期：2020.10.12
* 修改内容：
*   创建  HZH
*
*************************************************/
void PartionDevice::prepareOfFirstMount()
{
    //先卸载硬盘，以防被加载
    qDebug() << "执行拆卸硬盘指令：" << cmdUmountStr;
    cmdUmountBash = new CmdBash(cmdUmountStr,this);
    connect(cmdUmountBash,&CmdBash::cmdInfo,this,&PartionDevice::cmdInfo);
    cmdUmountBash->cmdExecute();

    //创建对应的文件夹
    qDebug() << "执行创建文件夹指令：" << cmdMkdirStr;
    cmdMkdirBash = new CmdBash(cmdMkdirStr,this);
    connect(cmdMkdirBash,&CmdBash::cmdInfo,this,&PartionDevice::cmdInfo);
    qDebug() << "new cmdBash" ;
    cmdMkdirBash->cmdExecute();

    qDebug() << "cmdExecute()" ;
    qDebug() << cmdMkdirBash->currentBash->readAll();

    qDebug() << "获取线程end!";

    //挂载对应的硬盘
    qDebug() << "执行挂载硬盘指令：" << cmdMountStr;
    cmdMountBash = new CmdBash(cmdMountStr,this);
    connect(cmdMountBash,&CmdBash::cmdInfo,this,&PartionDevice::cmdInfo);
    cmdMountBash->cmdExecute();



//    cmdMount->write(cmdMountStr.toLocal8Bit() + '\n');

//    cmdMount->waitForFinished();
//    qDebug() << cmdMountStr;


//    qDebug() << "等待5s再进行检查！" ;
//    QEventLoop eventloop;
//    QTimer::singleShot(1000, &eventloop,SLOT(quit()));
//    eventloop.exec();


//    qDebug() << "~~~~~~~~~~~~~~~~~~";
//    qDebug() << "创建文件夹指令结果检查";
//    qDebug() << "~~~~~~~~~~~~~~~~~~";

//    QString filePathCmdString = DeviceName;
//    QString temp1 = filePathCmdString;
//    QString temp2 = filePathCmdString;
//    temp2 = "/tmp/" + temp1.remove(0,5);

//    qDebug() << "检查" << temp2 << "是否存在";
//    QDir *dir = new QDir(temp2);

//    int mkdirNum = 0;
//    do
//    {
//        mkdirNum++;
//        if(!dir->exists())
//        {
//            qDebug() << temp2 << "文件夹不存在";
//            //创建对应的文件夹
//            QEventLoop eventloop2;
//            QTimer::singleShot(1000, &eventloop2,SLOT(quit()));
//            eventloop2.exec();
//            qDebug() << "等待2s再进行创建！" ;
//            qDebug() << "执行创建文件夹指令：" << cmdMkdirStr;
//            QDir dir2("/");
//            if(dir2.exists())
//            {
//                dir2.cd("./tmp");
//                qDebug() << "当前路径" << dir2.dirName();
//                qDebug() << "使用QDir创建" << temp2;
//                if(dir2.mkdir(temp2))
//                {
//                    qDebug() << "QDir创建！" << temp2 << "成功" ;
//                    qDebug() << "执行挂载硬盘指令：" << cmdMountStr;
//                    cmdMount->write(cmdMountStr.toLocal8Bit() + '\n');

//                    cmdMount->waitForFinished();
//                }
//                else
//                {
//                   qDebug() << "等待2s再进行创建！" << temp2 << "失败"  ;
//                }

//            }
//            fileCreatSuccess = false;
//        }
//        else
//        {
//            qDebug() << "文件夹" << temp2 << "存在";
//            qDebug() << "继续执行下一步";
//            fileCreatSuccess = true;
//            break;
//        }
//    }
//    while((false == fileCreatSuccess) && (mkdirNum < 5));

//    int mountNum = 0;
//    do
//    {
//        mountNum++;
//        if(dir->isEmpty())
//        {
//            qDebug() << temp1 << "挂载失败！";
//            //创建对应的文件夹
//            QEventLoop eventloop4;
//            QTimer::singleShot(1000, &eventloop4,SLOT(quit()));
//            eventloop4.exec();
//            qDebug() << "等待2s再进行挂载！" ;
//            qDebug() << "执行挂载硬盘指令：" << cmdMountStr;
//            cmdMountBash = new CmdBash(cmdMountStr,this);
//            connect(cmdMountBash,&CmdBash::cmdInfo,this,&PartionDevice::cmdInfo);
//            cmdMountBash->cmdExecute();
//            devMountSuccess = false;
//        }
//        else
//        {
//            qDebug() << "分区" << temp2 << "挂载成功";
//            qDebug() << "继续执行下一步";
//            devMountSuccess = true;
//            break;
//        }
//    }
//    while((false == devMountSuccess) && (mountNum < 5));
//    if((false == devMountSuccess))
//    {
//        qDebug() << "！！！！！！！！！！！";
//        qDebug() << temp2 << "挂载失败！回主线程";
//        qDebug() << "！！！！！！！！！！！";
//        emit failAndReturn();
//        return;
//    }



//    QEventLoop eventloop3;
//    QTimer::singleShot(2000, &eventloop3,SLOT(quit()));
//    eventloop3.exec();
//    qDebug() << "挂载后等待2s再进行检查！" ;
//    int mountNum = 0;
//    do
//    {
//        mountNum++;
//        if(dir->isEmpty())
//        {
//            qDebug() << temp2 << "挂载失败！";
//            //创建对应的文件夹
//            QEventLoop eventloop4;
//            QTimer::singleShot(2000, &eventloop4,SLOT(quit()));
//            eventloop4.exec();
//            qDebug() << "等待2s再进行挂载！" ;
//            qDebug() << "执行挂载硬盘指令：" << cmdMountStr;
//            cmdMountBash = new CmdBash(cmdMountStr,this);
//            connect(cmdMountBash,&CmdBash::cmdInfo,this,&PartionDevice::cmdInfo);
//            cmdMountBash->cmdExecute();
//            devMountSuccess = false;
//        }
//        else
//        {
//            qDebug() << "分区" << temp2 << "挂载成功";
//            qDebug() << "继续执行下一步";
//            devMountSuccess = true;
//            break;
//        }
//    }
//    while((false == devMountSuccess) && (mountNum < 5));

//    if((false == devMountSuccess))
//    {
//        qDebug() << "！！！！！！！！！！！";
//        qDebug() << temp2 << "挂载失败！回主线程";
//        qDebug() << "！！！！！！！！！！！";
//        emit failAndReturn();
//        return;
//    }
//    qDebug() << "等待2s，等候文件夹创建完成";
//    QTimer::singleShot(2000, [=](){
//        //挂载对应的硬盘
//        qDebug() << "执行挂载硬盘指令：" << cmdMountStr;
//        cmdMountBash = new CmdBash(cmdMountStr,this);
//        connect(cmdMountBash,&CmdBash::cmdInfo,this,&PartionDevice::cmdInfo);
//        cmdMountBash->cmdExecute();
//    });
//    //挂载对应的硬盘
//    qDebug() << "执行挂载硬盘指令：" << cmdMountStr;
//    cmdMountBash = new CmdBash(cmdMountStr,this);
//    connect(cmdMountBash,&CmdBash::cmdInfo,this,&PartionDevice::cmdInfo);
//    cmdMountBash->cmdExecute();

}

/************************************************
* 函数名称：partionTypeOfDevice
* 功能描述：根据硬盘分区挂载的目录，查找对应目录下的文件，
*         根据文件名判断分区类型。
* 输入参数：QString partionDeviceName
* 输出参数：无
* 修改日期：2020.10.12
* 修改内容：
*   创建  HZH
*
*************************************************/
void PartionDevice::partionTypeOfDevice(QString partionDeviceName)
{
    //拼接出分区当前的挂载目录
    QString filePathCmdString = partionDeviceName;
    QString temp = filePathCmdString;
    filePathCmdString = "/media/" + temp.remove(0,5);

    qDebug() << "开始遍历目录下文件夹" << filePathCmdString;
    QDir *dir = new QDir(filePathCmdString);

    if(!dir->exists())
    {
        qDebug() << filePathCmdString << "文件夹不存在";
        return;
    }
    else
    {
        qDebug() << filePathCmdString << "文件夹存在!";

        dir->setFilter(QDir::Dirs|QDir::Files|QDir::NoDotAndDotDot);
        dir->setSorting(QDir::DirsFirst);
        QFileInfoList dirList = dir->entryInfoList();

        for(int i = 0; i < dirList.size(); i++)
        {
            QFileInfo fileInfo = dirList.at(i);
            if(fileInfo.isDir())
            {

                QString dirName = QDir(fileInfo.absoluteFilePath()).dirName();
                qDebug() << "当前处理文件夹为： " << dirName;
                if(dirName == "boot")//如果该目录下包含名为boot的文件夹，则该目录为root分区挂载目录
                {
                    isRootPartion = true;
                    realRootMountStr = filePathCmdString;
                    QDir *bootdir = new QDir(filePathCmdString + "/boot");
                    if(bootdir->isEmpty())//boot文件夹为空，则boot有被单独分区
                    {
                        qDebug() << "目录下的boot文件夹为空，boot单独分区了！ ";
                        bootIsSeparate = true;
                    }
                    else//boot目录不为空，则boot未被单独分区，读取其中的grub文件夹下的系统架构文件夹，查看架构类型。
                    {
                        qDebug() << "目录下的boot文件夹不为空，boot未单独分区！ ";
                        bootIsSeparate = false;
                        qDebug() << "查看boot文件夹下的grub文件夹中文件内容，判断是什么类型架构的系统！ ";
                        QDir *grubDir = new QDir(filePathCmdString + "/boot/grub/");
                        grubDir->setFilter(QDir::Dirs|QDir::Files|QDir::NoDotAndDotDot);
                        grubDir->setSorting(QDir::DirsFirst);
                        QFileInfoList grubDdirList = grubDir->entryInfoList();

                        for(int i = 0; i < grubDdirList.size(); i++)
                        {
                            QFileInfo grubFileInfo = grubDdirList.at(i);
                            if(grubFileInfo.isDir())
                            {
                                QString grubDirName = QDir(grubFileInfo.absoluteFilePath()).dirName();
                                qDebug() << "当前文件为grub目录下的：" << grubDirName;
                                if(grubDirName != "fonts")
                                {
                                    systemClassEfi = grubDirName;
                                    qDebug() << "grub文件夹中，系统架构文件夹的名字是！ " << systemClassEfi;
                                }
                            }
                        }
                    }
                    break;
                }
                if(dirName == "grub")//如果分区根目录下有grub目录，则该分区为boot分区，读取其中架构类型文件夹
                {
                    qDebug() << "目录下存在grub文件夹，boot单独分区了！ ";
                    isBootPartion = true;
                    bootIsSeparate = true;
                    QDir *grubDir = new QDir(filePathCmdString + "/grub/");
                    grubDir->setFilter(QDir::Dirs|QDir::Files|QDir::NoDotAndDotDot);
                    grubDir->setSorting(QDir::DirsFirst);
                    QFileInfoList grubDdirList = grubDir->entryInfoList();

                    for(int i = 0; i < grubDdirList.size(); i++)
                    {
                        QFileInfo grubFileInfo = grubDdirList.at(i);
                        if(grubFileInfo.isDir())
                        {
                            QString grubDirName = QDir(grubFileInfo.absoluteFilePath()).dirName();
                            qDebug() << "当前文件为grub目录下的：" << grubDirName;
                            if(grubDirName != "fonts")
                            {
                                systemClassEfi = grubDirName;
                                qDebug() << "grub文件夹中，系统架构文件夹的名字是！ " << systemClassEfi;
                            }
                        }
                    }

                    break;
                }
                if(dirName == "EFI")
                {
                    isEfiParion = true;
                    break;
                }
            }
        }
    }
}

/************************************************
* 函数名称：readFstabInfo
* 功能描述：执行硬盘分区挂载及类型判断，读取/etc/fstab，
*         提取分区信息。
* 输入参数：无
* 输出参数：无
* 修改日期：2020.10.12
* 修改内容：
*   创建  HZH
*
*************************************************/
void PartionDevice::readFstabInfo()
{
    //挂载硬盘，读取硬盘类型信息
    qDebug() << "第一次装载硬盘";
    prepareOfFirstMount();
    qDebug() << "开始确定硬盘类型";
    partionTypeOfDevice(DeviceName);

    if(isRootPartion)
    {
        qDebug() << "该硬盘分区为root目录";
    }
    else
    {
        qDebug() << "该硬盘分区非root分区";
        if(isBootPartion)
        {
            qDebug() << "该硬盘分区为boot目录";
        }
        else if(isEfiParion)
        {
            qDebug() << "该硬盘分区为efi目录";
        }
        else
        {
            qDebug() << "home或swap分区";
        }
    }

    if(isRootPartion)//若为root分区，则读取fstab文件
    {
        qDebug() << "该硬盘为root分区!";
        rootPath = DeviceName;
        QFile fstab(fstabPath);
        qDebug() << fstabPath;

        if(fstab.exists())
        {
            qDebug() << "文件存在！";
        }
        else
        {
            qDebug() << "文件路径写错了！";
            return;
        }

        bool isOk = fstab.open(QFile::ReadOnly);
        if (!isOk) {
            qDebug() << "无法打开fstab文件showCmdInfo!";
            //QMessageBox::critical(this,"ERROR","file open failed");
            return;
        }

        QByteArray fstabArray = fstab.readAll();

        if(fstabArray.isEmpty()){
            qDebug() << "fstab内容为空！";
            return;
        }
        else
        {

            //把输出内容按行分割成元素添加至list
            QStringList list = (QString::fromLocal8Bit(fstabArray)).split("\n");
            for(QString& si : list)                        //遍历list中的各行
            {
                QStringList strlist = si.split(" ");
                int size = strlist.size();                 //各str中被空格隔开字段个数
                if (size < 2)
                {
                    continue;
                }

                else if("/boot" == QString::fromLocal8Bit(strlist.at(1).toLocal8Bit().data()) && \
                        "#" == QString::fromLocal8Bit(strlist.at(0).toLocal8Bit().data()))
                {
                    qDebug() << strlist;
                    selfBootDeviceName = QString::fromLocal8Bit(strlist.at(4).toLocal8Bit().data());
                    realBootMountStr = selfBootDeviceName;
                    bootPath = selfBootDeviceName;
                    qDebug() << "realBootMountStr" << realBootMountStr;
                    bootIsSeparate = true;
                    continue;
                }

                else if("/boot/efi" == QString::fromLocal8Bit(strlist.at(1).toLocal8Bit().data()) && \
                        "#" == QString::fromLocal8Bit(strlist.at(0).toLocal8Bit().data()))
                {
                    qDebug() << strlist;
                    selfEfiDeviceName = QString::fromLocal8Bit(strlist.at(4).toLocal8Bit().data());
                    realEfiMountStr = selfEfiDeviceName;
                    efiPath = selfEfiDeviceName;
                    qDebug() << "realEfiMountStr" << realEfiMountStr;
                    continue;
                }
                else if("/home" == QString::fromLocal8Bit(strlist.at(1).toLocal8Bit().data()) && \
                        "#" == QString::fromLocal8Bit(strlist.at(0).toLocal8Bit().data()))
                {
                    qDebug() << strlist;
                    selfHomeDeviceName = QString::fromLocal8Bit(strlist.at(4).toLocal8Bit().data());
                    realHomeMountStr = selfHomeDeviceName;
                    homePath = realHomeMountStr;
                    qDebug() << "realHomeMountStr" << realHomeMountStr;
                    continue;
                }
            }

            if ( 0 != (QString::compare(bootPath,"")))
            {
                qDebug() << "fstab中boot对应路径不为空，boot单独分区了！ ";
                bootIsSeparate = true;
            }
            if ( 0 == (QString::compare(efiPath,"")))
            {
                //错误情况，无法处理！
                qDebug() << "非uefi模式安装系统，无法修复！";
                //emit setInfo("非uefi模式安装系统，无法修复！");
                isUEFIBoot = false;
            }
            else
            {
                isUEFIBoot = true;
            }

            if ( 0 != (QString::compare(homePath,"")))
            {
                qDebug() << "fstab中boot对应路径不为空，boot单独分区了！ ";
                homeIsSeparate = true;
            }
        }
    }
    else
    {
        qDebug() << "该硬盘为非root分区!";
    }
    //再卸载硬盘，以便通过对应关系重新的，正确的挂载各分区
    qDebug() << "执行拆卸硬盘指令：" << cmdUmountStr;
    cmdUmountBash = new CmdBash(cmdUmountStr,this);
    connect(cmdUmountBash,&CmdBash::cmdInfo,this,&PartionDevice::cmdInfo);
    cmdUmountBash->cmdExecute();
}

/************************************************
* 函数名称：cmdInfo
* 功能描述：发送信号给主线程，暂时不用，为空。
* 输入参数：QString inputInfo
* 输出参数：无
* 修改日期：2020.10.12
* 修改内容：
*   创建  HZH
*
*************************************************/
void PartionDevice::cmdInfo(QString inputInfo)
{
    //emit setInfo(inputInfo);
}
