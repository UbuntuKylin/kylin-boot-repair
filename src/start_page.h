/************************************************
* 文件描述: 选择修复方式页面。
* 待完善:
* 待优化:
* 修改日期：2020.10.12
* 修改内容：
*   创建  HZH
*************************************************/
#ifndef STARTPAGE_H
#define STARTPAGE_H

#include "stylewidget.h"
#include <QDebug>
//控件
#include <QWidget>
#include <QLabel>
#include <QPushButton>
//布局
#include <QBoxLayout>
//打开文件
#include <QFileDialog>
//读取本地字体
#include <QFontDatabase>
//硬盘信息
#include <QStorageInfo>

class StartPage : public QWidget
{
    Q_OBJECT
public:
    explicit StartPage( StyleWidgetAttribute);
    void pageChangeForTheme(QString str);

signals:
    void makeStart();                          //开始修复信号
    void closeMainWin();

private:

    QPushButton *repairStart = nullptr;        //开始修复按钮
    QPushButton *advanceChoice = nullptr;      //手动修复按钮

    StyleWidgetAttribute swa;                  //属性

    QLabel *startIcon = nullptr;               //开始修复标志
    QLabel *startText = nullptr;               //开始修复标语

    void initControlQss();

};

#endif // STARTPAGE_H
