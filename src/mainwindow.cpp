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
    //单例运行
    checkSingle();

    myStyle();

    initGsetting();

    prepareAction();
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
    delete mycmdFdiskBash;
    pFdiskthread->quit();

    delete mycmdPreRepairBash;
    pPreRepair->quit();

    delete pFdiskthread;
    delete pPreRepair;

    delete stackedWidget;
    delete styleWidget;
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
void MainWindow::myStyle()
{
    //设置外观(有参构造)int style_w, int style_h, bool style_allRadius=1, int style_radius=0, int style_shadow =0,
    //double style_shadowAlpha=0.00, int style_titleHeight=0, int style_itemHeight=0, bool style_middle=true
    StyleWidgetAttribute swa(WINDOWWIDETH,WINDOWHEIGHT,0,WIDGETRADIUS,SHADOWALPHA,SHADOWALPHA,TITLEHEIGHT);
    styleWidget=new StyleWidget(swa,tr("麒麟引导修复"));

    prePage = new PrePage(swa);

    startPage = new StartPage(swa);
    connect(startPage,&StartPage::makeStart,this,&MainWindow::makeStart);

    warningPage = new WarningPage(swa);

    repairPage = new RepairPage(swa);

    repairPage2 = new RepairPage2(swa);

    finishPage = new FinishPage(swa);

    QHBoxLayout *hblayout=new QHBoxLayout(styleWidget->body);
    hblayout->setMargin(0);//控件间距
    hblayout->setSpacing(0);//控件间距

    //内部样式
    stackedWidget =new QStackedWidget;
    stackedWidget->addWidget(prePage);
    stackedWidget->addWidget(startPage);

    //stackedWidget->addWidget(repairPage);
    stackedWidget->addWidget(repairPage2);
    stackedWidget->addWidget(finishPage);
    stackedWidget->addWidget(warningPage);

    //布局
    //QHBoxLayout *hlt =new QHBoxLayout;

    hblayout->addWidget(stackedWidget);

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
void MainWindow::prepareAction()
{
    //硬盘信息获取线程
    qDebug() << "创建fdisk线程";
    mycmdFdiskBash = new FdiskThread();   //创建fdisk线程
    pFdiskthread = new QThread();
    mycmdFdiskBash->moveToThread(pFdiskthread);//将pFdiskthread移动到子线程mycmdFdiskBash中
    connect(pFdiskthread, &QThread::finished, mycmdFdiskBash, &QObject::deleteLater);//挂载
    //将主窗口线程的startFdisk信号和mycmdFdiskBash线程中的startFdisk槽函数连接
    connect(this,&MainWindow::startFdisk,mycmdFdiskBash,&FdiskThread::startFdisk);
    //第一次输入命令后，发现无效，获取管理员密码
    connect(mycmdFdiskBash,&FdiskThread::passwordNoInput,this,&MainWindow::passwordNoInput);
    connect(mycmdFdiskBash,&FdiskThread::mainWindowChangePage,this,&MainWindow::changeToNextPage);

    mycmdPreRepairBash = new PreRepair();   //创建repair线程
    pPreRepair = new QThread();
    mycmdPreRepairBash->moveToThread(pPreRepair);//将pRepairthread移动到子线程mycmdRepairBash中
    connect(pPreRepair, &QThread::finished, mycmdPreRepairBash, &QObject::deleteLater);//挂载
    connect(this,&MainWindow::start_pushButton_clicked,mycmdPreRepairBash,&PreRepair::start_pushButton_clicked);
    connect(mycmdPreRepairBash,&PreRepair::mainWindowChangePage,this,&MainWindow::changeToNextPage);


    pFdiskthread->start();                //启动fdisk线程
    pPreRepair->start();                //启动repair线程

    QString fdiskCmd;
    fdiskCmd = "pkexec sudo -S fdisk -l";    //通过pkexec提权

    emit startFdisk(fdiskCmd);
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
int MainWindow::changePage()
{
    int count = stackedWidget->count();

    int index = stackedWidget->currentIndex();

    ++index;
    if (index >= count)index = 0;
    qDebug() << "当前页面数值为" << index;
    return index;
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
void MainWindow::makeStart()
{
    hardDisklist = mycmdFdiskBash->listOfDevice;
    hardDiskNum  = mycmdFdiskBash->numOfLinuxPartion;

    qDebug() << "Linux系统硬盘分区名称" << hardDisklist;

    qDebug() << "Linux系统硬盘分区个数为：" << hardDiskNum;
    qDebug() << "主线程的makeStart!";
    stackedWidget->setCurrentIndex(changePage());

    start_pushButton_clicked(hardDisklist, hardDiskNum);

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
void MainWindow::changeToNextPage()
{
    qDebug() << "翻到下一页";
    stackedWidget->setCurrentIndex(changePage());
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
void MainWindow::passwordNoInput()
{
    qDebug() << "授权窗口被关闭，主线程窗口关闭！";
    styleWidget->WidgetStyleClose();
    this->close();
}

/************************************************
* 函数名称：单例模式
* 功能描述：检查是否单例运行
* 输入参数：
* 输出参数：
* 修改日期：2020.10.12
* 修改内容：
*   创建  HZH
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
        qDebug()<<"Can't lock single file, kylin-boot-repair is already running!";
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
    qDebug() << "In func initGsetting()";
    if(QGSettings::isSchemaInstalled(FITTHEMEWINDOW))
    {
        qDebug() << "配置文件存在！";
        m_pThemeStyle = new QGSettings(FITTHEMEWINDOW);
        qDebug() << m_pThemeStyle->get("styleName").toString();
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
* 函数名称：主题样式设计
* 功能描述：
* 输入参数：
* 输出参数：
* 修改日期：2020.10.12
* 修改内容：
*   创建  HZH
*
*************************************************/
void MainWindow::setThemeStyle()
{
    QString nowThemeStyle = m_pThemeStyle->get("styleName").toString();
    qDebug() << nowThemeStyle;
    styleWidget->ThemeChooseForWidget(nowThemeStyle);

    prePage->pageChangeForTheme(nowThemeStyle);

}
