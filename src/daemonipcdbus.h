/************************************************
* 文件描述: QDbus类
* 待完善:
* 待优化:
* 修改日期：2020.11.04
* 修改内容：
*   创建  HZH
*************************************************/
#ifndef DAEMONIPCDBUS_H
#define DAEMONIPCDBUS_H

#define KYLIN_USER_GUIDE_PATH ("/")

#define KYLIN_USER_GUIDE_SERVICE ("com.kylinUserGuide.hotel")

#define KYLIN_USER_GUIDE_INTERFACE ("com.guide.hotel")

#define SERVICE_NAME_SIZE (30)

#include <QObject>
#include <QApplication>
#include <QCoreApplication>
#include <QDebug>
#include <QtDBus/QDBusConnection>
#include <QtDBus/QDBusConnectionInterface>
#include <QtDBus/QDBusMessage>
#include <QtDBus/QDBusReply>
#include <unistd.h>
#include <sys/types.h>

class DaemonIpcDbus : public QObject
{
    Q_OBJECT
    // 定义Interface名称为com.scorpio.test.value
//    Q_CLASSINFO("D-Bus Interface", "com.scorpio.test.value")
public:

    DaemonIpcDbus() {}

public slots:

    int daemonIsNotRunning();
    void showGuide(QString appName);

};

#endif // DAEMONIPCDBUS_H
