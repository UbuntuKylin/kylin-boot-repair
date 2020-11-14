/************************************************
* 文件描述: finish页面类，界面设计。
* 待完善:
* 待优化:
* 修改日期：2020.10.12
* 修改内容：
*   创建  HZH
*************************************************/
#include "finish_page.h"

/************************************************
* 函数名称：FinishPage
* 功能描述：构造函数
* 输入参数：StyleWidgetAttribute page_swa页面基础属性
* 输出参数：无
* 修改日期：2020.10.12
* 修改内容：
*   创建  HZH
*
*************************************************/
FinishPage::FinishPage(StyleWidgetAttribute page_swa)
{
    swa=page_swa;
    initControlQss();//初始化样式
}

/************************************************
* 函数名称：initControlQss()
* 功能描述：私有成员实例化，界面布局
* 输入参数：
* 输出参数：
* 修改日期：2020.10.12
* 修改内容：
*   创建  HZH
*
*************************************************/
void FinishPage::initControlQss()
{
    //稍后按钮，点击后程序退出
    laterButton = new QPushButton(this);
    QFont pushButton_laterButton;
    pushButton_laterButton.setFamily(QFontDatabase::applicationFontFamilies(QFontDatabase::addApplicationFont(":/data/PingFang-Jian-ChangGuiTi-2.ttf")).at(0));//读取字体
    laterButton->setFixedSize(140,40);
    laterButton->setObjectName("laterButton");
    laterButton->setText(tr("稍后"));
    laterButton->setEnabled(true);

    connect(laterButton,&QPushButton::clicked,this,[=](){
        QApplication::exit();
    });

    //现在按钮，点击后立即重启电脑，程序退出。
    nowButton = new QPushButton(this);
    QFont nowButton_continueButton;
    nowButton_continueButton.setFamily(QFontDatabase::applicationFontFamilies(QFontDatabase::addApplicationFont(":/data/PingFang-Jian-ChangGuiTi-2.ttf")).at(0));//读取字体
    nowButton->setFixedSize(140,40);
    nowButton->setText(tr("现在"));
    nowButton->setEnabled(true);

    connect(nowButton,&QPushButton::clicked,this,[=](){
        shutDownBash = new QProcess();   //创建QProcess对象并连接信号与槽

        shutDownBash->start("sudo -S shutdown -r now");

//        shutDownBash->write("sudo -S shutdown -r now" + '\n');

        shutDownBash->waitForStarted();


//        QProcess::execute("sudo -S shutdown -r now");
//        QApplication::exit();
        qDebug() << "用户点击现在重启按钮！程序关闭";
        qDebug() << "*******************************************************";
    });

    //完成图标
    finishIcon = new QLabel;
    finishIcon->setStyleSheet("border-image:url(:/data/finish.png);border:0px;");
    finishIcon->setFixedSize(118,118);

    //完成标语
    finishText=new QLabel;
    finishText->setText(tr("修复完成，你现在可以重启电脑！"));
    finishText->setAlignment(Qt::AlignHCenter);
    //finishText->setStyleSheet("color:rgba(0, 0, 0, 0.85);font-size:14px;");

    QHBoxLayout *hl0=new QHBoxLayout;
    hl0->addSpacing(0);
    hl0->setMargin(0);
    hl0->addStretch(10);
    hl0->addWidget(finishIcon,1);
    hl0->addStretch(10);

    QHBoxLayout *hl1=new QHBoxLayout;
    hl1->addSpacing(0);
    hl1->setMargin(0);
    hl1->addStretch(10);
    hl1->addWidget(finishText,1);
    hl1->addStretch(10);

    QHBoxLayout *hl2=new QHBoxLayout;
    hl2->addSpacing(0);
    hl2->setMargin(0);
    hl2->addStretch(10);
    hl2->addWidget(laterButton,1);
    hl2->addSpacing(16);
    hl2->addWidget(nowButton,1);
    hl2->addStretch(10);

    QVBoxLayout *vl0=new QVBoxLayout;
    vl0->addSpacing(50);
    vl0->addLayout(hl0);
    vl0->addSpacing(45);
    vl0->addLayout(hl1);
    vl0->addSpacing(27);
    vl0->addLayout(hl2);
    vl0->addStretch(99);

    QHBoxLayout *vl00=new QHBoxLayout;
    vl00->addLayout(vl0);
    this->setLayout(vl00);

}

/************************************************
* 函数名称：pageChangeForTheme
* 功能描述：主题颜色适配
* 输入参数：StyleWidgetAttribute page_swa
* 输出参数：无
* 修改日期：2020.10.12
* 修改内容：
*   创建  HZH
*
*************************************************/
void FinishPage::pageChangeForTheme(QString str)
{
    if("ukui-dark" == str || "ukui-black" == str)
    {
        finishText->setStyleSheet("color:rgba(255, 255, 255, 0.85);font-size:14px;");
        laterButton->setStyleSheet("QPushButton#laterButton{color:rgba(0, 0, 0, 0.85);background-color:rgba(231, 231, 231, 1);border-radius:6px;font-size:14px;}"
                                   "QPushButton#laterButton:hover{color:rgba(0, 0, 0, 0.85);background-color:rgba(108, 142, 235, 1);border-radius:6px;font-size:14px;}"
                                   "QPushButton#laterButton:pressed{color:rgba(0, 0, 0, 0.85);background-color:rgba(50, 88, 202, 1);border-radius:6px;font-size:14px;}");
        nowButton->setStyleSheet("QPushButton#laterButton{color:rgba(0, 0, 0, 0.855);background-color:rgba(231, 231, 231, 1);border-radius:6px;font-size:14px;}"
                                              "QPushButton#laterButton:hover{color:rgba(0, 0, 0, 0.85);background-color:rgba(108, 142, 235, 1);border-radius:6px;font-size:14px;}"
                                              "QPushButton#laterButton:pressed{color:rgba(0, 0, 0, 0.85);background-color:rgba(50, 88, 202, 1);border-radius:6px;font-size:14px;}");

    }
    else
    {
        finishText->setStyleSheet("color:rgba(0, 0, 0, 0.85);font-size:14px;");
        laterButton->setStyleSheet("QPushButton#laterButton{color:rgba(255, 255, 255, 0.85);background-color:rgba(231, 231, 231, 1);border-radius:6px;font-size:14px;}"
                                   "QPushButton#laterButton:hover{color:rgba(255, 255, 255, 0.85);background-color:rgba(108, 142, 235, 1);border-radius:6px;font-size:14px;}"
                                   "QPushButton#laterButton:pressed{color:rgba(255, 255, 255, 0.85);background-color:rgba(50, 88, 202, 1);border-radius:6px;font-size:14px;}");
        nowButton->setStyleSheet("QPushButton#laterButton{color:rgba(255, 255, 255, 0.85);background-color:rgba(231, 231, 231, 1);border-radius:6px;font-size:14px;}"
                                 "QPushButton#laterButton:hover{color:rgba(255, 255, 255, 0.85);background-color:rgba(108, 142, 235, 1);border-radius:6px;font-size:14px;}"
                                 "QPushButton#laterButton:pressed{color:rgba(255, 255, 255, 0.85);background-color:rgba(50, 88, 202, 1);border-radius:6px;font-size:14px;}");
    }
}
