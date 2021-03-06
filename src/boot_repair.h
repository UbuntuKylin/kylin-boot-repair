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
    explicit BootRepair(const bool& hasPwd, const QString& userPwd,const linuxSystemInfo& systemStruct, QObject *parent = nullptr);
    ~BootRepair();
    void repairGrubFile();

    bool isV101 = false;
    linuxSystemInfo currentSystem;
public slots://提供给各线程的槽函数
    void readCmdRepairBashInfo();
    void readInstallCmdRepairBashInfo();
signals://发送信号给主窗体

    void repairResult(bool repairResult,bool v101);

private:

    bool systemVersionCheck();

    void legacyRepairGrubFile();
    void uefiRepairGrubFile();

    void grubinstallCheck();

    bool hasPassWord ;
    QString userPassWord ;


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
