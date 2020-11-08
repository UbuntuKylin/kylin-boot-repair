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
#include "logwidget.h"
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

#define LOGWINDOWWIDETH 460                  //窗口宽度
#define LOGWINDOWHEIGHT 544                  //窗口高度
#define LOGTITLEHEIGHT 50                    //标题栏高度
#define LOGSHADOWWIDTH 10                    //阴影宽度
#define LOGWIDGETRADIUS 12                   //窗口圆角
#define LOGBUTTONRADIUS 6                    //按钮圆角
#define LOGSHADOWALPHA 0.08                  //阴影透明度


class WarningPage : public QWidget
{
    Q_OBJECT
public:
    explicit WarningPage( StyleWidgetAttribute);
    void pageChangeForTheme(QString str);
signals:
    void closeMainWin();

private:
    LogWidget *logWinWidget = nullptr;

    QPushButton *logButton = nullptr;
    QPushButton *exitButton = nullptr;

    StyleWidgetAttribute swa;//属性

    QLabel *warningIcon = nullptr;//扫描硬盘标志
    QLabel *warningText = nullptr;//扫描硬盘标语

    void startFdisk(QString fdiskCmd);                            //向Fdisk线程发送调用信号
    void initControlQss();

};

#endif // WARNINGPAGE_H
