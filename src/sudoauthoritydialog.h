/************************************************
* 文件描述: 密码授权框
* 待完善:
* 待优化:
* 修改日期：2020.11.19
* 修改内容：
*   创建  HZH
*************************************************/
#ifndef SUDOAUTHORITYDIALOG_H
#define SUDOAUTHORITYDIALOG_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QApplication>
#include <QScreen>
#include <QHBoxLayout>
#include <QProcess>
#include <QDebug>
#include <QTimer>

class SudoAuthorityDialog : public QWidget
{
    Q_OBJECT
public:
    explicit SudoAuthorityDialog(QWidget *parent = nullptr);
    void pageChangeForTheme(QString nowThemeStyle);
signals:
    void nopassword();
    void getPassword(QString password);
private:
    void uiInit();
    void uiLocation();
    void btnOk_Clicked();

    uint incorrectTimes = 0;

    QString nomarlCmd = "whoami";
    QString rootCmd   = "sudo -S whoami";

    QWidget     *body       = nullptr ;
    QPushButton *btnCancel  = nullptr;
    QPushButton *btnOk      = nullptr;
    QLineEdit   *dialogKey  = nullptr;
    QLineEdit   *dialogUser = nullptr;
    QLabel      *title      = nullptr;
    QLabel      *tip        = nullptr;
    QLabel      *user       = nullptr;
    QLabel      *result     = nullptr;

    QProcess    *cmdWhoamiBash = nullptr;
    QProcess    *cmdPwdCheckBash = nullptr;

    QString userPassword = "";
    QString userName = "root";

    void readcmdWhoamiBashInfo();
    void readcmdWhoamiBashErrorInfo();

    void readcmdPwdCheckBashInfo();
    void readcmdPwdCheckBashErrorInfo();
};

#endif // SUDOAUTHORITYDIALOG_H
