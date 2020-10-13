/************************************************
* 文件描述: 修复时显示页面的布局文件。
* 待完善:
* 待优化:
* 修改日期：2020.10.12
* 修改内容：
*   创建  HZH
*************************************************/
#include "repair_page.h"

/************************************************
* 函数名称：RepairPage
* 功能描述：构造函数
* 输入参数：StyleWidgetAttribute page_swa属性
* 输出参数：无
* 修改日期：2020.10.12
* 修改内容：
*   创建  HZH
*
*************************************************/
RepairPage::RepairPage(StyleWidgetAttribute page_swa)
{
    swa=page_swa;
    initControlQss();//初始化样式
}

/************************************************
* 函数名称：initControlQss
* 功能描述：页面布局
* 输入参数：无
* 输出参数：无
* 修改日期：2020.10.12
* 修改内容：
*   创建  HZH
*
*************************************************/
void RepairPage::initControlQss()
{
    repairingIcon = new QLabel;
    repairingIcon->setStyleSheet("border-image:url(:/data/loading.png);border:0px;");
    repairingIcon->setFixedSize(64,64);

    repairingText=new QLabel;
    repairingText->setText(tr("正在修复，可能需要几分钟……"));
    //repairingText->setStyleSheet("color:rgba(0, 0, 0, 0.85);font-size:14px;");

    QHBoxLayout *hl0=new QHBoxLayout;
    hl0->setMargin(0);
    hl0->setSpacing(0);
    hl0->addStretch(10);
    hl0->addWidget(repairingIcon,1);
    hl0->addStretch(10);
    QHBoxLayout *hl1=new QHBoxLayout;
    hl1->addSpacing(0);
    hl1->setMargin(0);
    hl1->addStretch(10);
    hl1->addWidget(repairingText,1);
    hl1->addStretch(10);


    QVBoxLayout *vl0=new QVBoxLayout;
    vl0->addSpacing(102);
    vl0->addLayout(hl0);
    vl0->addSpacing(42);
    vl0->addLayout(hl1);
    vl0->addStretch();

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
void RepairPage::pageChangeForTheme(QString str)
{
    if("ukui-dark" == str || "ukui-black" == str)
    {
        repairingText->setStyleSheet("color:rgba(255, 255, 255, 0.85);font-size:14px;");
    }
    else
        repairingText->setStyleSheet("color:rgba(0, 0, 0, 0.85);font-size:14px;");
}
