/************************************************
* 文件描述: 修复时显示页面的布局文件的另一种样式。
* 待完善:   暂时流程中没有用到，保留。
* 待优化:
* 修改日期：2020.10.12
* 修改内容：
*   创建  HZH
*************************************************/
#ifndef REPAIRPAGE2_H
#define REPAIRPAGE2_H

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
#include <QMovie>

class RepairPage2 : public QWidget
{
    Q_OBJECT
public:
    explicit RepairPage2(const StyleWidgetAttribute& page_swa);

signals:

private:

    StyleWidgetAttribute swa;//属性

    QMovie *movieLoading  = nullptr;
    QLabel *lableMovie    = nullptr;
    QLabel *repairingIcon = nullptr;//修复分区标志
    QLabel *repairingText = nullptr;//修复分区标语

    void initControlQss();
    void pageChangeForTheme(const QString& str);

};

#endif // REPAIRPAGE_H
