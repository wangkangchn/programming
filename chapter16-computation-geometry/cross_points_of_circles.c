/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: cross_points_of_circles.c
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: 计算两圆的交点
时间	   	: 2020-10-11 09:10
***************************************************************/
#include <stdio.h>
#include <math.h>
#include "../tools/tools.h"
#include "../tools/log.h"
#include "../tools/geometry.h"

/**
 * angle - 计算向量与 x 轴的夹角
 * @v:      待计算向量	
 * @return: 夹角的弧度值
 */
static inline double angle(Vector v)
{
    return atan2(v.y, v.x); // 一定要记住的是向量没有起点, 只有大小和方向
}
/**
 * polar - 将极坐标转换为直角坐标
 * @theta:  极角	
 * @rho:    极径	
 * @return: 直角坐标
 */
static inline Point polar(double theta, double rho)
{
    return cPoint(cos(theta) * rho, sin(theta) * rho);
}

/**
 * cross_point_cc - 两圆的交点
 * @c1:     第一个圆	
 * @c2:     第二个圆	
 * @return: 无
 */
void cross_point_cc(Circle c1, Circle c2)
{
    /* 1. 计算圆心矩 */
    double d = vabs(vsub(c2.c, c1.c));

    /* 2. 根据余弦定理计算圆心交点与圆心连线的夹角 */
    double alpha = acos((c1.r * c1.r + d * d - c2.r * c2.r) / (2 * c1.r * d));

    /* 3. 计算圆心连线与 x 轴的夹角 */
    double beta = angle(vsub(c2.c, c1.c));

    /* 4. 计算交点, c1.c ± (alpha + beta) */
    show_point(vadd(c1.c, polar(alpha + beta, c1.r)));
    show_point(vadd(c1.c, polar(-1 * alpha + beta, c1.r)));
}

/* 测试:
0 0 2
2 0 2

 */
const int MAX = 100;
int main(int argc, char *argv[])
{
    int q, i;
    Circle c1, c2;

    scanf("%lf %lf %lf", &c1.c.x, &c1.c.y, &c1.r);
    scanf("%lf %lf %lf", &c2.c.x, &c2.c.y, &c2.r);
    cross_point_cc(c1, c2);
}