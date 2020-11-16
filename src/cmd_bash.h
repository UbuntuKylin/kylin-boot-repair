/************************************************
* 文件描述: 用于封装创建新qprocess执行语句流程而创建的类
* 待完善:
* 待优化:
* 修改日期：2020.10.12
* 修改内容：
*   创建  HZH
*************************************************/
#ifndef CMDBASH_H
#define CMDBASH_H

#include <QObject>
#include <QThread>
#include <QProcess>
#include <QDebug>
#include <QFileDialog>
#include <QFile>
#include <QDir>
#include "fdisk_thread.h"

class CmdBash : public QObject
{
    Q_OBJECT
public:
    explicit CmdBash(QString inputCmd, QObject *parent);
    ~CmdBash();


    QString cmd;
    QProcess *currentBash;

    bool bashFinished;           //命令语句执行结果

    void cmdExecute();

signals://partionDevice提供的槽函数
    void cmdInfo(QString inputInfo);

private:


    void readCmdBashInfo();
    void readCmdBashErrorInfo();
};

#endif // CMDBASH_H
