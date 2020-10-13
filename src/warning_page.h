/************************************************
* 文件描述: In User Settings Edit
* 待完善:
* 待优化:
* 修改日期：2020.10.12
* 修改内容：
*   创建  HZH
*************************************************/
#ifndef WARNINGPAGE_H
#define WARNINGPAGE_H

#include "stylewidget.h"
#include <QDebug>
//控件
#include <QWidget>
#include <QLabel>
#include <QPushButton>
//布局
#include <QBoxLayout>
//打开文件
#include <QFileDialog>
//读取本地字体
#include <QFontDatabase>
//硬盘信息
#include <QStorageInfo>

class WarningPage : public QWidget
{
    Q_OBJECT
public:
    explicit WarningPage( StyleWidgetAttribute);

signals:

private:

    QPushButton *cancelButton = nullptr;
    QPushButton *continueButton = nullptr;

    StyleWidgetAttribute swa;//属性

    QLabel *warningIcon = nullptr;//扫描硬盘标志
    QLabel *warningText = nullptr;//扫描硬盘标语

    void startFdisk(QString fdiskCmd);                            //向Fdisk线程发送调用信号
    void initControlQss();

};

#endif // WARNINGPAGE_H
