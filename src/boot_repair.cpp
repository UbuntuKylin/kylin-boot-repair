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
BootRepair::BootRepair(linuxSystemInfo systemStruct, QObject *parent) : QObject(parent)
{
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
void BootRepair::repairGrubFile()
{
    if (false == currentSystem.isUEFIBoot)
    {
        qDebug() << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
        qDebug() << "严重错误！！！无法检测到efi分区，无法继续修复！";
        qDebug() << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
        return;
    }



    qDebug() << "创建挂载文件所需要文件夹：" << currentSystem.treeMkdirCmd;
    treeMkdirCmd = new CmdBash(currentSystem.treeMkdirCmd,this);
    connect(treeMkdirCmd,&CmdBash::cmdInfo,this,&BootRepair::cmdInfo);
    treeMkdirCmd->cmdExecute();

    qDebug() << "创建挂载根目录文件夹：" << currentSystem.rootMkdirCmd;
    rootMkdirCmd = new CmdBash(currentSystem.rootMkdirCmd,this);
    connect(rootMkdirCmd,&CmdBash::cmdInfo,this,&BootRepair::cmdInfo);
    rootMkdirCmd->cmdExecute();

    qDebug() << "挂载根目录：" << currentSystem.rootMountCmd;
    rootMountCmd = new CmdBash(currentSystem.rootMountCmd,this);
    connect(rootMountCmd,&CmdBash::cmdInfo,this,&BootRepair::cmdInfo);
    rootMountCmd->cmdExecute();

    if(currentSystem.bootIsSeparate)
    {
        qDebug() << "该系统中，存在/boot单独分区";
        qDebug() << currentSystem.bootMountCmd;
        bootMountCmd = new CmdBash(currentSystem.bootMountCmd,this);
        connect(bootMountCmd,&CmdBash::cmdInfo,this,&BootRepair::cmdInfo);
        bootMountCmd->cmdExecute();
    }
    else
    {
        qDebug() << "该系统中/boot未单独分区";
    }

    qDebug() << currentSystem.efiMountCmd;
    efiMountCmd = new CmdBash(currentSystem.efiMountCmd,this);
    connect(efiMountCmd,&CmdBash::cmdInfo,this,&BootRepair::cmdInfo);
    efiMountCmd->cmdExecute();

    if(currentSystem.homeIsSeparate)
    {
        qDebug() << "该系统中/home单独分区了";
        qDebug() << currentSystem.homeIsSeparate;
        homeMountCmd = new CmdBash(currentSystem.homeMountCmd,this);
        connect(homeMountCmd,&CmdBash::cmdInfo,this,&BootRepair::cmdInfo);
        homeMountCmd->cmdExecute();
    }
    else
    {
        qDebug() << "该系统中/home未单独分区";
    }

    qDebug() << currentSystem.devMountCmd;
    devMountCmd = new CmdBash(currentSystem.devMountCmd,this);
    connect(devMountCmd,&CmdBash::cmdInfo,this,&BootRepair::cmdInfo);
    devMountCmd->cmdExecute();

    qDebug() << currentSystem.procMountCmd;
    procMountCmd = new CmdBash(currentSystem.procMountCmd,this);
    connect(procMountCmd,&CmdBash::cmdInfo,this,&BootRepair::cmdInfo);
    procMountCmd->cmdExecute();

    qDebug() << currentSystem.sysMountCmd;
    sysMountCmd = new CmdBash(currentSystem.sysMountCmd,this);
    connect(sysMountCmd,&CmdBash::cmdInfo,this,&BootRepair::cmdInfo);
    sysMountCmd->cmdExecute();

    //这几条命令需要在chroot命令之后的模式下使用，所以需要是在一个cmdbash里运行
    qDebug() << currentSystem.chrootCmd;
    QString temp = currentSystem.chrootCmd + "\n";


    chrootCmd = new CmdBash( temp,this);
    connect(chrootCmd,&CmdBash::cmdInfo,this,&BootRepair::cmdInfo);
    chrootCmd->cmdExecute();


    qDebug() << currentSystem.grubMkconfigCmd;
    QString temp1 = currentSystem.chrootCmd + "\n";
    temp1 += currentSystem.grubMkconfigCmd;
    temp1 += "\n";

    grubMkconfigCmd = new CmdBash(temp1,this);
    connect(grubMkconfigCmd,&CmdBash::cmdInfo,this,&BootRepair::cmdInfo);
    grubMkconfigCmd->cmdExecute();

    qDebug() << currentSystem.grubInstallCmd;
    QString temp2 = currentSystem.chrootCmd + "\n";
    temp2 += currentSystem.grubInstallCmd;
    temp2 += "\n";

    grubInstallCmd = new CmdBash(temp2,this);
    connect(grubInstallCmd,&CmdBash::cmdInfo,this,&BootRepair::cmdInfo);
    grubInstallCmd->cmdExecute();

    qDebug() << currentSystem.updateGrubCmd;
    QString temp3 = currentSystem.chrootCmd + "\n";
    temp3 += currentSystem.updateGrubCmd;
    temp3 += "\n";

    updateGrubCmd = new CmdBash(temp3,this);
    connect(updateGrubCmd,&CmdBash::cmdInfo,this,&BootRepair::cmdInfo);
    updateGrubCmd->cmdExecute();

    qDebug() << "拆卸已装载的分区" << currentSystem.umountAllCmd;
    umountAllCmd = new CmdBash( currentSystem.umountAllCmd,this);
    connect(umountAllCmd,&CmdBash::cmdInfo,this,&BootRepair::cmdInfo);
    umountAllCmd->cmdExecute();
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
void BootRepair::cmdInfo(QString inputInfo)
{
    //emit setInfo(inputInfo);
}

