/************************************************
* 文件描述: In User Settings Edit
* 待完善:
* 待优化:
* 修改日期：2020.10.12
* 修改内容：
*   创建  HZH
*************************************************/
#ifndef STYLEWIDGETATTRIBUTE_H
#define STYLEWIDGETATTRIBUTE_H


class StyleWidgetAttribute
{
public:
    StyleWidgetAttribute();
    StyleWidgetAttribute(int style_w, int style_h, bool style_allRadius=1, int style_radius=0, int style_shadow =0,
                         double style_shadowAlpha=0.00, int style_titleHeight=0, int style_itemHeight=0, bool style_middle=true);
    int w=0; //窗口宽度
    int h=0; //窗口高度
    bool allRadius=1;//圆角模式
    int radius=0; //窗口圆角
    int shadow=10; //阴影宽度
    double shadowAlpha=0.08; //阴影透明度
    int titleHeight=0;//标题栏高度
    bool middle=true;//在屏幕中央显示
    int itemHeight=0;
    void setW(int width);
    void setH(int height);
};

#endif // STYLEWIDGETATTRIBUTE_H
