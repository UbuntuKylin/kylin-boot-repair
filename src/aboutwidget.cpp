#include "aboutwidget.h"
/************************************************
* 函数名称：
* 功能描述：
* 输出参数：
* 修改日期：2020.12.10
* 修改内容：
*   创建  HZH
*
*************************************************/
AboutWidget::AboutWidget(const StyleWidgetAttribute& swa, QString dialogTitleText, bool isDialog )
    :local_swa(swa)
{
    m_isDialog=isDialog;
    swshadow = new StyleWidgetShadow(swa);
    this->setWindowIcon(QIcon(":/data/guide_repair24.png"));
    this->setWindowTitle(tr("KylinBootRepairAbout"));
    myStyle(swa);
}
/************************************************
* 函数名称：
* 功能描述：
* 输出参数：
* 修改日期：2020.12.10
* 修改内容：
*   创建  HZH
*
*************************************************/
AboutWidget::~AboutWidget()
{
    swshadow->deleteLater();
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
void AboutWidget::WidgetStyleClose()
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
void AboutWidget::myStyle(StyleWidgetAttribute swa)
{
    //窗口设置
    this->setWindowFlags(Qt::FramelessWindowHint);// | Qt::Popup);//无边框
    this->setAttribute(Qt::WA_TranslucentBackground, true);//窗体透明
    this->setFixedSize(swa.w,swa.h);

    QRect availableGeometry = qApp->primaryScreen()->availableGeometry();
    this->move((availableGeometry.width() - this->width())/2 + 2 * this->width(), (availableGeometry.height() - this->height())/2);

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

    QSize smallWidgetSize(30,30);//小按钮大小

    widgetClose =new QPushButton;//关闭按钮
    widgetClose->setObjectName("widgetClose");
    widgetClose->setIconSize(smallWidgetSize);
    widgetClose->setFixedSize(smallWidgetSize);
    connect(widgetClose,&QPushButton::clicked,this,&AboutWidget::WidgetStyleClose);

    //布局
    QHBoxLayout *hlt0=new QHBoxLayout;//右上角按钮内部，水平布局
    hlt0->setMargin(0);
    hlt0->setSpacing(0);
    hlt0->addWidget(widgetClose, 1);

    QHBoxLayout *hlt=new QHBoxLayout;//标题栏内部，水平布局
    hlt->setMargin(0);
    hlt->setSpacing(0);
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

    aboutIcon = new QLabel;
    if(nullptr == aboutIcon)
    {
        qDebug() << "startIcon对象创建失败！";
        return;
    }
    aboutIcon->setStyleSheet("border-image:url(:/data/bootrepair_icon.png);border:0px;");
    aboutIcon->setFixedSize(96,96);

    aboutText = new QLabel;
    if(nullptr == aboutText)
    {
        qDebug() << "startText对象创建失败！";
        return;
    }
    aboutText->setText(tr("Kylin Boot Repair"));//修复计算机引导程序的常见问题
    aboutText->setStyleSheet("font-size:25px;");

    aboutVersion_1 = new QLabel;
    if(nullptr == aboutVersion_1)
    {
        qDebug() << "startText对象创建失败！";
        return;
    }
    aboutVersion_1->setText(tr("Version:"));//修复计算机引导程序的常见问题

    aboutVersion_2 = new QLabel;
    if(nullptr == aboutVersion_2)
    {
        qDebug() << "startText对象创建失败！";
        return;
    }
    aboutVersion_2->setText(tr("1.0.26kord~rc13"));//修复计算机引导程序的常见问题



    QHBoxLayout *hlt_Icon=new QHBoxLayout;
    hlt_Icon->setMargin(0);
    hlt_Icon->setSpacing(0);
    hlt_Icon->addSpacing(162);
    hlt_Icon->addWidget(aboutIcon,1);
    hlt_Icon->addStretch(99);

    QHBoxLayout *hlt_Text=new QHBoxLayout;
    hlt_Text->setMargin(0);
    hlt_Text->setSpacing(0);
    hlt_Text->addSpacing(138);
    hlt_Text->addWidget(aboutText,1);
    hlt_Text->addStretch(99);

    QHBoxLayout *hlt_Ver=new QHBoxLayout;
    hlt_Ver->setMargin(0);
    hlt_Ver->setSpacing(0);
    hlt_Ver->addSpacing(138);
    hlt_Ver->addWidget(aboutVersion_1,1);
    hlt_Ver->addSpacing(5);
    hlt_Ver->addWidget(aboutVersion_2,1);
    hlt_Ver->addStretch(99);

    QVBoxLayout *vlt_body=new QVBoxLayout;
    vlt_body->setMargin(0);
    vlt_body->setSpacing(0);
    vlt_body->addSpacing(17);
    vlt_body->addLayout(hlt_Icon);
    vlt_body->addSpacing(18);
    vlt_body->addLayout(hlt_Text);
    vlt_body->addSpacing(18);
    vlt_body->addLayout(hlt_Ver);
    vlt_body->addStretch(99);

    body->setLayout(vlt_body);

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
void AboutWidget::paintEvent(QPaintEvent *event)//重绘窗口
{
    if(paintOnce)return;
    //设置字体字号
    QFont ft;
    ft.setPixelSize(14);
    if(m_isDialog)
        ft.setFamily(QFontDatabase::applicationFontFamilies(QFontDatabase::addApplicationFont(":/data/PingFang-SC-Semibold-2.ttf")).at(0));//读取字体
    else
        ft.setFamily(QFontDatabase::applicationFontFamilies(QFontDatabase::addApplicationFont(":/data/PingFang-Jian-ChangGuiTi-2.ttf")).at(0));//读取字体

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
void AboutWidget::showOrHide()
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
void AboutWidget::ThemeChooseForWidget(const QString& str)
{

    if("ukui-dark" == str || "ukui-black" == str)
    {

        //样式表stylesheet//测试用border:1px solid red;
        QString bodyStyleSheet="QWidget{background-color:rgba(20, 20, 20, 1);border-bottom-left-radius:"+QString::number(local_swa.radius)+
                                "px;border-bottom-right-radius:"+QString::number(local_swa.radius)+"px;}";
        title->setStyleSheet("QWidget{background-color:rgba(20, 20, 20, 1);border-top-left-radius:"
                                 +QString::number(local_swa.radius)+"px;border-top-right-radius:"+QString::number(local_swa.radius)+"px;}");
        body->setStyleSheet(bodyStyleSheet);


        widgetClose->setStyleSheet("QPushButton{background-color:rgba(255,255,255,0);border-image:url(:/data/close_h.png);border-radius:4px;font-size:14px;}"
                                   "QPushButton:hover{background-color:rgba(240,64,52,1);border-image:url(:/data/close_h.png);border-radius:4px;font-size:14px;}"
                                   "QPushButton:pressed{background-color:rgba(215,51,53,1);border-image:url(:/data/close_p.png);border-radius:4px;font-size:14px;}");
     }
    else
    {

       //样式表stylesheet//测试用border:1px solid red;
       QString bodyStyleSheet="QWidget{background-color:rgba(255,255,255,1);border-bottom-left-radius:"+QString::number(local_swa.radius)+
                               "px;border-bottom-right-radius:"+QString::number(local_swa.radius)+"px;}";
       title->setStyleSheet("QWidget{background-color:rgba(255,255,255,1);border-top-left-radius:"
                                +QString::number(local_swa.radius)+"px;border-top-right-radius:"+QString::number(local_swa.radius)+"px;}");
       body->setStyleSheet(bodyStyleSheet);


       widgetClose->setStyleSheet("QPushButton{background-color:rgba(255,255,255,0);border-image:url(:/data/close_d.png);border-radius:4px;font-size:14px;}"
                                  "QPushButton:hover{background-color:rgba(240,64,52,1);border-image:url(:/data/close_h.png);border-radius:4px;font-size:14px;}"
                                  "QPushButton:pressed{background-color:rgba(215,51,53,1);border-image:url(:/data/close_p.png);border-radius:4px;font-size:14px;}");
    }

}

