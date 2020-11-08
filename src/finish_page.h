/************************************************
* 文件描述: finish页面类，界面设计。
* 待完善:
* 待优化:
* 修改日期：2020.10.12
* 修改内容：
*   创建  HZH
*************************************************/
#ifndef FINISHPAGE_H
#define FINISHPAGE_H

#include "stylewidget.h"
#include <QDebug>
#include <QProcess>
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

class FinishPage : public QWidget
{
    Q_OBJECT
public:
    explicit FinishPage( StyleWidgetAttribute);
    void pageChangeForTheme(QString str);
public slots:

signals:

private:
    QProcess *cmdFinishBash;

    QPushButton *laterButton = nullptr;
    QPushButton *nowButton = nullptr;

    StyleWidgetAttribute swa;//属性

    QLabel *finishIcon = nullptr;//修复完成标志
    QLabel *finishText = nullptr;//修复完成标语

    int frameCount=0;

    void initControlQss();

};

#endif // FINISHPAGE_H
