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
PrePage::PrePage(const StyleWidgetAttribute& page_swa)
    :swa(page_swa)
{
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
    if(nullptr == loadingIcon)
    {
        qDebug() << "错误！loadingIcon申请空间失败！";
        return;
    }
    loadingIcon->setStyleSheet("border:0px;");
    loadingIcon->setFixedSize(64,64);

    movieLoading = new QMovie(":/data/loading.gif");
    if(nullptr == movieLoading)
    {
        qDebug() << "错误！movieLoading申请空间失败！";
        return;
    }
    lableMovie=new QLabel(loadingIcon);
    if(nullptr == lableMovie)
    {
        qDebug() << "错误！lableMovie申请空间失败！";
        return;
    }
    QSize movieSize(64,64);
    lableMovie->setFixedSize(movieSize);
    movieLoading->setScaledSize(movieSize);
    lableMovie->setMovie(movieLoading);

    loadingText=new QLabel;
    if(nullptr == loadingText)
    {
        qDebug() << "错误！loadingText申请空间失败！";
        return;
    }
    loadingText->setText(tr("Detecting"));//正在扫描系统

    QHBoxLayout *hl0=new QHBoxLayout;
    if(nullptr == hl0)
    {
        qDebug() << "错误！hl0申请空间失败！";
        return;
    }
    hl0->setMargin(0);
    hl0->setSpacing(0);
    hl0->addStretch(10);
    hl0->addWidget(loadingIcon,1);
    hl0->addStretch(10);
    QHBoxLayout *hl1=new QHBoxLayout;
    if(nullptr == hl1)
    {
        qDebug() << "错误！hl1申请空间失败！";
        return;
    }
    hl1->addSpacing(0);
    hl1->setMargin(0);
    hl1->addStretch(10);
    hl1->addWidget(loadingText,1);
    hl1->addStretch(10);


    QVBoxLayout *vl0=new QVBoxLayout;
    if(nullptr == vl0)
    {
        qDebug() << "错误！vl0申请空间失败！";
        return;
    }
    vl0->addSpacing(102);
    vl0->addLayout(hl0);
    vl0->addSpacing(42);
    vl0->addLayout(hl1);
    vl0->addStretch();

    QHBoxLayout *vl00=new QHBoxLayout;
    if(nullptr == vl00)
    {
        qDebug() << "错误！vl00申请空间失败！";
        return;
    }
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
void PrePage::pageChangeForTheme(const QString& str)
{
    if("" == str)
    {
        qDebug() << "错误！未获取主题样式字符！";
        return;
    }
    if("ukui-dark" == str || "ukui-black" == str)
    {
        loadingText->setStyleSheet("color:rgba(255, 255, 255, 0.85);font-size:14px;");
    }
    else
        loadingText->setStyleSheet("color:rgba(0, 0, 0, 0.85);font-size:14px;");
}
