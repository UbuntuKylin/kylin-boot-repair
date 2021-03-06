/************************************************
* 文件描述: fdisk线程，用于执行sudo fdisk -l命令，读取
*          系统硬盘信息。
* 待完善:
* 待优化:
* 修改日期：2020.10.12
* 修改内容：
*   创建  HZH
*************************************************/
#ifndef FDISKTHREAD_H
#define FDISKTHREAD_H

#include <QObject>
#include <QThread>
#include <QProcess>
#include <QDebug>
#include <QFileDialog>
#include <QTimer>
#include <QTime>

class FdiskThread : public QObject
{
    Q_OBJECT
public:
    explicit FdiskThread(const bool& hasPwd,const QString& userPwd,QObject *parent = nullptr);
    ~FdiskThread();
    QStringList listOfDevice = {};
    uint numOfLinuxPartion;

signals://发送信号给主窗体
    void changeToMainPage();
    void startpBootRepairThread(QStringList inputListOfDevice);//开启修复线程
    void failAndReturn();                                      //出现错误，失败返回主线程信号

public slots:
    void startFdisk(QString fdiskCmd);//供外部调用的槽函数


private:
    void readcmdFdiskBashInfo();//读取*cmdFdiskBash执行命令后返回内容函数
    void readcmdMountBashInfo();//读取*cmdMountBash执行命令后返回内容函数
    void readcmdBootRepairBashBashInfo();//读取*cmdBootRepairBash执行命令后返回内容函数
    void readcmdFdiskBashErrorInfo();
    void startPreHandle(QStringList cmdOutFromFdisk);//处理fdisk返回的内容，提取硬盘信息
    void startMount();//根据硬盘信息，创建文件夹,装载硬盘

    const bool hasPassWord;
    const QString userPassWord;

    QProcess *cmdFdiskBash = nullptr;//qprocess指针，用来写入fdisk命令
    QProcess *cmdMountBash = nullptr;//qprocess指针，用来写入mkdir命令
    QProcess *cmdBootRepairBash = nullptr;//qprocess指针，用来写入repair命令

    QStringList allDeviceInfoStr = {};
    QStringList fdiskCmdStdOut   = {};

    uint rootPartionNum = 0;                //root目录的个数，即该电脑上安装了多少个linux内核系统
    uint bootPartionNum = 0;                //boot目录的个数，即该电脑上安装了多少个linux内核系统

    QTimer *fdiskTimer = new QTimer(this);

};

#endif // FDISKTHREAD_H
