/************************************************
* 文件描述: 预扫描界面（执行fdisk线程时显示）。
* 待完善:
* 待优化:
* 修改日期：2020.10.12
* 修改内容：
*   创建  HZH
*************************************************/
#include "pre_page.h"

/************************************************
* 函数名称：PrePage
* 功能描述：构造函数，根据属性模板创建对象
* 输入参数：StyleWidgetAttribute page_swa
* 输出参数：无
* 修改日期：2020.10.12
* 修改内容：
*   创建  HZH
*
*************************************************/
PrePage::PrePage(StyleWidgetAttribute page_swa)
{
    swa=page_swa;
    initControlQss();//初始化样式

    movieLoading->start();
}

/************************************************
* 函数名称：initControlQss
* 功能描述：页面布局
* 输入参数：StyleWidgetAttribute page_swa
* 输出参数：无
* 修改日期：2020.10.12
* 修改内容：
*   创建  HZH
*
*************************************************/
void PrePage::initControlQss()
{
    loadingIcon = new QLabel;
    loadingIcon->setStyleSheet("border:0px;");
    loadingIcon->setFixedSize(64,64);

    movieLoading = new QMovie(":/data/loading.gif");
    lableMovie=new QLabel(loadingIcon);
    QSize movieSize(64,64);
    lableMovie->setFixedSize(movieSize);
    movieLoading->setScaledSize(movieSize);
    lableMovie->setMovie(movieLoading);

    loadingText=new QLabel;
    loadingText->setText(tr("正在扫描系统"));

    QHBoxLayout *hl0=new QHBoxLayout;
    hl0->setMargin(0);
    hl0->setSpacing(0);
    hl0->addStretch(10);
    hl0->addWidget(loadingIcon,1);
    hl0->addStretch(10);
    QHBoxLayout *hl1=new QHBoxLayout;
    hl1->addSpacing(0);
    hl1->setMargin(0);
    hl1->addStretch(10);
    hl1->addWidget(loadingText,1);
    hl1->addStretch(10);


    QVBoxLayout *vl0=new QVBoxLayout;
    vl0->addSpacing(102);
    vl0->addLayout(hl0);
    vl0->addSpacing(42);
    vl0->addLayout(hl1);
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
void PrePage::pageChangeForTheme(QString str)
{
    if("ukui-dark" == str || "ukui-black" == str)
    {
        loadingText->setStyleSheet("color:rgba(255, 255, 255, 0.85);font-size:14px;");
    }
    else
        loadingText->setStyleSheet("color:rgba(0, 0, 0, 0.85);font-size:14px;");
}
