/************************************************
* 文件描述: 选择修复方式页面。
* 待完善:
* 待优化:
* 修改日期：2020.10.12
* 修改内容：
*   创建  HZH
*************************************************/
#include "start_page.h"

/************************************************
* 函数名称：StartPage
* 功能描述：构造函数
* 输入参数：StyleWidgetAttribute page_swa
* 输出参数：无
* 修改日期：2020.10.12
* 修改内容：
*   创建  HZH
*
*************************************************/
StartPage::StartPage(StyleWidgetAttribute page_swa)
{
    swa=page_swa;
    initControlQss();//初始化样式
}

/************************************************
* 函数名称：initControlQss
* 功能描述：页面布局函数
* 输入参数：无
* 输出参数：无
* 修改日期：2020.10.12
* 修改内容：
*   创建  HZH
*
*************************************************/
void StartPage::initControlQss()
{
    repairStart = new QPushButton(this);
    QFont pushButton_repairStart;
    pushButton_repairStart.setFamily(QFontDatabase::applicationFontFamilies(QFontDatabase::addApplicationFont(":/data/PingFang-Jian-ChangGuiTi-2.ttf")).at(0));//读取字体
    repairStart->setFixedSize(240,40);
    repairStart->setText(tr("开始修复"));
    repairStart->setEnabled(true);


    connect(repairStart,&QPushButton::clicked,this,[=](){
        emit makeStart();
    });

    advanceChoice = new QPushButton(this);
    QFont pushButton_advanceChoice;
    pushButton_advanceChoice.setFamily(QFontDatabase::applicationFontFamilies(QFontDatabase::addApplicationFont(":/data/PingFang-Jian-ChangGuiTi-2.ttf")).at(0));//读取字体
    advanceChoice->setFixedSize(240,40);
    advanceChoice->setText(tr("手动修改GRUB"));
    advanceChoice->setEnabled(true);

    connect(advanceChoice,&QPushButton::clicked,this,[=](){
        int tempCheck = 0;

        tempCheck = system("mate-terminal --title='手动修复' -x  \
                            bash -c 'echo 手动修复优麒麟系统方法，请勿贸然尝试：; \
                                     echo 本方法仅适用于优麒麟系统，对于双系统等复杂情况，需视情况自行调整。; \
                                     echo ; \
                                     echo ① 输入sudo fdisk -l命令查看所有硬盘情况。; \
                                     echo ; \
                                     echo ② 使用mount命令挂载对应分区：若/boot目录未单独分区，则只挂载/根目录，并将/efi分区挂载至根目录下/boot文件夹中/efi目录下。;\
                                     echo ; \
                                     echo ③ 若/boot目录单独分区，则先挂载/根分区后，再执行第 ② 步。; \
                                     echo ; \
                                     echo ④ 在此之后还要分别使用sudo mount --bind命令挂载/dev目录、/proc目录、/sys目录，否则无法修复grub引导文件。; \
                                     echo ; \
                                     echo ⑤ 输入sudo -S chroot +根目录所在分区，进行根目录切换。; \
                                     echo ; \
                                     echo ⑥ 输入sudo -S grub-install --target= +boot分区下grub目录中的系统架构型号文件夹名称，如：x86_64-efi。; \
                                     echo ; \
                                     echo ⑦ 输入sudo -S grub-mkconfig -o /boot/grub/grub.cfg，生成grub.cfg文件。; \
                                     echo ; \
                                     echo ⑧ 输入sudo -S update-grub，修复引导文件。; \
                                     echo ; \
                                     echo ⑨ 修复完成，重启计算机。; exec bash'");

        if (-1 == tempCheck)
        {
            qDebug() << "改用kylin终端！";
            //system("kylin-terminal")
        }
        qDebug() << "用户选择手动修复模式！";
        qDebug() << "关闭手动模式即退出程序！";
        emit closeMainWin();
        qDebug() << "关闭主程序！";
        qDebug() << "*******************************************************";

    });

    startIcon = new QLabel;
    startIcon->setStyleSheet("border-image:url(:/data/main.png);border:0px;");
    startIcon->setFixedSize(144,144);

    startText = new QLabel;
    startText->setText(tr("修复计算机引导程序的常见问题"));

    QHBoxLayout *hl0=new QHBoxLayout;
    hl0->addSpacing(0);
    hl0->setMargin(0);
    hl0->addStretch(10);
    hl0->addWidget(startIcon,1);
    hl0->addStretch(10);

    QHBoxLayout *hl1=new QHBoxLayout;
    hl1->addSpacing(0);
    hl1->setMargin(0);
    hl1->addStretch(10);
    hl1->addWidget(startText,1);
    hl1->addStretch(10);


    QVBoxLayout *vl0=new QVBoxLayout;
    vl0->addSpacing(0);
    vl0->addLayout(hl0);
    vl0->addSpacing(15);
    vl0->addLayout(hl1);
    vl0->addStretch(99);

    QHBoxLayout *hl2=new QHBoxLayout;
    hl2->addSpacing(0);
    hl2->setMargin(0);
    hl2->addStretch(10);
    hl2->addWidget(repairStart,1);
    hl2->addStretch(10);

    QHBoxLayout *hl3=new QHBoxLayout;
    hl3->addSpacing(0);
    hl3->setMargin(0);
    hl3->addStretch(10);
    hl3->addWidget(advanceChoice,1);
    hl3->addStretch(10);


    QVBoxLayout *vl1=new QVBoxLayout;
    vl1->addSpacing(26);
    vl1->addLayout(vl0,1);
    vl1->addSpacing(15);

    vl1->addSpacing(24);
    vl1->addLayout(hl2,1);
    vl1->addSpacing(24);
    vl1->addLayout(hl3,1);
    vl1->addStretch(99);

    QHBoxLayout *vl00=new QHBoxLayout;

    vl00->addLayout(vl1);
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
void StartPage::pageChangeForTheme(QString str)
{
    if("ukui-dark" == str || "ukui-black" == str)
    {
        startText->setStyleSheet("color:rgba(255, 255, 255, 0.85);font-size:14px;");
        repairStart->setStyleSheet(".QPushButton{color:rgba(0, 0, 0, 0.85);background-color:rgba(62, 108, 229, 1);border-radius:6px;font-size:14px;}"
                                   ".QPushButton:hover{color:rgba(0, 0, 0, 0.85);background-color:rgba(108, 142, 235, 1);border-radius:6px;font-size:14px;}"
                                   ".QPushButton:pressed{color:rgba(0, 0, 0, 0.85);background-color:rgba(151, 151, 151, 1);border-radius:6px;font-size:14px;}");
        advanceChoice->setStyleSheet(".QPushButton{color:rgba(0, 0, 0, 0.85);background-color:rgba(62, 108, 229, 1);border-radius:6px;font-size:14px;}"
                                   ".QPushButton:hover{color:rgba(0, 0, 0, 0.85);background-color:rgba(108, 142, 235, 1);border-radius:6px;font-size:14px;}"
                                   ".QPushButton:pressed{color:rgba(0, 0, 0, 0.85);background-color:rgba(151, 151, 151, 1);border-radius:6px;font-size:14px;}");

    }
    else
    {
        startText->setStyleSheet("color:rgba(0, 0, 0, 0.85);font-size:14px;");
        repairStart->setStyleSheet(".QPushButton{color:rgba(255, 255, 255, 0.85);background-color:rgba(62, 108, 229, 1);border-radius:6px;font-size:14px;}"
                                   ".QPushButton:hover{color:rgba(255, 255, 255, 0.85);background-color:rgba(108, 142, 235, 1);border-radius:6px;font-size:14px;}"
                                   ".QPushButton:pressed{color:rgba(255, 255, 255, 0.85);background-color:rgba(151, 151, 151, 1);border-radius:6px;font-size:14px;}");
        advanceChoice->setStyleSheet(".QPushButton{color:rgba(255, 255, 255, 0.85);background-color:rgba(62, 108, 229, 1);border-radius:6px;font-size:14px;}"
                                   ".QPushButton:hover{color:rgba(255, 255, 255, 0.85);background-color:rgba(108, 142, 235, 1);border-radius:6px;font-size:14px;}"
                                   ".QPushButton:pressed{color:rgba(255, 255, 255, 0.85);background-color:rgba(151, 151, 151, 1);border-radius:6px;font-size:14px;}");

    }
}
