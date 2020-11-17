/************************************************
* 文件描述: 装载硬盘线程，将找到的根分区挂载，以便读取/boot
*          /efi，/root等分区路径。
* 待完善:
* 待优化:
* 修改日期：2020.10.12
* 修改内容：
*   创建  HZH
*************************************************/
#ifndef PARTIONDEVICE_H
#define PARTIONDEVICE_H

#include <QObject>
#include <QThread>
#include <QProcess>
#include <QDebug>
#include <QFileDialog>
#include <QEventLoop>
#include <QFile>
#include <QDir>
#include "cmd_bash.h"

class PartionDevice : public QObject
{
    Q_OBJECT
public:
    PartionDevice(QString partionDeviceName, QObject *parent = nullptr);

    ~PartionDevice();

    void prepareOfFirstMount();                               //提取fdisk内容，进行第一次硬盘装载

    void partionTypeOfDevice(QString partionDeviceName);      //对挂载的硬盘进行分析，判断硬盘分区类型

    void readFstabInfo();                                     //如果是root分区，读取其/etc/目录下的fstab文件
    void archdetectCmdInfo(QString outputInfo);
    QString DeviceName;
    QString rootPath = "";
    QString bootPath = "";
    QString efiPath  = "";
    QString homePath = "";

    bool isRootPartion = false;
    bool isBootPartion = false;
    bool isEfiParion = false;
    bool bootIsSeparate = false;
    bool homeIsSeparate = false;
    bool isUEFIBoot = false;

    bool fileCreatSuccess = false;
    bool devMountSuccess = false;

    QString selfBootDeviceName;
    QString selfEfiDeviceName;
    QString selfHomeDeviceName;
    QString systemClassEfi  = "";
    bool    needGrubInstall = false;

    QString cmdUmountStr;
    QString cmdMkdirStr;
    QString cmdMountStr;

    QString fstabPath;

    QString realMkdirCmd;
    QString realMountCmd;

    QString realRootMountStr;
    QString realBootMountStr;
    QString realEfiMountStr ;
    QString realHomeMountStr;
    QString archDetectCmd;

public slots://提供给各线程的槽函数
    void cmdInfo(QString inputInfo);

signals://发送信号给主窗体
    //void setInfo(QString inputInfo);//写入状态栏信息
    void failAndReturn();

private:
    CmdBash* cmdUmountBash;           //拆卸硬盘线程类
    CmdBash* cmdMkdirBash;            //创建文件夹线程类
    CmdBash* cmdMountBash;            //挂载硬盘线程类
    CmdBash* cmdArchBash;            //挂载硬盘线程类
    QProcess* cmdMount;               //挂载硬盘QProcess

};

#endif // PARTIONDEVICE_H
