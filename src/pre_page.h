/************************************************
* 文件描述: 预扫描界面（执行fdisk线程时显示）。
* 待完善:
* 待优化:
* 修改日期：2020.10.12
* 修改内容：
*   创建  HZH
*************************************************/
#ifndef PREPAGE_H
#define PREPAGE_H

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
#include <QMovie>

class PrePage : public QWidget
{
    Q_OBJECT
public:
    explicit PrePage( StyleWidgetAttribute);
    void pageChangeForTheme(QString str);

public slots:

signals:

private:

    QPushButton *repairStart = nullptr;                          //开始修复按钮

    StyleWidgetAttribute swa;                                    //属性

    QMovie *movieLoading=nullptr;
    QLabel *lableMovie=nullptr;
    QLabel *loadingIcon = nullptr;                               //扫描硬盘标志
    QLabel *loadingText = nullptr;                               //扫描硬盘标语

    void startFdisk(QString fdiskCmd);                            //向Fdisk线程发送调用信号
    void initControlQss();




};

#endif // MAINPAGE_H
