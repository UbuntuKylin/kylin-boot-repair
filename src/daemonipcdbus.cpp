/************************************************
* 文件描述: QDbus类
* 待完善:
* 待优化:
* 修改日期：2020.11.04
* 修改内容：
*   创建  HZH
*************************************************/
#include "daemonipcdbus.h"

int DaemonIpcDbus::daemonIsNotRunning()
{
    char service_name[SERVICE_NAME_SIZE];
    memset(service_name, 0, SERVICE_NAME_SIZE);
    snprintf(service_name, SERVICE_NAME_SIZE, "%s_%d",KYLIN_USER_GUIDE_SERVICE,getuid());
    QDBusConnection conn = QDBusConnection::sessionBus();
    if (!conn.isConnected())
        return -1;

    QDBusReply<QString> reply = conn.interface()->call("GetNameOwner", service_name);
    return reply.value() == "";
}

void DaemonIpcDbus::showGuide(QString appName)
{
    qDebug() << Q_FUNC_INFO << appName;
    bool bRet  = false;

    char service_name[SERVICE_NAME_SIZE];
    memset(service_name, 0, SERVICE_NAME_SIZE);
    snprintf(service_name, SERVICE_NAME_SIZE, "%s_%d",KYLIN_USER_GUIDE_SERVICE,getuid());

    qDebug() << "service_name  " << service_name;
    // 用来构造一个在D-Bus上传递的Message
    QDBusMessage m = QDBusMessage::createMethodCall(QString(service_name),KYLIN_USER_GUIDE_PATH,KYLIN_USER_GUIDE_INTERFACE,"showGuide");
    // 给QDBusMessage增加一个参数;
    // 这是一种比较友好的写法，也可以用setArguments来实现
    m << appName;

    // 发送Message
    QDBusMessage response = QDBusConnection::sessionBus().call(m);
    // 判断Method是否被正确返回
    if (response.type()== QDBusMessage::ReplyMessage)
    {
        // QDBusMessage的arguments不仅可以用来存储发送的参数，也用来存储返回值;
//        bRet = response.arguments().at(0).toBool();
    }
    else {
        qDebug()<<"showGuide In fail!\n";
    }

    qDebug()<<"bRet:"<<bRet;
}
