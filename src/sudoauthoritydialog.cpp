/************************************************
* 文件描述: 密码授权框
* 待完善:
* 待优化:
* 修改日期：2020.11.19
* 修改内容：
*   创建  HZH
*************************************************/
#include "sudoauthoritydialog.h"
/************************************************
* 函数名称：
* 功能描述：构造函数
* 输出参数：
* 修改日期：2020.11.19
* 修改内容：
*   创建  HZH
*
*************************************************/
SudoAuthorityDialog::SudoAuthorityDialog(QWidget *parent) : QWidget(parent)
{
    uiInit();
    uiLocation();
    qDebug() << "开始用whoami命令获取信息" ;

    incorrectTimes = 0;

    cmdWhoamiBash = new QProcess();   //创建QProcess对象并连接信号与槽

    connect(cmdWhoamiBash,&QProcess::readyReadStandardOutput,this,&SudoAuthorityDialog::readcmdWhoamiBashInfo);

    cmdWhoamiBash->start("bash");

    cmdWhoamiBash->write(nomarlCmd.toLocal8Bit() + '\n');

    cmdWhoamiBash->waitForStarted();
}
/************************************************
* 函数名称：
* 功能描述：ui组件初始化
* 输出参数：
* 修改日期：2020.11.19
* 修改内容：
*   创建  HZH
*
*************************************************/
void SudoAuthorityDialog::uiInit()
{
    this->setWindowIcon(QIcon(":/data/guide_repair24.png"));
    this->setWindowTitle(tr("麒麟引导修复工具"));

    body = new QWidget(this);
    body->setFixedSize(420,270);
    body->setObjectName("body");

    title = new QLabel;
    title->setFixedSize(288,25);
    title->setText(tr("执行此次操作需要验证管理员权限。"));
    title->setObjectName("title");

    tip = new QLabel;
    tip->setFixedSize(210,20);
    tip->setText(tr("输入管理员密码以允许此次操作。"));
    tip->setObjectName("tip");

    result = new QLabel;
    result->setFixedSize(156,20);
    result->setText(tr(""));
    result->setAlignment(Qt::AlignLeft);
    result->setAlignment(Qt::AlignVCenter);
    result->setObjectName("result");

    dialogUser = new QLineEdit;
    dialogUser->setText(tr(""));
    dialogUser->setFixedSize(356,36);
    dialogUser->setObjectName("dialogUser");
    dialogUser->setEnabled(false);

    user = new QLabel(this);
    user->setFixedSize(350,20);
    user->setText(tr(""));
    user->setObjectName("user");

    dialogKey = new QLineEdit;
    dialogKey->setFixedSize(356,36);
    dialogKey->setObjectName("dialogKey");
    dialogKey->setPlaceholderText(tr("请输入密码"));
    dialogKey->setEchoMode(QLineEdit::Password);
    connect(dialogKey,&QLineEdit::textChanged,this,[=]{
        result->setText(tr(""));
    });

    btnCancel = new QPushButton;
    btnCancel->setText(tr("取消"));
    btnCancel->setFixedSize(120,36);
    btnCancel->setObjectName("btnCancel");
    connect(btnCancel,&QPushButton::clicked,this,[=]{
        emit nopassword();
    });

    btnOk = new QPushButton;
    btnOk->setText(tr("授权"));
    btnOk->setFixedSize(120,36);
    btnOk->setObjectName("btnOk");
    connect(btnOk,&QPushButton::clicked,this,[=]{
        btnOk_Clicked();
    });

}
/************************************************
* 函数名称：
* 功能描述：ui布局
* 输出参数：
* 修改日期：2020.11.19
* 修改内容：
*   创建  HZH
*
*************************************************/
void SudoAuthorityDialog::uiLocation()
{
    QHBoxLayout *hlt_title=new QHBoxLayout;
    hlt_title->setMargin(0);
    hlt_title->setSpacing(0);
    hlt_title->addSpacing(32);
    hlt_title->addWidget(title,1);
    hlt_title->addStretch(99);

    QHBoxLayout *hlt_tip=new QHBoxLayout;
    hlt_tip->setMargin(0);
    hlt_tip->setSpacing(0);
    hlt_tip->addSpacing(32);
    hlt_tip->addWidget(tip,1);
    hlt_tip->addStretch(99);

    QHBoxLayout *hlt_User=new QHBoxLayout;
    hlt_User->setMargin(0);
    hlt_User->setSpacing(0);
    hlt_User->addSpacing(32);
    hlt_User->addWidget(dialogUser,1);
    hlt_User->addStretch(99);

    QHBoxLayout *hlt_Key=new QHBoxLayout;
    hlt_Key->setMargin(0);
    hlt_Key->setSpacing(0);
    hlt_Key->addSpacing(32);
    hlt_Key->addWidget(dialogKey,1);
    hlt_Key->addStretch(99);

    QHBoxLayout *hlt_res=new QHBoxLayout;
    hlt_res->setMargin(0);
    hlt_res->setSpacing(0);
    hlt_res->addSpacing(40);
    hlt_res->addWidget(result,1);
    hlt_res->addStretch(99);

    QHBoxLayout *hlt_btn=new QHBoxLayout;
    hlt_btn->setMargin(0);
    hlt_btn->setSpacing(0);
    hlt_btn->addSpacing(132);
    hlt_btn->addWidget(btnCancel);
    hlt_btn->addSpacing(16);
    hlt_btn->addWidget(btnOk);
    hlt_btn->addStretch(99);

    QVBoxLayout *vlt_all=new QVBoxLayout;
    vlt_all->setMargin(0);
    vlt_all->setSpacing(0);
    vlt_all->addSpacing(32);
    vlt_all->addLayout(hlt_title);
    vlt_all->addSpacing(16);
    vlt_all->addLayout(hlt_tip);
    vlt_all->addSpacing(8);
    vlt_all->addLayout(hlt_User);
    vlt_all->addSpacing(8);
    vlt_all->addLayout(hlt_Key);
    vlt_all->addSpacing(3);
    vlt_all->addLayout(hlt_res);
    vlt_all->addSpacing(1);
    vlt_all->addLayout(hlt_btn);
    vlt_all->addSpacing(29);

    body->setLayout(vlt_all);

    user->move(40,109);

    this->hide();
}
/************************************************
* 函数名称：
* 功能描述：确认密码按下槽函数
* 输出参数：
* 修改日期：2020.11.19
* 修改内容：
*   创建  HZH
*
*************************************************/
void SudoAuthorityDialog::btnOk_Clicked()
{
    qDebug() << "开始用whoami命令获取信息" ;
    result->setText(tr(""));
    userPassword = dialogKey->text();
    if(userPassword.isEmpty())
    {
        qDebug() << "请输入密码！！！";
        result->setText(tr("请输入密码！"));
        return;
    }

    cmdPwdCheckBash = new QProcess();   //创建QProcess对象并连接信号与槽

    connect(cmdPwdCheckBash,&QProcess::readyReadStandardOutput,this,&SudoAuthorityDialog::readcmdPwdCheckBashInfo);
    connect(cmdPwdCheckBash,&QProcess::readyReadStandardError,this,&SudoAuthorityDialog::readcmdPwdCheckBashInfo);


    QString str_temp = rootCmd;

    qDebug() << str_temp;
    qDebug() << userPassword;
    cmdPwdCheckBash->start("bash");

    cmdPwdCheckBash->write(str_temp.toLocal8Bit() + '\n');
    cmdPwdCheckBash->write(userPassword.toLocal8Bit() + '\n');

    cmdPwdCheckBash->waitForStarted();

    btnOk->setEnabled(false);
    dialogKey->setEnabled(false);
}

/************************************************
* 函数名称：readcmdWhoamiBashInfo()
* 功能描述：读取标准输出
* 输出参数：
* 修改日期：2020.11.19
* 修改内容：
*   创建  HZH
*
*************************************************/
void SudoAuthorityDialog::readcmdWhoamiBashInfo()
{
    QString cmdStdOut = QString::fromLocal8Bit(cmdWhoamiBash->readAllStandardOutput());
    if(!cmdStdOut.isEmpty() ){
        qDebug() << cmdStdOut;
        user->setText(cmdStdOut);
    }
}
/************************************************
* 函数名称：readcmdPwdCheckBashInfo()
* 功能描述：检查密码是否正确
* 输出参数：
* 修改日期：2020.11.19
* 修改内容：
*   创建  HZH
*
*************************************************/
void SudoAuthorityDialog::readcmdPwdCheckBashInfo()
{
    QByteArray cmdStdOut = cmdPwdCheckBash->readAllStandardOutput();
    QByteArray cmdStdOutErr = cmdPwdCheckBash->readAllStandardError();
    if(!cmdStdOut.isEmpty() )
    {
        qDebug() << QString::fromLocal8Bit(cmdStdOut);
        QString output = QString::fromLocal8Bit(cmdStdOut);
        if(output.contains("root"))
        {
            qDebug() << "密码输入正确";
            result->setText(tr("密码正确！"));
            emit getPassword(userPassword);
        }
    }
    if(!cmdStdOutErr.isEmpty())
    {
        qDebug() << QString::fromLocal8Bit(cmdStdOutErr);
        QString err_output = QString::fromLocal8Bit(cmdStdOutErr);
        if(err_output.contains("Sorry") || err_output.contains("对不起"))
        {
            incorrectTimes++;
            if(incorrectTimes == 3)
            {
                qDebug() << "密码输入错误3次";
                result->setText(tr("密码错误！30s后再试！"));
                //输入错误密码后，等待几秒，防止用户一直点。
                QTimer::singleShot(30000, [=](){
                    btnOk->setEnabled(true);
                    dialogKey->setEnabled(true);
                    result->setText(tr("请输入密码！"));
                });
                incorrectTimes = 0;
            }
            else
            {
                qDebug() << "密码输入错误";
                result->setText(tr("密码错误！"));
                btnOk->setEnabled(true);
                dialogKey->setEnabled(true);
                QTimer::singleShot(2000, [=](){
                    result->setText(tr("请输入密码！"));
                });
            }
        }
        else if(err_output.contains("sudoers"))
        {
            qDebug() << "用户无权限";
            result->setText(tr("该用户无管理员权限！"));
            btnOk->setEnabled(true);
            dialogKey->setEnabled(true);
            QTimer::singleShot(2000, [=](){
                result->setText(tr("请切换管理员用户！"));
            });
        }


    }
}
/************************************************
* 函数名称：pageChangeForTheme
* 功能描述：主题样式适配
* 输出参数：
* 修改日期：2020.11.19
* 修改内容：
*   创建  HZH
*
*************************************************/
void SudoAuthorityDialog::pageChangeForTheme(QString nowThemeStyle)
{
    qDebug() << nowThemeStyle;
    if("ukui-dark" == nowThemeStyle || "ukui-black" == nowThemeStyle)
    {
        title->setStyleSheet("color:rgba(255, 255, 255, 0.85);font-size:18px;");
        tip->setStyleSheet("color:rgba(255, 255, 255, 0.85);font-size:14px;");
        result->setStyleSheet("color:rgba(255, 255, 255, 0.85);font-size:14px;");
        //dialogUser->setStyleSheet("background:rgba(20, 20, 20, 1);color:rgba(255, 255, 255, 1));font-size:14px;");
        user->setStyleSheet("color:rgba(255, 255, 255, 1));font-size:14px;");
        dialogKey->setStyleSheet("color:rgba(255, 255, 255, 0.85);font-size:14px;");
        btnCancel->setStyleSheet("QPushButton#btnCancel{background:rgba(20, 20, 20, 1);font-size:14px;color:rgba(255, 255, 255, 0.85);}"
                                   "QPushButton#btnCancel:hover{background:rgba(62, 108, 229, 1);font-size:14px;color:rgba(255, 255, 255, 0.85);}"
                                   "QPushButton#btnCancel:pressed{background:rgba(50, 88, 202, 1);font-size:14px;color:rgba(255, 255, 255, 0.85);}");
        btnOk->setStyleSheet("QPushButton#btnOk{background:rgba(20, 20, 20, 1);font-size:14px;color:rgba(255, 255, 255, 0.85);}"
                                   "QPushButton#btnOk:hover{background:rgba(62, 108, 229, 1);font-size:14px;color:rgba(255, 255, 255, 0.85);}"
                                   "QPushButton#btnOk:pressed{background:rgba(50, 88, 202, 1);font-size:14px;color:rgba(255, 255, 255, 0.85);}");
        //body->setStyleSheet("QWidget #body{background:rgba(20, 20, 20, 1);border-radius:12px;}");
    }
    else
    {
        title->setStyleSheet("color:rgba(0, 0, 0, 1);font-size:18px;");
        tip->setStyleSheet("color:rgba(0, 0, 0, 1);font-size:14px;");
        result->setStyleSheet("color:rgba(0, 0, 0, 1);font-size:14px;");
        dialogUser->setStyleSheet("color:rgba(0, 0, 0, 1);font-size:14px;");
        dialogKey->setStyleSheet("color:rgba(0, 0, 0, 1);font-size:14px;");
        btnCancel->setStyleSheet("QPushButton#btnCancel{background:rgba(221, 223, 231, 1);font-size:14px;color:rgba(0, 0, 0, 1);}"
                                   "QPushButton#btnCancel:hover{background:rgba(221, 223, 231, 1);font-size:14px;color:rgba(0, 0, 0, 1);}"
                                   "QPushButton#btnCancel:pressed{background:rgba(221, 223, 231, 1);font-size:14px;color:rgba(0, 0, 0, 1);}");
        btnOk->setStyleSheet("QPushButton#btnOk{background:rgba(221, 223, 231, 1);font-size:14px;color:rgba(0, 0, 0, 1);}"
                                   "QPushButton#btnOk:hover{background:rgba(221, 223, 231, 1);font-size:14px;color:rgba(0, 0, 0, 1);}"
                                   "QPushButton#btnOk:pressed{background:rgba(221, 223, 231, 1);font-size:14px;color:rgba(0, 0, 0, 1);}");
        //body->setStyleSheet("QWidget #body{background:rgba(221, 223, 231, 1);border-radius:12px;}");
    }
}

