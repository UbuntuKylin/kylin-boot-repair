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
    explicit PreRepair(const bool& hasPwd, const QString& userPwd, QObject *parent = nullptr);
    ~PreRepair();

public slots://提供给各线程的槽函数
    void start_pushButton_clicked(const QStringList& list, const uint& num);//开始按钮按下后连接的槽函数
    void getRepairResult(const bool& res,const bool& v101);                        //获取修复结果
signals://发送信号给主窗体
    void changeToFinishPage();                              //主窗体翻页信号
    void failAndReturn();

private:
    bool hasPassWord;
    QString userPassWord;

    PartionDevice *currentDevice = nullptr;

    uint systemNumOnDisk = 0;

    QList<linuxSystemInfo> readyToRepairList = {};

    QStringList hardDisklist = {};
    uint hardDiskNum = 0;


    BootRepair *currentBootRepair;

    bool repairSuccess = true;

    uint repairTimes = 0;
    bool isV101 = false;

};

#endif // BOOTREPAIR_H
