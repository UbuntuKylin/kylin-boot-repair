/************************************************
* 文件描述: 用于封装创建新qprocess执行语句流程而创建的类
* 待完善:
* 待优化:
* 修改日期：2020.10.12
* 修改内容：
*   创建  HZH
*************************************************/
#include "cmd_bash.h"

/************************************************
* 函数名称：CmdBash
* 功能描述：构造函数，根据入参初始化成员。
* 输入参数：QString inputCmd, QObject *parent
* 输出参数：无
* 修改日期：2020.10.12
* 修改内容：
*   创建  HZH
*
*************************************************/
CmdBash::CmdBash(QString inputCmd, QObject *parent) : QObject(parent)
{
    cmd = inputCmd;
    bashFinished = false;
    qDebug() << "创建名为 " << cmd << "的线程";
}

/************************************************
* 函数名称：~CmdBash()
* 功能描述：析构函数，结束并关闭线程。若不销毁线程对象，会造成
*         卡顿等现象。
* 输入参数：无
* 输出参数：无
* 修改日期：2020.10.12
* 修改内容：
*   创建  HZH
*
*************************************************/
CmdBash::~CmdBash()
{
    if(currentBash)
    {
        currentBash->waitForFinished();
        currentBash->close();
        currentBash->deleteLater();
    }
}

/************************************************
* 函数名称：cmdExecute()
* 功能描述：执行函数，创建新的QProcess，执行linux命令。
* 输入参数：无
* 输出参数：无
* 修改日期：2020.10.12
* 修改内容：
*   创建  HZH
*
*************************************************/
void CmdBash::cmdExecute()
{
    currentBash = new QProcess();
    currentBash->start("bash");
    currentBash->waitForStarted();

    connect(currentBash,&QProcess::readyReadStandardOutput,this,&CmdBash::readCmdBashInfo);

    qDebug() << "执行命令： " << cmd;
    currentBash->write(cmd.toLocal8Bit() + '\n');

    currentBash->closeWriteChannel();


    bashFinished = currentBash->waitForFinished(10000);
}

/************************************************
* 函数名称：readCmdBashInfo()
* 功能描述：读取currentBash的标准返回内容，暂无显示框，对
*         程序执行无影响。
* 输入参数：无
* 输出参数：无
* 修改日期：2020.10.12
* 修改内容：
*   创建  HZH
*
*************************************************/
void CmdBash::readCmdBashInfo()
{
    QByteArray cmdStdOut = currentBash->readAllStandardOutput();

    if(!cmdStdOut.isEmpty()){
        qDebug() << cmdStdOut;
        //qDebug() << "命令" << cmd<< "获取数据信息成功";
        qDebug() << "cmdbash类有返回信息";
        emit cmdInfo(cmdStdOut);
    }
    else
    {
        qDebug() << "实验内容";
        qDebug() << "命令" << cmd<< "无返回信息";
        emit cmdInfo(cmd + "无返回信息");
    }
}
