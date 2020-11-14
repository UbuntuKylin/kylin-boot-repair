/************************************************
* 文件描述: In User Settings Edit
* 待完善:
* 待优化:
* 修改日期：2020.10.12
* 修改内容：
*   创建  HZH
*************************************************/
#include "logwidget.h"

/************************************************
* 函数名称：
* 功能描述：
* 输出参数：
* 修改日期：2020.10.12
* 修改内容：
*   创建  HZH
*
*************************************************/
LogWidget::LogWidget(StyleWidgetAttribute swa, QString dialogTitleText, bool isDialog )
{
    local_swa = swa;
    m_isDialog=isDialog;
    swshadow = new StyleWidgetShadow(swa);
    this->setWindowIcon(QIcon(":/data/guide_repair24.png"));
    this->setWindowTitle(tr("麒麟引导修复日志"));
    myStyle(swa);
    text->setText(dialogTitleText);
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
LogWidget::~LogWidget()
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
void LogWidget::WidgetStyleClose()
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
void LogWidget::myStyle(StyleWidgetAttribute swa)
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

    widgetMin =new QPushButton;//最小化按钮
    widgetMin->setObjectName("widgetMin");
    widgetMin->setIconSize(smallWidgetSize);
    widgetMin->setFixedSize(smallWidgetSize);
    connect(widgetMin,&QPushButton::clicked,this,[=]{this->setWindowState(Qt::WindowMinimized);});

    widgetClose =new QPushButton;//关闭按钮
    widgetClose->setObjectName("widgetClose");
    widgetClose->setIconSize(smallWidgetSize);
    widgetClose->setFixedSize(smallWidgetSize);
    connect(widgetClose,&QPushButton::clicked,this,&LogWidget::WidgetStyleClose);

    widgetSave =new QPushButton;//导出
    widgetSave->setText(tr("导出"));
    widgetSave->setObjectName("widgetClose");
    widgetSave->setFixedSize(120,36);
    connect(widgetSave,&QPushButton::clicked,this,&LogWidget::WidgetStyleSave);

    //布局
    QHBoxLayout *hlt0=new QHBoxLayout;//右上角按钮内部，水平布局
    hlt0->setMargin(0);
    hlt0->setSpacing(0);
    hlt0->addWidget(widgetMin, 1);
    hlt0->addSpacing(4);
    hlt0->addWidget(widgetClose, 1);

//    QVBoxLayout *vlt0=new QVBoxLayout;//右上角按钮外部，垂直布局
//    vlt0->setMargin(0);
//    vlt0->setSpacing(0);
//    vlt0->addSpacing(6);
//    vlt0->addLayout(hlt0);
//    vlt0->addSpacing(14);

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

    logText = new QTextEdit;
    logText->setReadOnly(true);
    logText->setObjectName("logText");
    logText->setFixedSize(395,390);



    QHBoxLayout *hlt_logText=new QHBoxLayout;
    hlt_logText->setMargin(0);
    hlt_logText->setSpacing(0);
    hlt_logText->addSpacing(32);
    hlt_logText->addWidget(logText,1);
    hlt_logText->addStretch(99);

    QHBoxLayout *hlt_widgetSave=new QHBoxLayout;
    hlt_widgetSave->setMargin(0);
    hlt_widgetSave->setSpacing(0);
    hlt_widgetSave->addSpacing(308);
    hlt_widgetSave->addWidget(widgetSave,1);
    hlt_widgetSave->addStretch(99);


    QVBoxLayout *vlt_logText=new QVBoxLayout;
    vlt_logText->setMargin(0);
    vlt_logText->setSpacing(0);
    vlt_logText->addSpacing(3);
    vlt_logText->addLayout(hlt_logText);
    vlt_logText->addSpacing(24);
    vlt_logText->addLayout(hlt_widgetSave);
    vlt_logText->addStretch(99);

    body->setLayout(vlt_logText);

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
void LogWidget::paintEvent(QPaintEvent *event)//重绘窗口
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
void LogWidget::showOrHide()
{
    if(this->isHidden())
    {
        QString logString;
        QFile logfile("/tmp/BootRepairLog.txt");

        if(!logfile.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            qDebug()<<"无法打开日志!";
        }
        while(!logfile.atEnd())
        {
            QByteArray line = logfile.readLine();
            QString str(line);
            logString.append(str);
        }

        logText->clear();
        logText->setPlainText(logString);
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
void LogWidget::ThemeChooseForWidget(QString str)
{

    if("ukui-dark" == str || "ukui-black" == str)
    {
        text->setStyleSheet("rgba(255, 255, 255, 0.85);");

        //样式表stylesheet//测试用border:1px solid red;
        QString bodyStyleSheet="QWidget{background-color:rgba(20, 20, 20, 1);border-bottom-left-radius:"+QString::number(local_swa.radius)+
                                "px;border-bottom-right-radius:"+QString::number(local_swa.radius)+"px;}";
        title->setStyleSheet("QWidget{background-color:rgba(20, 20, 20, 1);border-top-left-radius:"
                                 +QString::number(local_swa.radius)+"px;border-top-right-radius:"+QString::number(local_swa.radius)+"px;}");
        body->setStyleSheet(bodyStyleSheet);


        widgetMin->setStyleSheet("QPushButton{background-color:rgba(255,255,255,0);border-image:url(:/data/min_h.png);border-radius:4px;font-size:14px;}"
                                 "QPushButton:hover{background-color:rgba(108, 142, 235, 1);border-image:url(:/data/min_h.png);border-radius:4px;font-size:14px;}"
                                 "QPushButton:pressed{background-color:rgba(50, 88, 202, 1);border-image:url(:/data/min_h.png);border-radius:4px;font-size:14px;}");
        widgetClose->setStyleSheet("QPushButton{background-color:rgba(255,255,255,0);border-image:url(:/data/close_h.png);border-radius:4px;font-size:14px;}"
                                   "QPushButton:hover{background-color:rgba(240,64,52,1);border-image:url(:/data/close_h.png);border-radius:4px;font-size:14px;}"
                                   "QPushButton:pressed{background-color:rgba(215,51,53,1);border-image:url(:/data/close_p.png);border-radius:4px;font-size:14px;}");
        logText->setStyleSheet("QTextEdit{background-color:rgba(20, 20, 20, 1);color:rgba(255, 255, 255, 0.85);font-size:14px;}");
    }
    else
    {
       text->setStyleSheet("rgba(0, 0, 0, 0.85);");

       //样式表stylesheet//测试用border:1px solid red;
       QString bodyStyleSheet="QWidget{background-color:rgba(255,255,255,1);border-bottom-left-radius:"+QString::number(local_swa.radius)+
                               "px;border-bottom-right-radius:"+QString::number(local_swa.radius)+"px;}";
       title->setStyleSheet("QWidget{background-color:rgba(255,255,255,1);border-top-left-radius:"
                                +QString::number(local_swa.radius)+"px;border-top-right-radius:"+QString::number(local_swa.radius)+"px;}");
       body->setStyleSheet(bodyStyleSheet);


       widgetMin->setStyleSheet("QPushButton{background-color:rgba(255,255,255,0);border-image:url(:/data/min_d.png);border-radius:4px;font-size:14px;}"
                                "QPushButton:hover{background-color:rgba(108, 142, 235, 1);border-image:url(:/data/min_h.png);border-radius:4px;font-size:14px;}"
                                "QPushButton:pressed{background-color:rgba(50, 88, 202, 1);border-image:url(:/data/min_h.png);border-radius:4px;font-size:14px;}");
       widgetClose->setStyleSheet("QPushButton{background-color:rgba(255,255,255,0);border-image:url(:/data/close_d.png);border-radius:4px;font-size:14px;}"
                                  "QPushButton:hover{background-color:rgba(240,64,52,1);border-image:url(:/data/close_h.png);border-radius:4px;font-size:14px;}"
                                  "QPushButton:pressed{background-color:rgba(215,51,53,1);border-image:url(:/data/close_p.png);border-radius:4px;font-size:14px;}");
        logText->setStyleSheet("QTextEdit{background-color:rgba(255,255,255,1);color:rgba(0, 0, 0, 0.85);font-size:14px;}");
    }

}

void LogWidget::WidgetStyleSave()
{
    qDebug() << "文件另存为";
    QFileDialog saveDialog;
        QString fileName = saveDialog.getSaveFileName(this,tr("Open File"),"/home",tr("Text File(*.txt)"));
        if(fileName == "")
        {
            return;
        }
        QFile file(fileName);
        if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QMessageBox::warning(this,tr("错误"),tr("打开文件失败"));
            return;
        }
        else
        {
            QTextStream textStream(&file);
            QString str = logText->toPlainText();
            textStream<<str;
            QMessageBox::warning(this,tr("提示"),tr("保存文件成功"));

            file.close();
        }
}
