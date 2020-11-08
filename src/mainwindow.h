/************************************************
* 文件描述: 主线程类，窗口参数设定。
* 待完善:
* 待优化:
* 修改日期：2020.10.12
* 修改内容：
*   创建  HZH
*************************************************/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define WINDOWWIDETH 360 //窗口宽度
#define WINDOWHEIGHT 460//窗口高度
#define TITLEHEIGHT 50//标题栏高度
#define SHADOWWIDTH 10//阴影宽度
#define WIDGETRADIUS 12//窗口圆角
#define BUTTONRADIUS 6//按钮圆角
#define SHADOWALPHA 0.08//阴影透明度


#include <QMainWindow>
#include <QWidget>
#include <QMessageBox>
#include <QStackedWidget>
#include <QProcess>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QThread>
#include <QFontDatabase>
#include <QTimer>
#include <QTime>
#include <QStandardPaths>
#include <QGSettings>

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <xcb/xcb.h>

#include "fdisk_thread.h"
#include "partion_device.h"
#include "cmd_bash.h"
#include "boot_repair.h"
#include "stylewidget.h"
#include "pre_page.h"
#include "start_page.h"
#include "repair_page.h"
#include "warning_page.h"
#include "repair_page2.h"
#include "finish_page.h"
#include "pre_repair.h"

#define FITTHEMEWINDOW "org.ukui.style"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QString outputTime = nullptr;                         //用于获取本次程序启动时间

public slots://提供给各线程的槽函数
    void passwordNoInput();                               //密码输入对话框弹窗没有输入就被关闭
    void makeStart();                                     //开始修复槽函数
    void closeMainWin();                                  //供子线程调用的关闭主程序窗口的函数接口
    void failAndReturn();

private slots:
    void changeToNextPage();                              //翻页槽函数

signals:
    void startFdisk(QString fdiskCmd);                            //向Fdisk线程发送调用信号
    void startRepair(QStringList inputListOfDevice);              //向bootrepair线程发送调用信号
    void start_pushButton_clicked(QStringList list, uint Num);    //按键事件函数
private:

    void myStyle();

    void prepareAction();

    int changePage();

    void checkSingle();

    StyleWidget *styleWidget = nullptr;

    QStackedWidget *stackedWidget = nullptr;

    PrePage *prePage         = nullptr;
    StartPage *startPage     = nullptr;
    RepairPage *repairPage   = nullptr;
    WarningPage *warningPage = nullptr;
    RepairPage2 *repairPage2 = nullptr;
    FinishPage *finishPage   = nullptr ;

    PreRepair* mycmdPreRepairBash;                                   //PreRepair线程
    QThread *pPreRepair;

    FdiskThread* mycmdFdiskBash;                                     //fdisk线程
    QThread *pFdiskthread;

    QStringList hardDisklist;                                        //硬盘分区列表
    uint hardDiskNum;                                                //硬盘分区个数

    // getstting初始化、值获取、 设置getsetting值
    void initGsetting();
    void setThemeStyle();

    QGSettings  *m_pThemeStyle= nullptr;
};
#endif // MAINWINDOW_H
