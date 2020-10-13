/************************************************
* 文件描述: grub修复前命令拼接线程。
* 待完善:
* 待优化:
* 修改日期：2020.10.12
* 修改内容：
*   创建  HZH
*************************************************/
#ifndef PREREPAIR_H
#define PREREPAIR_H

#include <QObject>
#include "structNeedToUse.h"
#include "cmd_bash.h"
#include "partion_device.h"
#include "boot_repair.h"

class PreRepair : public QObject
{
    Q_OBJECT
public:
    explicit PreRepair(QObject *parent = nullptr);
    ~PreRepair();

public slots://提供给各线程的槽函数
    void start_pushButton_clicked(QStringList list, uint num);//开始按钮按下后连接的槽函数

signals://发送信号给主窗体
    void mainWindowChangePage();                              //主窗体翻页信号

private:

    PartionDevice *currentDevice = nullptr;

    uint systemNumOnDisk = 0;

    QList<linuxSystemInfo> readyToRepairList = {};

    QStringList hardDisklist = {};
    uint hardDiskNum = 0;


    BootRepair *currentSystem;

};

#endif // BOOTREPAIR_H
