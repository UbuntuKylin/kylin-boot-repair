/************************************************
* 文件描述: In User Settings Edit
* 待完善:
* 待优化:
* 修改日期：2020.10.12
* 修改内容：
*   创建  HZH
*************************************************/
#include "warning_page.h"

/************************************************
* 函数名称：
* 功能描述：
* 输出参数：
* 修改日期：2020.10.12
* 修改内容：
*   创建  HZH
*
*************************************************/
WarningPage::WarningPage(StyleWidgetAttribute page_swa)
{
    swa=page_swa;
    initControlQss();//初始化样式

    StyleWidgetAttribute logWin(LOGWINDOWWIDETH,LOGWINDOWHEIGHT,0,LOGWIDGETRADIUS,LOGSHADOWWIDTH,LOGSHADOWALPHA,LOGTITLEHEIGHT);
    logWinWidget=new LogWidget(logWin,tr("KylinBootRepairLog"));//麒麟引导修复日志

    //logWinWidget->hide();
    logWinWidget->showOrHide();
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
WarningPage::~WarningPage()
{
    delete logWinWidget;
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
void WarningPage::initControlQss()
{
    logButton = new QPushButton(this);
    QFont pushButton_cancelButton;
    pushButton_cancelButton.setFamily(QFontDatabase::applicationFontFamilies(QFontDatabase::addApplicationFont(":/data/PingFang-Jian-ChangGuiTi-2.ttf")).at(0));//读取字体
    logButton->setFixedSize(240,40);
    logButton->setText(tr("Check Log"));//查看修复日志
    logButton->setObjectName("logButton");
    logButton->setEnabled(true);
    connect(logButton,&QPushButton::clicked,this,[=](){
        logWinWidget->showOrHide();
    });

    exitButton = new QPushButton(this);
    QFont pushButton_continueButton;
    pushButton_continueButton.setFamily(QFontDatabase::applicationFontFamilies(QFontDatabase::addApplicationFont(":/data/PingFang-Jian-ChangGuiTi-2.ttf")).at(0));//读取字体
    exitButton->setFixedSize(240,40);
    exitButton->setText(tr("Exit"));//退出程序
    exitButton->setObjectName("exitButton");
    exitButton->setEnabled(true);
    exitButton->setStyleSheet("color:rgba(0, 0, 0, 0.85);");
    connect(exitButton,&QPushButton::clicked,this,[=](){
        emit closeMainWin();
    });

    warningIcon = new QLabel;
    warningIcon->setStyleSheet("border-image:url(:/data/fail.png);border:0px;");
    warningIcon->setFixedSize(118,118);

    warningText=new QLabel;
    warningText->setText(tr("Error occurred,failed"));//过程出现问题，修复失败！
    warningText->setAlignment(Qt::AlignHCenter);
    warningText->setStyleSheet("color:rgba(0, 0, 0, 0.85);font-size:14px;");

    QHBoxLayout *hl0=new QHBoxLayout;
    hl0->addSpacing(0);
    hl0->setMargin(0);
    hl0->addStretch(10);
    hl0->addWidget(warningIcon,1);
    hl0->addStretch(10);

    QHBoxLayout *hl1=new QHBoxLayout;
    hl1->addSpacing(0);
    hl1->setMargin(0);
    hl1->addStretch(10);
    hl1->addWidget(warningText,1);
    hl1->addStretch(10);

    QHBoxLayout *hl2=new QHBoxLayout;
    hl2->addSpacing(0);
    hl2->setMargin(0);
    hl2->addStretch(10);
    hl2->addWidget(logButton,1);
    hl2->addStretch(10);

    QHBoxLayout *hl3=new QHBoxLayout;
    hl3->addSpacing(0);
    hl3->setMargin(0);
    hl3->addStretch(10);
    hl3->addWidget(exitButton,1);
    hl3->addStretch(10);

    QVBoxLayout *vl0=new QVBoxLayout;
    vl0->addSpacing(44);
    vl0->addLayout(hl0);
    vl0->addSpacing(5);
    vl0->addLayout(hl1);
    vl0->addSpacing(34);
    vl0->addLayout(hl2);
    vl0->addSpacing(22);
    vl0->addLayout(hl3);
    vl0->addStretch();

    QHBoxLayout *vl00=new QHBoxLayout;
    //vl00->addStretch(3);
    vl00->addLayout(vl0);
    //vl00->addStretch(3);
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
void WarningPage::pageChangeForTheme(QString str)
{
    logWinWidget->ThemeChooseForWidget(str);
    if("ukui-dark" == str || "ukui-black" == str)
    {
        warningText->setStyleSheet("color:rgba(255, 255, 255, 0.85);font-size:14px;");
        logButton->setStyleSheet("QPushButton#logButton{color:rgba(255, 255, 255, 0.65);background-color:rgba(62, 108, 229, 1);border-radius:6px;font-size:14px;}"
                                   "QPushButton#logButton:hover{color:rgba(255, 255, 255, 0.65);background-color:rgba(108, 142, 235, 1);border-radius:6px;font-size:14px;}"
                                   "QPushButton#logButton:pressed{color:rgba(255, 255, 255, 0.65);background-color:rgba(151, 151, 151, 1);border-radius:6px;font-size:14px;}");
        exitButton->setStyleSheet("QPushButton#exitButton{color:rgba(255, 255, 255, 0.65);background-color:rgba(151, 151, 151, 1);border-radius:6px;font-size:14px;}"
                                   "QPushButton#exitButton:hover{color:rgba(255, 255, 255, 0.65);background-color:rgba(108, 142, 235, 1);border-radius:6px;font-size:14px;}"
                                   "QPushButton#exitButton:pressed{color:rgba(255, 255, 255, 0.65);background-color:rgba(151, 151, 151, 1);border-radius:6px;font-size:14px;}");

    }
    else
    {
        warningText->setStyleSheet("color:rgba(0, 0, 0, 0.85);font-size:14px;");
        logButton->setStyleSheet("QPushButton#logButton{color:rgba(255, 255, 255, 0.85);background-color:rgba(62, 108, 229, 1);border-radius:6px;font-size:14px;}"
                                   "QPushButton#logButton:hover{color:rgba(255, 255, 255, 0.85);background-color:rgba(108, 142, 235, 1);border-radius:6px;font-size:14px;}"
                                   "QPushButton#logButton:pressed{color:rgba(255, 255, 255, 0.85);background-color:rgba(151, 151, 151, 1);border-radius:6px;font-size:14px;}");
        exitButton->setStyleSheet("QPushButton#exitButton{color:rgba(0, 0, 0, 0.85);background-color:rgba(231, 231, 231, 1);border-radius:6px;font-size:14px;}"
                                   "QPushButton#exitButton:hover{color:rgba(0, 0, 0, 0.85);background-color:rgba(108, 142, 235, 1);border-radius:6px;font-size:14px;}"
                                   "QPushButton#exitButton:pressed{color:rgba(0, 0, 0, 0.85);background-color:rgba(151, 151, 151, 1);border-radius:6px;font-size:14px;}");

    }
}

