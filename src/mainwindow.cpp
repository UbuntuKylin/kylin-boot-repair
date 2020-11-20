/************************************************
* 文件描述: 主线程类，窗口参数设定。线程创建，翻页等功能
*          实现。
* 待完善:
* 待优化:
* 修改日期：2020.10.12
* 修改内容：
*   创建  HZH
*************************************************/
#include "mainwindow.h"

/************************************************
* 函数名称：MainWindow
* 功能描述：构造函数，设置标题图标及标题
* 输入参数：无
* 输出参数：无
* 修改日期：2020.10.12
* 修改内容：
*   创建  HZH
*
*************************************************/
MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    //单例运行检查
    checkSingle();

    //用户权限检查
    cmdWhoamiBash = new QProcess();   //创建QProcess对象并连接信号与槽

    connect(cmdWhoamiBash,&QProcess::readyReadStandardOutput,this,&MainWindow::readcmdWhoamiBashInfo);
    connect(cmdWhoamiBash,&QProcess::readyReadStandardError,this,&MainWindow::readcmdWhoamiBashInfo);

    cmdWhoamiBash->start("bash");

    cmdWhoamiBash->write(rootCmd.toLocal8Bit()  + '\n');

    cmdWhoamiBash->waitForStarted();

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
MainWindow::~MainWindow()
{
    if(mycmdFdiskBash)
    {
        mycmdFdiskBash->deleteLater();
    }

    if(pFdiskthread)
    {
        pFdiskthread->quit();
        pFdiskthread->deleteLater();
    }

    if(mycmdPreRepairBash)
    {
        mycmdPreRepairBash->deleteLater();
    }

    if(pPreRepair)
    {
        pPreRepair->quit();
        pPreRepair->deleteLater();
    }

    if(stackedWidget)
    {
        stackedWidget->deleteLater();
    }

    if(styleWidget)
    {
        styleWidget->deleteLater();
    }
    authorityBox->close();
    delete authorityBox;
    cmdWhoamiBash->deleteLater();
}
/************************************************
* 函数名称：readcmdWhoamiBashInfo
* 功能描述：主线程查看root权限！函数
* 输入参数：无
* 输出参数：
* 修改日期：2020.11.19
* 修改内容：
*   创建  HZH
*
*************************************************/
void MainWindow::readcmdWhoamiBashInfo()
{
    qDebug() << "主线程查看root权限！";
    QString cmdStdOut = QString::fromLocal8Bit(cmdWhoamiBash->readAllStandardOutput());
    QString cmdStdOut_err = QString::fromLocal8Bit(cmdWhoamiBash->readAllStandardError());

    if(cmdStdOut.contains("secure_path"))
    {
        qDebug() << "无管理员密码！";
        hasPassword = false;
    }

    else if(cmdStdOut_err.contains("Sorry") || cmdStdOut_err.contains("对不起"))
    {
        qDebug() << "错误输出！";
        qDebug() << cmdStdOut_err;

        hasPassword = true;
    }

    myStyle();

    initGsetting();
    cmdWhoamiBash->kill();
}
/************************************************
* 函数名称：myStyle
* 功能描述：
* 输出参数：
* 修改日期：2020.10.12
*         2020.11.19
* 修改内容：
*   创建  HZH
*   修改  HZH 加入页数enum定义，增加密码框检查密码流程
*
*************************************************/
void MainWindow::myStyle()
{
    //设置外观(有参构造)int style_w, int style_h, bool style_allRadius=1, int style_radius=0, int style_shadow =0,
    //double style_shadowAlpha=0.00, int style_titleHeight=0, int style_itemHeight=0, bool style_middle=true
    StyleWidgetAttribute swa(WINDOWWIDETH,WINDOWHEIGHT,0,WIDGETRADIUS,SHADOWWIDTH,SHADOWALPHA,TITLEHEIGHT);
    styleWidget=new StyleWidget(swa,tr("麒麟引导修复"));
    connect(styleWidget,&StyleWidget::allClose,this,&MainWindow::closeMainWin);

    prePage = new PrePage(swa);

    startPage = new StartPage(swa);
    connect(startPage,&StartPage::makeStart,this,&MainWindow::makeStart);
    connect(startPage,&StartPage::closeMainWin,this,&MainWindow::closeMainWin);

    warningPage = new WarningPage(swa);
    connect(warningPage,&WarningPage::closeMainWin,this,&MainWindow::closeMainWin);

    repairPage = new RepairPage(swa);

    repairPage2 = new RepairPage2(swa);

    finishPage = new FinishPage(swa);
    connect(finishPage,&FinishPage::shutdownNow,this,&MainWindow::shutdownNow);

    QHBoxLayout *hblayout=new QHBoxLayout(styleWidget->body);
    hblayout->setMargin(0);//控件间距
    hblayout->setSpacing(0);//控件间距

    //内部样式
    stackedWidget =new QStackedWidget;
    stackedWidget->addWidget(prePage);         //prePage为第0页
    stackedWidget->addWidget(startPage);       //startPage为第1页
    stackedWidget->addWidget(repairPage2);     //repairPage2为第2页
    stackedWidget->addWidget(finishPage);      //finishPage为第3页
    stackedWidget->addWidget(warningPage);     //warningPage为第4页
/*
    enum PageIndex
    {
        prePageIndex = 0,
        startPageIndex,
        repairPage2Index,
        finishPageIndex,
        warningPageIndex
    };
*/
    //布局
    //QHBoxLayout *hlt =new QHBoxLayout;

    hblayout->addWidget(stackedWidget);

    authorityBox = new SudoAuthorityDialog();
    connect(authorityBox,&SudoAuthorityDialog::nopassword,this,&MainWindow::passwordNoInput);
    connect(authorityBox,&SudoAuthorityDialog::getPassword,this,&MainWindow::getPassword);

    authorityBox->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog );//无边框
    //authorityBox->setAttribute(Qt::WA_TranslucentBackground, true);//窗体透明
    authorityBox->setWindowTitle("麒麟引导修复授权");
    //authorityBox->setFixedSize(420,270);

    QRect availableGeometry = qApp->primaryScreen()->availableGeometry();
    authorityBox->move((availableGeometry.width() - this->width())/2, (availableGeometry.height() - this->height())/2);
    authorityBox->hide();

    if(true == hasPassword)      //如果检查需要密码，则显示密码弹框，否则直接执行。
    { 
        authorityBox->show();
    }
    else
    {
        getPassword("");
    }

}

/************************************************
* 函数名称：prepareAction
* 功能描述：通过fdisk命令查看电脑硬件信息
* 输出参数：
* 修改日期：2020.10.12
* 修改内容：
*   创建  HZH
*
*************************************************/
void MainWindow::prepareAction()
{
    //硬盘信息获取线程
    qDebug() << "创建fdisk线程";
    mycmdFdiskBash = new FdiskThread(hasPassword,userPassword);   //创建fdisk线程
    pFdiskthread = new QThread();
    mycmdFdiskBash->moveToThread(pFdiskthread);//将pFdiskthread移动到子线程mycmdFdiskBash中
    connect(pFdiskthread, &QThread::finished, mycmdFdiskBash, &QObject::deleteLater);//挂载
    //将主窗口线程的startFdisk信号和mycmdFdiskBash线程中的startFdisk槽函数连接
    connect(this,&MainWindow::startFdisk,mycmdFdiskBash,&FdiskThread::startFdisk);
    connect(mycmdFdiskBash,&FdiskThread::changeToMainPage,this,&MainWindow::changeToMainPage);

    connect(mycmdFdiskBash,&FdiskThread::failAndReturn,this,&MainWindow::failAndReturn);

    mycmdPreRepairBash = new PreRepair(hasPassword,userPassword);   //创建repair线程
    pPreRepair = new QThread();
    mycmdPreRepairBash->moveToThread(pPreRepair);//将pRepairthread移动到子线程mycmdRepairBash中
    connect(pPreRepair, &QThread::finished, mycmdPreRepairBash, &QObject::deleteLater);//挂载
    connect(this,&MainWindow::start_pushButton_clicked,mycmdPreRepairBash,&PreRepair::start_pushButton_clicked);
    connect(mycmdPreRepairBash,&PreRepair::changeToFinishPage,this,&MainWindow::changeToFinishPage);
    connect(mycmdPreRepairBash,&PreRepair::failAndReturn,this,&MainWindow::failAndReturn);

    pFdiskthread->start();                //启动fdisk线程
    pPreRepair->start();                //启动repair线程

    QString fdiskCmd;
    fdiskCmd = "sudo -S fdisk -l";

    emit startFdisk(fdiskCmd);
    styleWidget->widgetClose->setEnabled(false);
    styleWidget->widgetMin->setEnabled(false);
}

/************************************************
* 函数名称：makeStart
* 功能描述：开始修复函数
* 输出参数：
* 修改日期：2020.10.12
* 修改内容：
*   创建  HZH
*
*************************************************/
void MainWindow::makeStart()
{

    hardDisklist = mycmdFdiskBash->listOfDevice;
    hardDiskNum  = mycmdFdiskBash->numOfLinuxPartion;

    qDebug() << "Linux系统硬盘分区名称" << hardDisklist;

    qDebug() << "Linux系统硬盘分区个数为：" << hardDiskNum;
    qDebug() << "主线程的makeStart!";

    stackedWidget->setCurrentIndex(repairPage2Index);
    styleWidget->widgetClose->setEnabled(true);
    styleWidget->widgetMin->setEnabled(true);

    emit start_pushButton_clicked(hardDisklist, hardDiskNum);
    styleWidget->widgetClose->setEnabled(false);

}

/************************************************
* 函数名称：passwordNoInput
* 功能描述：密码输入对话框弹窗没有输入就被关闭
* 输出参数：
* 修改日期：2020.11.07
* 修改内容：
*   创建  HZH
*   修改  HZH 日志输出内容完善
*
*************************************************/
void MainWindow::passwordNoInput()
{
    qDebug() << "fdisk命令出错，程序退出！";
    styleWidget->WidgetStyleClose();
    this->closeMainWin();
}

/************************************************
* 函数名称：getPassword
* 功能描述：从密码框获取到密码
* 输出参数：
* 修改日期：2020.11.19
* 修改内容：
*   创建  HZH
*
*************************************************/
void MainWindow::getPassword(QString str)
{
    if(str.isEmpty())
    {
        qDebug() << "密码为空";
        hasPassword = false;
    }
    else
    {
        hasPassword = true;
        qDebug() << "password:" << str;
        userPassword = str;
        authorityBox->hide();
    }
    prepareAction();
}

/************************************************
* 函数名称：单例模式
* 功能描述：检查是否单例运行
* 输入参数：
* 输出参数：
* 修改日期：2020.11.07
* 修改内容：
*   创建  HZH
*   修改  HZH 日志输出内容完善
*
*************************************************/
void MainWindow::checkSingle()
{
    QStringList homePath = QStandardPaths::standardLocations(QStandardPaths::HomeLocation);
//    QString lockPath = homePath.at(0) + "/.config/kylin-boot-repair";//不支持vnc远程使用
//    int fd = open(lockPath.toUtf8().data(), O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);

    int fd = open(QString(homePath.at(0) + "/.config/kylin-boot-repair%1.lock").arg(getenv("DISPLAY")).toUtf8().data(), O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);

    if (fd < 0) { exit(1); }

    if (lockf(fd, F_TLOCK, 0)) {
        qDebug()<<"单例检查警告——麒麟引导修复工具已经在运行!";
        exit(0);
    }
}

/************************************************
* 函数名称：gsetting初始化
* 功能描述：
* 输入参数：
* 输出参数：
* 修改日期：2020.10.12
* 修改内容：
*   创建  HZH
*
*************************************************/
void MainWindow::initGsetting()
{
    qDebug() << "gsetting开始初始化！";
    if(QGSettings::isSchemaInstalled(FITTHEMEWINDOW))
    {
        qDebug() << "配置文件存在！";
        m_pThemeStyle = new QGSettings(FITTHEMEWINDOW);
        qDebug() << "当前系统主题模式为：" << m_pThemeStyle->get("styleName").toString();
        connect(m_pThemeStyle,&QGSettings::changed,this, [=] (const QString &key)
        {
            if(key == "styleName")
            {

                    setThemeStyle();
            }
        });
    }
    setThemeStyle();
    return;

}

/************************************************
* 函数名称：setThemeStyle
* 功能描述：主题样式设计
* 输入参数：
* 输出参数：
* 修改日期：2020.10.12
*         2020.11.19
* 修改内容：
*   创建  HZH
*   修改  HZH 增加密码框的主题适配
*
*************************************************/
void MainWindow::setThemeStyle()
{
    QString nowThemeStyle = m_pThemeStyle->get("styleName").toString();
    qDebug() << "设置程序主题模式为" << nowThemeStyle;
    styleWidget->ThemeChooseForWidget(nowThemeStyle);

    prePage->pageChangeForTheme(nowThemeStyle);
    startPage->pageChangeForTheme(nowThemeStyle);
    finishPage->pageChangeForTheme(nowThemeStyle);
    warningPage->pageChangeForTheme(nowThemeStyle);

    authorityBox->pageChangeForTheme(nowThemeStyle);

}
/************************************************
* 函数名称：closeMainWin
* 功能描述：关闭主线程槽函数
* 输入参数：
* 输出参数：
* 修改日期：2020.11.07
*         2020.11.19
* 修改内容：
*   创建  HZH
*   修改  HZH  调整关闭策略
*
*************************************************/
void MainWindow::closeMainWin()
{
    qDebug() << "主线程收到关闭信号！";
    //关闭主窗口
    QTimer::singleShot(200, [=](){
        this->~MainWindow();//延迟0.2秒，关闭主窗口
    });
}
/************************************************
* 函数名称：shutdownNow
* 功能描述：关机槽函数
* 输入参数：
* 输出参数：
* 修改日期：2020.11.19
* 修改内容：
*   创建  HZH
*
*************************************************/
void MainWindow::shutdownNow()
{
    qDebug() << "主线程收到关机！";
//    shutDownBash = new QProcess();   //创建QProcess对象并连接信号与槽

//    shutDownBash->start("bash");

//    shutDownBash->write("sudo -S shutdown -r now\n");
//    if(hasPassword)
//    {
//        qDebug() << "有密码！";
//        shutDownBash->write(userPassword.toLocal8Bit() + '\n');
//    }

//    shutDownBash->waitForStarted();
    QProcess::execute("shutdown -r now");
    QApplication::exit();
}
/************************************************
* 函数名称：failAndReturn
* 功能描述：修复报错，主线程槽函数
* 输入参数：无
* 输出参数：
* 修改日期：2020.11.07
* 修改内容：
*   创建  HZH
*
*************************************************/
void MainWindow::failAndReturn()
{
    qDebug() << "主线程收到支线程错误信号！";
    stackedWidget->setCurrentIndex(warningPageIndex);
    styleWidget->widgetClose->setEnabled(true);
    styleWidget->widgetMenuBtn->setEnabled(true);
    styleWidget->widgetMin->setEnabled(true);
    qInstallMessageHandler(nullptr);
}
/************************************************
* 函数名称：changeToMainPage
* 功能描述：翻转至主页槽函数
* 输入参数：无
* 输出参数：
* 修改日期：2020.11.07
*         2020.11.19
* 修改内容：
*   创建  HZH
*   修改  HZH  改用enum代替翻页数字
*
*************************************************/
void MainWindow::changeToMainPage()
{
    stackedWidget->setCurrentIndex(startPageIndex);//翻到开始主页
    styleWidget->widgetClose->setEnabled(true);
    styleWidget->widgetMenuBtn->setEnabled(true);
    styleWidget->widgetMin->setEnabled(true);
}
/************************************************
* 函数名称：changeToFinishPage
* 功能描述：翻转至完成页槽函数
* 输入参数：无
* 输出参数：
* 修改日期：2020.11.07
*         2020.11.19
* 修改内容：
*   创建  HZH
*   修改  HZH  改用enum代替翻页数字
*
*************************************************/
void MainWindow::changeToFinishPage()
{
    qDebug() << "主线程收到修复完成信号！";
    stackedWidget->setCurrentIndex(finishPageIndex);
    styleWidget->widgetClose->setEnabled(true);
    styleWidget->widgetMenuBtn->setEnabled(true);
    styleWidget->widgetMin->setEnabled(true);
}

