/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: cross_point.c
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: 两线段交叉点
时间	   	: 2020-10-09 13:40
***************************************************************/
#include <stdio.h>
#include "../tools/tools.h"
#include "../tools/log.h"
#include "../tools/geometry.h"

/**
 * cross_point - 计算两线段的交点
 * @s1, s2: 线段	
 * @return: 交点坐标
 */
Point cross_point(Segment s1, Segment s2)
{
    Vector base = vsub(s2.p2, s2.p1);
    Vector hypo1 = vsub(s1.p1, s2.p1);
    Vector hypo2 = vsub(s1.p2, s2.p1);
    double t = fabs(vcross(base, hypo1)) / (fabs(vcross(base, hypo1)) + fabs(vcross(base, hypo2)));
    return vadd(s1.p1, vmul(vsub(s1.p2, s1.p1), t)); 
}

/* 测试:
3 
0 0 2 0 1 1 1 -1
0 0 1 1 0 1 1 0
0 0 1 1 1 0 0 1

 */
const int MAX = 100;
int main(int argc, char *argv[])
{
    // SET_DEFAULT_LEVEL(CONSOLE_LOGLEVEL_INFO);
    int q, i;
    Segment s1, s2;

    scanf("%d", &q);
    
    for (i = 0; i < q; ++i) { 
        scanf("%lf %lf %lf %lf", &s1.p1.x, &s1.p1.y, &s1.p2.x, &s1.p2.y);
        scanf("%lf %lf %lf %lf", &s2.p1.x, &s2.p1.y, &s2.p2.x, &s2.p2.y);
        show_point(cross_point(s1, s2));
    }

    return 0;
}