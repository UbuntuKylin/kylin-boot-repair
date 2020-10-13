/************************************************
* 文件描述: In User Settings Edit
* 待完善:
* 待优化:
* 修改日期：2020.10.12
* 修改内容：
*   创建  HZH
*************************************************/
#ifndef STYLEWIDGETSHADOW_H
#define STYLEWIDGETSHADOW_H

#include "stylewidgetattribute.h"
#include <QDebug>
#include <QWidget>
//窗体阴影
#include <QPainter>
//窗口显示在屏幕中心
#include <QApplication>
#include <QScreen>

class StyleWidgetShadow : public QWidget
{
    Q_OBJECT
public:
    StyleWidgetShadow(StyleWidgetAttribute);

private:
    void handleIconClickedSub();//在屏幕中央显示
    void paintEvent(QPaintEvent *event);//重绘窗口
    StyleWidgetAttribute swa;
    int paintOnce=0;//只绘制一次

signals:

};

#endif // STYLEWIDGETSHADOW_H
