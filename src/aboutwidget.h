#ifndef ABOUTWIDGET_H
#define ABOUTWIDGET_H

#include "stylewidgetshadow.h"
#include <QWidget>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QFileDialog>
#include <QMessageBox>
//布局
#include <QBoxLayout>
//读取本地字体
#include <QFontDatabase>
//鼠标拖动事件
#include <QMouseEvent>
#include <QPoint>

class AboutWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AboutWidget(const StyleWidgetAttribute& swa, QString dialogTitleText,bool isDialog=false);
    ~AboutWidget();
    QWidget *body  = nullptr;//窗体
    void showOrHide();//切换显示和隐藏状态
    void WidgetStyleClose();//点击关闭事件
    void WidgetStyleSave();

    void ThemeChooseForWidget(const QString& str);

    QPushButton *widgetMenu = nullptr;//菜单按钮
    QPushButton *widgetClose = nullptr;//关闭窗口
    QPushButton *widgetMin = nullptr;//最小化窗口

signals:
    void allClose();
    void doSomethig();

private:
    virtual void paintEvent(QPaintEvent *ev);//重绘窗口

    void myStyle(StyleWidgetAttribute swa);//设定样式

    StyleWidgetAttribute local_swa;

    StyleWidgetShadow *swshadow = nullptr;//阴影
    QWidget *title = nullptr;//标题栏
    QLabel *aboutIcon = nullptr;//标题
    QLabel *aboutText = nullptr;//图标
    QLabel *aboutVersion_1 = nullptr;//版本
    QLabel *aboutVersion_2 = nullptr;//版本
    QPixmap titleImage;   //标题栏图片

    bool m_isDialog =false;//如果是窗口
    bool paintOnce=false;//只绘制一次
    bool m_isLeftButtonPressed = false;
    QPoint m_last;

};

#endif // ABOUTWIDGET_H
