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
    explicit BootRepair(linuxSystemInfo systemStruct, QObject *parent = nullptr);
    ~BootRepair();
    void repairGrubFile();

public slots://提供给各线程的槽函数
    void cmdInfo(QString inputInfo);

signals://发送信号给主窗体
    //void setInfo(QString inputInfo);//写入状态栏信息

private:

    linuxSystemInfo currentSystem;
    CmdBash* chrootCmd;
    CmdBash* bootMountCmd;
    CmdBash* treeMkdirCmd;
    CmdBash* rootMkdirCmd;
    CmdBash* rootMountCmd;
    CmdBash* efiMountCmd;
    CmdBash* devMountCmd;
    CmdBash* procMountCmd;
    CmdBash* sysMountCmd;
    CmdBash* grubInstallCmd;
    CmdBash* grubMkconfigCmd;
    CmdBash* updateGrubCmd;
    CmdBash* homeMountCmd;
    CmdBash* umountAllCmd;

};

#endif // BOOTREPAIR_H
