/************************************************
* 文件描述: 主函数
* 待完善:
* 待优化:
* 修改日期：2020.10.12
* 修改内容：
*   创建  HZH
*************************************************/
#include "mainwindow.h"
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QTranslator>
#include <QLibraryInfo>
#include <QApplication>

/************************************************
* 函数名称：qtMessagePutIntoLog
* 功能描述：日志记录函数
* 输入参数：qDebug标准输出
* 输出参数：BootRepairLog.txt
* 修改日期：2020.11.07
* 修改内容：
*   创建  HZH
*
*************************************************/
void qtMessagePutIntoLog(QtMsgType type, const QMessageLogContext &context, const QString &qDebugMsg)
{
    QString logTxt;
    QString currentTime = QString(QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss"));
    logTxt = QString(currentTime + ": %1").arg(qDebugMsg);

    QString logPath = "/tmp/";
    QFile outputLog(logPath+"BootRepairLog.txt");
    outputLog.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream os(&outputLog);
    os << logTxt << "\r\n";
    os.flush();              //保证文本实时刷新
    outputLog.flush();
    outputLog.close();
}

/************************************************
* 函数名称：
* 功能描述：
* 输出参数：
* 修改日期：2020.10.12
* 修改内容：
*   创建  HZH
*
*************************************************/
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator app_trans;
    QTranslator qt_trans;
    QString locale = QLocale::system().name();
    QString trans_path;
    if (QDir("/usr/share/kylin-boot-repair/translations").exists()) {
        trans_path = "/usr/share/kylin-boot-repair/translations";
    }
    else {
        trans_path = qApp->applicationDirPath() + "/translations";
    }
    QString qt_trans_path;
    qt_trans_path = QLibraryInfo::location(QLibraryInfo::TranslationsPath);// /usr/share/qt5/translations

    if (locale == "zh_CN") {
        if(!app_trans.load("kylin-boot-repair_" + locale + ".qm", trans_path))
            qDebug() << "Load translation file："<< "kylin-boot-repair_" + locale + ".qm from" << trans_path << "failed!";
        else
            a.installTranslator(&app_trans);

        if(!qt_trans.load("qt_" + locale + ".qm", qt_trans_path))
            qDebug() << "Load translation file："<< "qt_" + locale + ".qm from" << qt_trans_path << "failed!";
        else
            a.installTranslator(&qt_trans);
    }

    //打开日志
    qInstallMessageHandler(qtMessagePutIntoLog);
    qDebug() << "*******************************************************";
    qDebug() << "*";
    qDebug() << "* 启动麒麟引导修复工具";
    qDebug() << "* 当前时间：" << QString(QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss"));
    qDebug() << "*";
    qDebug() << "*******************************************************";

    QString latestTime = QString(QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss"));
    MainWindow w;
    w.outputTime = latestTime;

    return a.exec();
}
