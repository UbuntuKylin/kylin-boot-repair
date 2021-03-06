/************************************************
* 文件描述: In User Settings Edit
* 待完善:
* 待优化:
* 修改日期：2020.10.12
* 修改内容：
*   创建  HZH
*************************************************/
#include "stylewidget.h"

/************************************************
* 函数名称：
* 功能描述：
* 输出参数：
* 修改日期：2020.10.12
* 修改内容：
*   创建  HZH
*
*************************************************/
StyleWidget::StyleWidget(StyleWidgetAttribute swa, QString dialogTitleText, bool isDialog )
    :local_swa(swa)
{
    m_pDaemonIpcDbus = new DaemonIpcDbus();
    m_isDialog=isDialog;
    swshadow = new StyleWidgetShadow(swa);
    this->setWindowIcon(QIcon(":/data/guide_repair24.png"));
    this->setWindowTitle(tr("KylinBootRepair"));//麒麟引导修复工具
    myStyle(swa);
    text->setText(dialogTitleText);

    StyleWidgetAttribute tabWin(TABWINDOWWIDETH,TABWINDOWHEIGHT,0,TABWIDGETRADIUS,TABSHADOWWIDTH,TABSHADOWALPHA,TABTITLEHEIGHT);

    tabWinWidget=new TabWidget(tabWin,tr("KylinBootRepair"),false,this);//麒麟引导修复

    tabWinWidget->setObjectName("widgetMenu");
    tabWinWidget->setStyleSheet("StyleWidget #widgetMenu{background-color:rgba(255, 20, 20, 1);border-radius:6px;}");

    tabWinWidget->move(260 , 45);
    tabWinWidget->raise();

    StyleWidgetAttribute aboutWin(ABOUTWINDOWWIDETH,ABOUTWINDOWHEIGHT,0,ABOUTWIDGETRADIUS,ABOUTSHADOWWIDTH,ABOUTSHADOWALPHA,ABOUTTITLEHEIGHT);
    aboutWinWidget=new AboutWidget(aboutWin,tr("KylinBootRepairAbout"));//麒麟引导修复日志

    aboutWinWidget->showOrHide();

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
StyleWidget::~StyleWidget()
{
    swshadow->deleteLater();
    delete aboutWinWidget;
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
void StyleWidget::WidgetStyleClose()
{
    //emit doSomethig();
    emit allClose();
    this->close();
    swshadow->close();
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
void StyleWidget::myStyle(const StyleWidgetAttribute& swa)
{
    //窗口设置
    this->setWindowFlags(Qt::FramelessWindowHint);// | Qt::Popup);//无边框
    this->setAttribute(Qt::WA_TranslucentBackground, true);//窗体透明
    this->setFixedSize(swa.w,swa.h);

    QRect availableGeometry = qApp->primaryScreen()->availableGeometry();
    this->move((availableGeometry.width() - this->width())/2, (availableGeometry.height() - this->height())/2);

    //设置阴影
    QHBoxLayout *hblayout=new QHBoxLayout(swshadow);
    hblayout->setMargin(0);//控件间距
    hblayout->setSpacing(0);//控件间距
    hblayout->addWidget(this);
    swshadow->show();
    //this->show();

    //控件
    title = new QWidget;//标题栏
    title->setMaximumHeight(swa.titleHeight);
    title->setMinimumHeight(swa.titleHeight);
    title->setObjectName("title");

    body = new QWidget;//窗体
    body->setFixedHeight(this->height()-title->height()-swa.shadow*2);
    body->setObjectName("body");

    icon = new QLabel;//图标
    icon->setPixmap(QPixmap::fromImage(QImage(":/data/guide_repair24.png")));
    icon->setFixedSize(22,22);

    text = new QLabel;//标题

    QSize smallWidgetSize(30,30);//小按钮大小

    widgetMin = new QPushButton;//最小化按钮
    widgetMin->setObjectName("widgetMin");
    widgetMin->setIconSize(smallWidgetSize);
    widgetMin->setFixedSize(smallWidgetSize);
    connect(widgetMin,&QPushButton::clicked,this,[=]{
        swshadow->setWindowState(Qt::WindowMinimized);
    });

    widgetClose = new QPushButton;//关闭按钮
    widgetClose->setObjectName("widgetClose");
    widgetClose->setIconSize(smallWidgetSize);
    widgetClose->setFixedSize(smallWidgetSize);
    connect(widgetClose,&QPushButton::clicked,this,&StyleWidget::WidgetStyleClose);

    widgetMenu = new QPushButton;
    widgetMenu->setObjectName("widgetMenu");
    widgetMenu->setIconSize(smallWidgetSize);
    widgetMenu->setFixedSize(smallWidgetSize);

    styleMenu = new QMenu();
    QList<QAction *> actions ;
    actionHelp = new QAction(styleMenu);
    actionHelp->setText(tr("Help"));
    actionAbout = new QAction(styleMenu);
    actionAbout->setText(tr("About"));
    actions << actionHelp << actionAbout;
    styleMenu->addActions(actions);
    widgetMenu->setMenu(styleMenu);

    connect(styleMenu,&QMenu::triggered,this,&StyleWidget::trigerMenu);

    //布局
    QHBoxLayout *hlt0=new QHBoxLayout;//右上角按钮内部，水平布局
    hlt0->setMargin(0);
    hlt0->setSpacing(0);
    hlt0->addWidget(widgetMenu, 1);
    hlt0->addSpacing(4);
    hlt0->addWidget(widgetMin, 1);
    hlt0->addSpacing(4);
    hlt0->addWidget(widgetClose, 1);

    QHBoxLayout *hlt=new QHBoxLayout;//标题栏内部，水平布局
    hlt->setMargin(0);
    hlt->setSpacing(0);
    hlt->addSpacing(16);
    hlt->addWidget(icon,1);
    hlt->addSpacing(8);
    hlt->addWidget(text,1);
    hlt->addStretch(99);
    hlt->addLayout(hlt0,1);
    hlt->addSpacing(8);

    QVBoxLayout *vlt_temp=new QVBoxLayout;//标题栏内部，水平布局
    vlt_temp->setMargin(0);
    vlt_temp->setSpacing(0);
    vlt_temp->addSpacing(6);
    vlt_temp->addLayout(hlt,1);
    vlt_temp->addStretch(99);

    title->setLayout(vlt_temp);

    QHBoxLayout *hlt2=new QHBoxLayout;//标题栏外部
    hlt2->setMargin(0);
    hlt2->setSpacing(0);
    hlt2->addSpacing(swa.shadow);
    hlt2->addWidget(title);
    hlt2->addSpacing(swa.shadow);


    QHBoxLayout *hlt3=new QHBoxLayout;//窗体
    hlt3->setMargin(0);
    hlt3->setSpacing(0);
    hlt3->addSpacing(swa.shadow);
    hlt3->addWidget(body);
    hlt3->addSpacing(swa.shadow);

    QVBoxLayout *vl=new QVBoxLayout;//总体
    vl->setMargin(0);
    vl->setSpacing(0);
    vl->addSpacing(swa.shadow);
    vl->addLayout(hlt2);
    vl->addLayout(hlt3);
    vl->addStretch(99);
    vl->addSpacing(swa.shadow);
    this->setLayout(vl);

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
void StyleWidget::paintEvent(QPaintEvent *event)//重绘窗口
{
    if(paintOnce)return;
    //设置字体字号
    QFont ft;
    ft.setPixelSize(14);
    if(m_isDialog)
        ft.setFamily(QFontDatabase::applicationFontFamilies(QFontDatabase::addApplicationFont(":/data/PingFang-SC-Semibold-2.ttf")).at(0));//读取字体
    else
        ft.setFamily(QFontDatabase::applicationFontFamilies(QFontDatabase::addApplicationFont(":/data/PingFang-Jian-ChangGuiTi-2.ttf")).at(0));//读取字体
    text->setFont(ft);
    paintOnce=true;
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
void StyleWidget::showOrHide()
{
    if(this->isHidden())
    {
        swshadow->show();
        this->show();
    }
    else
    {
        swshadow->hide();
        this->hide();
    }
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
void StyleWidget::ThemeChooseForWidget(const QString& str)
{
    if("" == str)
    {
        qDebug() << "获取主题信息失败！";
        return;
    }

    tabWinWidget->ThemeChooseForWidget(str);
    aboutWinWidget->ThemeChooseForWidget(str);

    if("ukui-dark" == str || "ukui-black" == str)
    {
        text->setStyleSheet("rgba(255, 255, 255, 0.85);");

        //样式表stylesheet//测试用border:1px solid red;
        QString bodyStyleSheet="StyleWidget #body{background-color:rgba(20, 20, 20, 1);border-bottom-left-radius:"+QString::number(local_swa.radius)+
                                "px;border-bottom-right-radius:"+QString::number(local_swa.radius)+"px;}";
        title->setStyleSheet("StyleWidget #title{background-color:rgba(20, 20, 20, 1);border-top-left-radius:"
                                 +QString::number(local_swa.radius)+"px;border-top-right-radius:"+QString::number(local_swa.radius)+"px;}");
        body->setStyleSheet(bodyStyleSheet);


        widgetMin->setStyleSheet("StyleWidget #widgetMin{background-color:rgba(255,255,255,0);border-image:url(:/data/min_h.png);border-radius:4px;font-size:14px;}"
                                 "StyleWidget #widgetMin:hover{background-color:rgba(108, 142, 235, 1);border-image:url(:/data/min_h.png);border-radius:4px;font-size:14px;}"
                                 "StyleWidget #widgetMin:pressed{background-color:rgba(50, 88, 202, 1);border-image:url(:/data/min_h.png);border-radius:4px;font-size:14px;}");
        widgetClose->setStyleSheet("StyleWidget #widgetClose{background-color:rgba(255,255,255,0);border-image:url(:/data/close_h.png);border-radius:4px;font-size:14px;}"
                                   "StyleWidget #widgetClose:hover{background-color:rgba(240,64,52,1);border-image:url(:/data/close_h.png);border-radius:4px;font-size:14px;}"
                                   "StyleWidget #widgetClose:pressed{background-color:rgba(215,51,53,1);border-image:url(:/data/close_p.png);border-radius:4px;font-size:14px;}");
        widgetMenu->setStyleSheet("StyleWidget #widgetMenu{background-color:rgba(255,255,255,0);border-image:url(:/data/menu_h.png);border-radius:4px;}"
                                  "StyleWidget #widgetMenu:hover{background-color:rgba(0,0,0,0.04);border-image:url(:/data/menu_h.png);border-radius:4px;}"
                                  "StyleWidget #widgetMenu:pressed{background-color:rgba(0,0,0,0.08);border-image:url(:/data/menu_h.png);border-radius:4px;}"
                                 "StyleWidget #widgetMenu::menu-indicator{image:None;}");
    }
    else
    {
       text->setStyleSheet("rgba(0, 0, 0, 0.85);");

       //样式表stylesheet//测试用border:1px solid red;
       QString bodyStyleSheet="StyleWidget #body{background-color:rgba(255,255,255,1);border-bottom-left-radius:"+QString::number(local_swa.radius)+
                               "px;border-bottom-right-radius:"+QString::number(local_swa.radius)+"px;}";
       title->setStyleSheet("StyleWidget #title{background-color:rgba(255,255,255,1);border-top-left-radius:"
                                +QString::number(local_swa.radius)+"px;border-top-right-radius:"+QString::number(local_swa.radius)+"px;}");
       body->setStyleSheet(bodyStyleSheet);


       widgetMin->setStyleSheet("StyleWidget #widgetMin{background-color:rgba(255,255,255,0);border-image:url(:/data/min_d.png);border-radius:4px;font-size:14px;}"
                                "StyleWidget #widgetMin:hover{background-color:rgba(108, 142, 235, 1);border-image:url(:/data/min_h.png);border-radius:4px;font-size:14px;}"
                                "StyleWidget #widgetMin:pressed{background-color:rgba(50, 88, 202, 1);border-image:url(:/data/min_h.png);border-radius:4px;font-size:14px;}");
       widgetClose->setStyleSheet("StyleWidget #widgetClose{background-color:rgba(255,255,255,0);border-image:url(:/data/close_d.png);border-radius:4px;font-size:14px;}"
                                  "StyleWidget #widgetClose:hover{background-color:rgba(240,64,52,1);border-image:url(:/data/close_h.png);border-radius:4px;font-size:14px;}"
                                  "StyleWidget #widgetClose:pressed{background-color:rgba(215,51,53,1);border-image:url(:/data/close_p.png);border-radius:4px;font-size:14px;}");
       widgetMenu->setStyleSheet("StyleWidget #widgetMenu{background-color:rgba(255,255,255,0);border-image:url(:/data/menu_d.png);border-radius:4px;}"
                                 "StyleWidget #widgetMenu:hover{background-color:rgba(0,0,0,0.04);border-image:url(:/data/menu_d.png);border-radius:4px;}"
                                 "StyleWidget #widgetMenu:pressed{background-color:rgba(0,0,0,0.08);border-image:url(:/data/menu_d.png);border-radius:4px;}"
                                "StyleWidget #widgetMenu::menu-indicator{image:None;}");
    }

}
void StyleWidget::widgetMenuPopUp()
{
    tabWinWidget->showOrHide();
}

/************************************************
* 函数名称：keyPressEvent
* 功能描述：F1键打开用户手册对应页
* 输入参数：QKeyEvent *event键盘事件
* 输出参数：
* 修改日期：2020.12.08
* 修改内容：
*   创建  HZH
*
*************************************************/
void StyleWidget::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_F1)
    {
        if(!m_pDaemonIpcDbus->daemonIsNotRunning()){
            m_pDaemonIpcDbus->showGuide("");
        }
    }
}

void StyleWidget::trigerMenu(QAction *act)
{
    if(tr("Help") == act->text())
    {
        qDebug() << "Help";
        if(!m_pDaemonIpcDbus->daemonIsNotRunning())
        {
            m_pDaemonIpcDbus->showGuide("");
        }
    }
    else if(tr("About") == act->text())
    {
        qDebug() << "About";
        aboutWinWidget->showOrHide();
    }
}
