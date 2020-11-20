/************************************************
* 文件描述: 修复指令执行线程，真正修复命令的执行在此线程中
* 待完善:
* 待优化:
* 修改日期：2020.10.12
* 修改内容：
*   创建  HZH
*************************************************/
#include "boot_repair.h"

/************************************************
* 函数名称：BootRepair
* 功能描述：构造函数，读取输入的结构体中，当前系统的各分区目录字符串
*          对私有成员进行初始化。
* 输入参数：linuxSystemInfo systemStruct, QObject *parent
* 输出参数：无
* 修改日期：2020.10.12
* 修改内容：
*   创建  HZH
*
*************************************************/
BootRepair::BootRepair(bool hasPwd, QString userPwd, linuxSystemInfo systemStruct, QObject *parent) : QObject(parent)
{
    hasPassWord  = hasPwd;
    userPassWord = userPwd;
    currentSystem = systemStruct;
}

/************************************************
* 函数名称：~BootRepair
* 功能描述：析构函数
* 输入参数：
* 输出参数：
* 修改日期：2020.10.12
* 修改内容：
*   创建  HZH
*
*************************************************/
BootRepair::~BootRepair()
{
    treeMkdirCmd->deleteLater();
    rootMkdirCmd->deleteLater();

    chrootCmd->deleteLater();

    bootMountCmd->deleteLater();

    rootMountCmd->deleteLater();
    efiMountCmd->deleteLater();
    devMountCmd->deleteLater();
    procMountCmd->deleteLater();
    sysMountCmd->deleteLater();
    grubInstallCmd->deleteLater();
    grubMkconfigCmd->deleteLater();
    updateGrubCmd->deleteLater();
    homeMountCmd->deleteLater();
    umountAllCmd->deleteLater();
}

/************************************************
* 函数名称：repairGrubFile()
* 功能描述：修复grub文件函数，根据命令字符串创建对应的
*         cmd_bash对象，执行对应语句。
* 输入参数：
* 输出参数：
* 修改日期：2020.11.07
* 修改内容：
*   创建  HZH
*   修改  完善打印信息
*
*************************************************/
bool BootRepair::repairGrubFile()
{
    if (false == currentSystem.isUEFIBoot)
    {
        qDebug() << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
        qDebug() << "严重错误！！！无法检测到efi分区，无法继续修复！";
        qDebug() << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
        return false;//检测失败，返回false
    }



    qDebug() << "创建挂载文件所需要文件夹：" << currentSystem.treeMkdirCmd;
    treeMkdirCmd = new CmdBash(hasPassWord,userPassWord,currentSystem.treeMkdirCmd,this);
    //connect(treeMkdirCmd,&CmdBash::cmdInfo,this,&BootRepair::cmdInfo);
    treeMkdirCmd->cmdExecute();

    qDebug() << "创建挂载根目录文件夹：" << currentSystem.rootMkdirCmd;
    rootMkdirCmd = new CmdBash(hasPassWord,userPassWord,currentSystem.rootMkdirCmd,this);
    //connect(rootMkdirCmd,&CmdBash::cmdInfo,this,&BootRepair::cmdInfo);
    rootMkdirCmd->cmdExecute();

    qDebug() << "挂载根目录：" << currentSystem.rootMountCmd;
    rootMountCmd = new CmdBash(hasPassWord,userPassWord,currentSystem.rootMountCmd,this);
    //connect(rootMountCmd,&CmdBash::cmdInfo,this,&BootRepair::cmdInfo);
    rootMountCmd->cmdExecute();

    if(currentSystem.bootIsSeparate)
    {
        qDebug() << "该系统中，存在/boot单独分区";
        qDebug() << currentSystem.bootMountCmd;
        bootMountCmd = new CmdBash(hasPassWord,userPassWord,currentSystem.bootMountCmd,this);
        //connect(bootMountCmd,&CmdBash::cmdInfo,this,&BootRepair::cmdInfo);
        bootMountCmd->cmdExecute();
    }
    else
    {
        qDebug() << "该系统中/boot未单独分区";
    }

    qDebug() << currentSystem.efiMountCmd;
    efiMountCmd = new CmdBash(hasPassWord,userPassWord,currentSystem.efiMountCmd,this);
    //connect(efiMountCmd,&CmdBash::cmdInfo,this,&BootRepair::cmdInfo);
    efiMountCmd->cmdExecute();

    if(currentSystem.homeIsSeparate)
    {
        qDebug() << "该系统中/home单独分区了";
        qDebug() << currentSystem.homeIsSeparate;
        homeMountCmd = new CmdBash(hasPassWord,userPassWord,currentSystem.homeMountCmd,this);
        //connect(homeMountCmd,&CmdBash::cmdInfo,this,&BootRepair::cmdInfo);
        homeMountCmd->cmdExecute();
    }
    else
    {
        qDebug() << "该系统中/home未单独分区";
    }

    qDebug() << currentSystem.devMountCmd;
    devMountCmd = new CmdBash(hasPassWord,userPassWord,currentSystem.devMountCmd,this);
    //connect(devMountCmd,&CmdBash::cmdInfo,this,&BootRepair::cmdInfo);
    devMountCmd->cmdExecute();

    qDebug() << currentSystem.procMountCmd;
    procMountCmd = new CmdBash(hasPassWord,userPassWord,currentSystem.procMountCmd,this);
    //connect(procMountCmd,&CmdBash::cmdInfo,this,&BootRepair::cmdInfo);
    procMountCmd->cmdExecute();

    qDebug() << currentSystem.sysMountCmd;
    sysMountCmd = new CmdBash(hasPassWord,userPassWord,currentSystem.sysMountCmd,this);
    //connect(sysMountCmd,&CmdBash::cmdInfo,this,&BootRepair::cmdInfo);
    sysMountCmd->cmdExecute();

    //这几条命令需要在chroot命令之后的模式下使用，所以需要是在一个QProcess里运行
    qDebug() << currentSystem.chrootCmd;

    chrootCmd = new QProcess();   //创建QProcess对象并连接信号与槽

    chrootCmd->start("bash");

    chrootCmd->write(currentSystem.chrootCmd.toLocal8Bit() + '\n');

    //此条不需要，暂时保留
//    qDebug() << currentSystem.grubMkconfigCmd;
//    chrootCmd->write(currentSystem.grubMkconfigCmd.toLocal8Bit()+ "\n");
//    if(hasPassWord)
//    {
//        chrootCmd->write(userPassWord.toLocal8Bit() + '\n');
//    }

    //这里要检查是否需要进行grubinstall
    if(currentSystem.needGrubInstall && !(currentSystem.grubInstallCmd.isEmpty()))
    {
        qDebug() << "需要执行grub-install，命令内容为：" << currentSystem.grubInstallCmd;

        chrootCmd->write(currentSystem.grubInstallCmd.toLocal8Bit()+ "\n");
        if(hasPassWord)
        {
            chrootCmd->write(userPassWord.toLocal8Bit() + '\n');
        }
    }
    else if(currentSystem.needGrubInstall && currentSystem.grubInstallCmd.isEmpty())
    {
        qDebug() << "需要执行grub-install，但命令为空";
        return false;//逻辑存在问题，检测失败，返回false
    }
    else if(false == currentSystem.needGrubInstall && !(currentSystem.grubInstallCmd.isEmpty()))
    {
        qDebug() << "不需要执行grub-install，但命令不为空";
        qDebug() << "命令内容为：" << currentSystem.grubInstallCmd;
        return false;//逻辑存在问题，检测失败，返回false
    }
    else
    {
        qDebug() << "无需执行grub-install";
    }

    qDebug() << currentSystem.updateGrubCmd;

    chrootCmd->write(currentSystem.updateGrubCmd.toLocal8Bit()+ "\n");
    if(hasPassWord)
    {
        chrootCmd->write(userPassWord.toLocal8Bit() + '\n');
    }
    chrootCmd->waitForFinished();

    chrootCmd->kill();

    qDebug() << "拆卸已装载的分区" << currentSystem.umountAllCmd;
    umountAllCmd = new CmdBash(hasPassWord,userPassWord,currentSystem.umountAllCmd,this);
    //connect(umountAllCmd,&CmdBash::cmdInfo,this,&BootRepair::cmdInfo);
    umountAllCmd->cmdExecute();

    return true;  //修复成功，返回true
}

/************************************************
* 函数名称：cmdInfo
* 功能描述：发送信号给主线程，返回相关信息，现暂时废弃
* 输入参数：QString inputInfo
* 输出参数：无
* 修改日期：2020.10.12
* 修改内容：
*   创建  HZH
*
*************************************************/
//void BootRepair::cmdInfo(QString inputInfo)
//{
//    //qDebug() << inputInfo;
//    //emit setInfo(inputInfo);
//}

