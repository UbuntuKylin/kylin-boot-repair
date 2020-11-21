/************************************************
* 文件描述: 修复指令执行线程，真正修复命令的执行在此线程中
* 待完善:
* 待优化:
* 修改日期：2020.10.12
* 修改内容：
*   创建  HZH
*************************************************/
#ifndef BOOTREPAIR_H
#define BOOTREPAIR_H

#include <QObject>
#include "structNeedToUse.h"
#include "cmd_bash.h"

class BootRepair : public QObject
{
    Q_OBJECT
public:
    explicit BootRepair(bool hasPwd, QString userPwd,linuxSystemInfo systemStruct, QObject *parent = nullptr);
    ~BootRepair();
    void repairGrubFile();

public slots://提供给各线程的槽函数
    void readcmdRepairBashInfo();

signals://发送信号给主窗体
    //void setInfo(QString inputInfo);//写入状态栏信息
    void repairResult(bool result);

private:
    bool hasPassWord  = false;
    QString userPassWord = "";

    linuxSystemInfo currentSystem;
    QProcess* chrootCmd       = nullptr;
    QProcess* grubMkconfigCmd = nullptr;
    QProcess* updateGrubCmd   = nullptr;
    CmdBash*  bootMountCmd    = nullptr;
    CmdBash*  treeMkdirCmd    = nullptr;
    CmdBash*  rootMkdirCmd    = nullptr;
    CmdBash*  rootMountCmd    = nullptr;
    CmdBash*  efiMountCmd     = nullptr;
    CmdBash*  devMountCmd     = nullptr;
    CmdBash*  procMountCmd    = nullptr;
    CmdBash*  sysMountCmd     = nullptr;
    CmdBash*  grubInstallCmd  = nullptr;


    CmdBash*  homeMountCmd    = nullptr;
    CmdBash*  umountAllCmd    = nullptr;

    bool      finalResult     = false;
};

#endif // BOOTREPAIR_H
