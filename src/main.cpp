/************************************************
* 文件描述: 主函数
* 待完善:
* 待优化:
* 修改日期：2020.10.12
* 修改内容：
*   创建  HZH
*************************************************/
#include "mainwindow.h"
#include "dbusadaptor.h"
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QTranslator>
#include <QLibraryInfo>
#include <QApplication>

/************************************************
* 函数名称：responseCommand
* 功能描述：dbus响应函数
* 输入参数：QApplication指针
* 输出参数：
* 修改日期：2020.12.02
* 修改内容：
*   创建  HZH
*
*************************************************/
void responseCommand(QApplication &a) //响应外部dbus命令
{
    //提供DBus接口，添加show参数
    QCommandLineParser parser;
    parser.setApplicationDescription(QCoreApplication::translate("main", "kylinbootrepair"));
    parser.addHelpOption();
    parser.addVersionOption();

    QCommandLineOption swOption(QStringLiteral("show"),QCoreApplication::translate("main", "show kylin-boot-repair test"));

    parser.addOptions({swOption});
    parser.process(a);

    if(parser.isSet(swOption) || !QDBusConnection::sessionBus().registerService("com.kylin.bootrepair"))
    {
//        if(!a.isRunning())return;
            QDBusInterface *interface = new QDBusInterface("com.kylin.bootrepair",
                                                           "/com/kylin/bootrepair",
                                                           "com.kylin.bootrepair",
                                                           QDBusConnection::sessionBus(),
                                                           NULL);

            interface->call(QStringLiteral("showMainWindow"));
    }
}
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
    //高清屏幕自适应
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);

    QApplication a(argc, argv);
    responseCommand(a);//响应dbus绑定事件

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
    //qInstallMessageHandler(qtMessagePutIntoLog);
    qDebug() << "*******************************************************";
    qDebug() << "*";
    qDebug() << "* 启动麒麟引导修复工具";
    qDebug() << "* 当前时间：" << QString(QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss"));
    qDebug() << "*";
    qDebug() << "*******************************************************";

    QString latestTime = QString(QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss"));
    MainWindow w;
    DbusAdaptor adaptor(&w);
    Q_UNUSED(adaptor);
    auto connection = QDBusConnection::sessionBus();
    qDebug()<<"建立DBus服务状态： "<< (connection.registerService("com.kylin.bootrepair")&&connection.registerObject("/com/kylin/bootrepair", &w));

    w.outputTime = latestTime;

//    MotifWmHints hints;
//    hints.flags = MWM_HINTS_FUNCTIONS|MWM_HINTS_DECORATIONS;
//    hints.functions = MWM_FUNC_ALL;
//    hints.decorations = MWM_DECOR_BORDER;
//    XAtomHelper::getInstance()->setWindowMotifHint(w.winId(), hints);

    return a.exec();
}
