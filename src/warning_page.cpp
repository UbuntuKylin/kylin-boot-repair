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
    cancelButton = new QPushButton(this);
    QFont pushButton_cancelButton;
    pushButton_cancelButton.setFamily(QFontDatabase::applicationFontFamilies(QFontDatabase::addApplicationFont(":/data/PingFang-Jian-ChangGuiTi-2.ttf")).at(0));//读取字体
    cancelButton->setFixedSize(140,40);
    cancelButton->setText(tr("取消"));
    cancelButton->setEnabled(false);
    cancelButton->setStyleSheet("color:rgba(0, 0, 0, 0.85);");
    cancelButton->setStyleSheet("background-color:rgba(231, 231, 231, 1);border-radius:6px;");
    //connect(repairStart,&QPushButton::clicked,this,&PrePage::on_pushButton_clicked);

    continueButton = new QPushButton(this);
    QFont pushButton_continueButton;
    pushButton_continueButton.setFamily(QFontDatabase::applicationFontFamilies(QFontDatabase::addApplicationFont(":/data/PingFang-Jian-ChangGuiTi-2.ttf")).at(0));//读取字体
    continueButton->setFixedSize(140,40);
    continueButton->setText(tr("继续"));
    continueButton->setEnabled(false);
    continueButton->setStyleSheet("color:rgba(0, 0, 0, 0.85);");
    continueButton->setStyleSheet("background-color:rgba(231, 231, 231, 1);border-radius:6px;");
    //connect(repairStart,&QPushButton::clicked,this,&PrePage::on_pushButton_clicked);

    warningIcon = new QLabel;
    warningIcon->setStyleSheet("border-image:url(:/data/main.png);border:0px;");
    warningIcon->setFixedSize(144,144);

    warningText=new QLabel;
    warningText->setText(tr("引导修复需要授权，请不要关闭授权页面\n是否继续？"));
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
    hl2->addWidget(cancelButton,1);
    hl2->addSpacing(32);
    hl2->addWidget(continueButton,1);
    hl2->addStretch(10);

    QVBoxLayout *vl0=new QVBoxLayout;
    vl0->addSpacing(26);
    vl0->addLayout(hl0);
    vl0->addSpacing(15);
    vl0->addLayout(hl1);
    vl0->addSpacing(61);
    vl0->addLayout(hl2);
    vl0->addStretch();

    QHBoxLayout *vl00=new QHBoxLayout;
    //vl00->addStretch(3);
    vl00->addLayout(vl0);
    //vl00->addStretch(3);
    this->setLayout(vl00);

}

