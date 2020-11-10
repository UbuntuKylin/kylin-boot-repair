#ifndef TABMENUSHADOW_H
#define TABMENUSHADOW_H

#include "stylewidgetattribute.h"
#include <QDebug>
#include <QWidget>
//窗体阴影
#include <QPainter>
//窗口显示在屏幕中心
#include <QApplication>
#include <QScreen>

class TabMenuShadow : public QWidget
{
    Q_OBJECT
public:
    TabMenuShadow(StyleWidgetAttribute,QWidget *parent = nullptr);

private:
    void handleIconClickedSub();//在屏幕中央显示
    void paintEvent(QPaintEvent *event);//重绘窗口
    StyleWidgetAttribute swa;
    int paintOnce=0;//只绘制一次

signals:

};

#endif // TABMENUSHADOW_H
