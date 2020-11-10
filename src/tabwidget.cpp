/************************************************
* 文件描述: In User Settings Edit
* 待完善:
* 待优化:
* 修改日期：2020.10.12
* 修改内容：
*   创建  HZH
*************************************************/
#include "tabwidget.h"


/************************************************
* 函数名称：
* 功能描述：
* 输出参数：
* 修改日期：2020.10.12
* 修改内容：
*   创建  HZH
*
*************************************************/
TabWidget::TabWidget(StyleWidgetAttribute swa, QString dialogTitleText, bool isDialog,QWidget *parent) : QWidget(parent)
{
    local_swa = swa;
    m_isDialog=isDialog;
    swshadow = new TabMenuShadow(swa,this);
    //swshadow->setParent(this);
    swshadow->show();
    //myStyle(swa);
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
TabWidget::~TabWidget()
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
void TabWidget::WidgetStyleClose()
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
void TabWidget::myStyle(StyleWidgetAttribute swa)
{
    //窗口设置
    this->setWindowFlags(Qt::FramelessWindowHint);//无边框
    this->setAttribute(Qt::WA_TranslucentBackground, true);//窗体透明
    this->setFixedSize(swa.w,swa.h);

//    QRect availableGeometry = qApp->primaryScreen()->availableGeometry();
//    //this->move((availableGeometry.width() - this->width())/2, (availableGeometry.height() - this->height())/2);

    //设置阴影
    QHBoxLayout *hblayout=new QHBoxLayout(swshadow);
    hblayout->setMargin(0);//控件间距
    hblayout->setSpacing(0);//控件间距
    hblayout->addWidget(this);
    swshadow->show();

    //控件
//    title = new QWidget;//标题栏
//    title->setMaximumHeight(42);
//    title->setMinimumHeight(42);
//    title->setObjectName("title");


//    body = new QWidget;//窗体
//    body->setFixedHeight(this->height()-title->height()-swa.shadow*2);
//    body->setObjectName("body");

//    QSize smallWidgetSize(30,30);//小按钮大小

//    widgetMin =new QPushButton(this);//最小化按钮
//    widgetMin->setObjectName("widgetMin");
//    widgetMin->setIconSize(smallWidgetSize);
//    widgetMin->setFixedSize(smallWidgetSize);
//    connect(widgetMin,&QPushButton::clicked,this,[=]{this->setWindowState(Qt::WindowMinimized);});

//    widgetClose =new QPushButton(this);//关闭按钮
//    widgetClose->setObjectName("widgetClose");
//    widgetClose->setIconSize(smallWidgetSize);
//    widgetClose->setFixedSize(smallWidgetSize);
//    connect(widgetClose,&QPushButton::clicked,this,&TabWidget::WidgetStyleClose);

//    //布局
//    QHBoxLayout *hlt0=new QHBoxLayout;//右上角按钮内部，水平布局
//    hlt0->setMargin(0);
//    hlt0->setSpacing(0);
//    hlt0->addWidget(widgetMin, 1);

////    QVBoxLayout *vlt0=new QVBoxLayout;//右上角按钮外部，垂直布局
////    vlt0->setMargin(0);
////    vlt0->setSpacing(0);
////    vlt0->addSpacing(6);
////    vlt0->addLayout(hlt0);
////    vlt0->addSpacing(14);

//    QHBoxLayout *hlt=new QHBoxLayout;//标题栏内部，水平布局
//    hlt->setMargin(0);
//    hlt->setSpacing(0);
//    hlt->addStretch(99);
//    hlt->addLayout(hlt0,1);
//    hlt->addStretch(99);

//    QVBoxLayout *vlt_temp=new QVBoxLayout;//标题栏内部，水平布局
//    vlt_temp->setMargin(0);
//    vlt_temp->setSpacing(0);
//    vlt_temp->addSpacing(6);
//    vlt_temp->addLayout(hlt,1);
//    vlt_temp->addStretch(99);

//    title->setLayout(vlt_temp);

//    QHBoxLayout *hlt2=new QHBoxLayout;//标题栏外部
//    hlt2->setMargin(0);
//    hlt2->setSpacing(0);
//    hlt2->addSpacing(swa.shadow);
//    hlt2->addWidget(title);
//    hlt2->addSpacing(swa.shadow);

//    QHBoxLayout *hlt8=new QHBoxLayout;//右上角按钮内部，水平布局
//    hlt8->setMargin(0);
//    hlt8->setSpacing(0);
//    hlt8->addWidget(widgetClose, 1);

//    body->setLayout(hlt8);

//    QHBoxLayout *hlt3=new QHBoxLayout;//窗体
//    hlt3->setMargin(0);
//    hlt3->setSpacing(0);
//    hlt3->addSpacing(swa.shadow);
//    hlt3->addWidget(body);
//    hlt3->addSpacing(swa.shadow);

//    QVBoxLayout *vl=new QVBoxLayout;//总体
//    vl->setMargin(0);
//    vl->setSpacing(0);
//    vl->addSpacing(swa.shadow);
//    vl->addLayout(hlt2);
//    vl->addLayout(hlt3);
//    vl->addStretch(99);
//    vl->addSpacing(swa.shadow);
//    this->setLayout(vl);

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
void TabWidget::paintEvent(QPaintEvent *event)//重绘窗口
{
    if(paintOnce)return;
    //设置字体字号
    QFont ft;
    ft.setPixelSize(14);
    if(m_isDialog)
        ft.setFamily(QFontDatabase::applicationFontFamilies(QFontDatabase::addApplicationFont(":/data/PingFang-SC-Semibold-2.ttf")).at(0));//读取字体
    else
        ft.setFamily(QFontDatabase::applicationFontFamilies(QFontDatabase::addApplicationFont(":/data/PingFang-Jian-ChangGuiTi-2.ttf")).at(0));//读取字体
    //text->setFont(ft);
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
void TabWidget::showOrHide()
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
void TabWidget::ThemeChooseForWidget(QString str)
{
    qDebug() << str;

    if("ukui-dark" == str || "ukui-black" == str)
    {
        //样式表stylesheet//测试用border:1px solid red;
        //QString bodyStyleSheet="QWidget{background-color:rgba(20, 20, 20, 1);border-bottom-left-radius:6px;border-bottom-right-radius:6px;}";
//        title->setStyleSheet("QWidget{background-color:rgba(20, 20, 20, 1);border-top-left-radius:"
//                                 +QString::number(local_swa.radius)+"px;border-top-right-radius:"+QString::number(local_swa.radius)+"px;}");
        //body->setStyleSheet("QWidget{background-color:rgba(20, 20, 20, 1);border-bottom-left-radius:6px;border-bottom-right-radius:6px;}");


//        widgetMin->setStyleSheet("QPushButton{background-color:rgba(255,255,255,0);border-image:url(:/data/min_h.png);border-radius:4px;}"
//                                 "QPushButton:hover{background-color:rgba(108, 142, 235, 1);border-image:url(:/data/min_h.png);border-radius:4px;}"
//                                 "QPushButton:pressed{background-color:rgba(50, 88, 202, 1);border-image:url(:/data/min_h.png);border-radius:4px;}");
//        widgetClose->setStyleSheet("QPushButton{background-color:rgba(255,255,255,0);border-image:url(:/data/close_h.png);border-radius:4px;}"
//                                   "QPushButton:hover{background-color:rgba(240,64,52,1);border-image:url(:/data/close_h.png);border-radius:4px;}"
//                                   "QPushButton:pressed{background-color:rgba(215,51,53,1);border-image:url(:/data/close_p.png);border-radius:4px;}");

    }
    else
    {
       //样式表stylesheet//测试用border:1px solid red;
       //QString bodyStyleSheet="QWidget{background-color:rgba(255,255,255,1);border-bottom-left-radius:6px;border-bottom-right-radius:6px;}";
//       title->setStyleSheet("QWidget{background-color:rgba(255,255,255,1);border-top-left-radius:"
//                                +QString::number(local_swa.radius)+"px;border-top-right-radius:"+QString::number(local_swa.radius)+"px;}");
       //body->setStyleSheet("{background-color:rgba(255,255,255,1);border-bottom-left-radius:6px;border-bottom-right-radius:6px;}");


//       widgetMin->setStyleSheet("QPushButton{background-color:rgba(255,255,255,0);border-image:url(:/data/min_d.png);border-radius:4px;}"
//                                "QPushButton:hover{background-color:rgba(108, 142, 235, 1);border-image:url(:/data/min_h.png);border-radius:4px;}"
//                                "QPushButton:pressed{background-color:rgba(50, 88, 202, 1);border-image:url(:/data/min_h.png);border-radius:4px;}");
//       widgetClose->setStyleSheet("QPushButton{background-color:rgba(255,255,255,0);border-image:url(:/data/close_d.png);border-radius:4px;}"
//                                  "QPushButton:hover{background-color:rgba(240,64,52,1);border-image:url(:/data/close_h.png);border-radius:4px;}"
//                                  "QPushButton:pressed{background-color:rgba(215,51,53,1);border-image:url(:/data/close_p.png);border-radius:4px;}");

    }

}

void TabWidget::enterEvent(QEvent *event)
{
    qDebug() << "!!!!!!!!!!!!!!!!!!!!!";
    qDebug() << "!!!!!!enterEvent!!!!!";
    qDebug() << "!!!!!!!!!!!!!!!!!!!!!";
    moveInFlag = true;
    //QWidget::mouseMoveEvent(event);
}

void TabWidget::leaveEvent(QEvent *event)
{
    if(moveInFlag)
    {
        swshadow->hide();
        this->hide();
        moveInFlag = false;
    }
    else
    {
        swshadow->show();
        this->show();
    }

}

void TabWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        /*this->dragPosition = event->globalPos() - frameGeometry().topLeft();
        this->mousePressed = true*/
        qDebug() << "!!!!!!!!!!!!!!!!!!!!!";
        qDebug() << "!!!!!!pressEvent!!!!!";
        qDebug() << "!!!!!!!!!!!!!!!!!!!!!";
    }
    QWidget::mousePressEvent(event);
}
