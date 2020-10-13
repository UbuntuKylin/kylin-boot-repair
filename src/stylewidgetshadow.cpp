/************************************************
* 文件描述: In User Settings Edit
* 待完善:
* 待优化:
* 修改日期：2020.10.12
* 修改内容：
*   创建  HZH
*************************************************/
#include "stylewidgetshadow.h"

/************************************************
* 函数名称：
* 功能描述：
* 输出参数：
* 修改日期：2020.10.12
* 修改内容：
*   创建  HZH
*
*************************************************/
StyleWidgetShadow::StyleWidgetShadow(StyleWidgetAttribute s)
{
    swa=s;
    //窗口设置
    this->setWindowFlags(Qt::FramelessWindowHint);//无边框
    this->setAttribute(Qt::WA_TranslucentBackground, true);//窗体透明
    this->setWindowTitle("麒麟引导修复");
    this->setFixedSize(swa.w,swa.h);
    if(swa.middle)handleIconClickedSub();//在屏幕中央显示
}

/************************************************
* 函数名称：
* 功能描述：
* 输出参数：
* 修改日期：2020.10.12
* 修改内容：
*   创建  HZH
*
*************************************************/
void StyleWidgetShadow::handleIconClickedSub()//在屏幕中央显示
{
    QRect availableGeometry = qApp->primaryScreen()->availableGeometry();
    this->move((availableGeometry.width() - this->width())/2, (availableGeometry.height() - this->height())/2);
}

/************************************************
* 函数名称：
* 功能描述：
* 输出参数：
* 修改日期：2020.10.12
* 修改内容：
*   创建  HZH
*
*************************************************/
void StyleWidgetShadow::paintEvent(QPaintEvent *event)//重绘窗口
{
    //if(paintOnce>swa.radius*2)return;
    //上半部分阴影
    QPainterPath painterPath;
    painterPath.setFillRule(Qt::WindingFill);//设置填充方式
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.fillPath(painterPath, QBrush(Qt::white));
    //下半部分阴影
    QPainterPath painterPath2;
    painterPath2.setFillRule(Qt::WindingFill);

    QColor color(0, 0, 0);
    for(int i=0; i<swa.shadow; i++)
    {
        int alpha=swa.shadowAlpha*255/4;
        color.setAlpha(alpha - (alpha/swa.shadow)*(i+1));
        painter.setPen(color);

        QRect rec(swa.shadow-i,swa.shadow-i,swa.w-(swa.shadow-i)*2,swa.titleHeight+swa.radius*2 );
        painterPath.addRoundedRect(rec,swa.radius,swa.radius);
        painter.setClipRegion(QRegion(0,0,swa.w,swa.titleHeight+swa.radius)); //裁剪区域（标题栏）
        painter.drawPath(painterPath);

        QRect rec2(rec.left(),rec.top()+swa.titleHeight,swa.w-(swa.shadow-i)*2,swa.h-swa.titleHeight-swa.radius);
        if(!swa.allRadius)
            painterPath2.addRect(rec2);
        else
            painterPath2.addRoundedRect(rec2,swa.radius,swa.radius);
        painter.setClipRegion(QRegion(0,swa.titleHeight+swa.radius,swa.w,swa.h)); //裁剪区域（窗体）
        painter.drawPath(painterPath2);
    }
    paintOnce++;
}
