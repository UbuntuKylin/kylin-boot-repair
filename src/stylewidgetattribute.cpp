/************************************************
* 文件描述: In User Settings Edit
* 待完善:
* 待优化:
* 修改日期：2020.10.12
* 修改内容：
*   创建  HZH
*************************************************/
#include "stylewidgetattribute.h"

/************************************************
* 函数名称：
* 功能描述：
* 输出参数：
* 修改日期：2020.10.12
* 修改内容：
*   创建  HZH
*
*************************************************/
StyleWidgetAttribute::StyleWidgetAttribute()
{

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
StyleWidgetAttribute::StyleWidgetAttribute(int style_w, int style_h, bool style_allRadius, int style_radius,int style_shadow,
                                           double style_shadowAlpha, int style_titleHeight, int style_itemHeight, bool style_middle)
{
    w=style_w+style_shadow*2;
    h=style_h+style_shadow*2;
    allRadius=style_allRadius;
    radius=style_radius;
    shadow=style_shadow;
    shadowAlpha=style_shadowAlpha;
    titleHeight=style_titleHeight;
    itemHeight=style_itemHeight;
    middle=style_middle;
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
void StyleWidgetAttribute::setW(int width)
{
    w=width+shadow;
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
void StyleWidgetAttribute::setH(int height)
{
    h=height+shadow;
}
