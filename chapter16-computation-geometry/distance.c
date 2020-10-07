/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: distance.c
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: 计算线段 s1 与 s2 间的距离
时间	   	: 2020-10-07 09:02
***************************************************************/
#include <stdio.h>
#include "../tools/tools.h"
#include "../tools/log.h"
#include "../tools/geometry.h"

/**
 * distance_pp - 计算两点间的距离
 * @p1:     第一个点	
 * @p2:     第二个点	
 * @return: 两点间的距离
 */
static inline double distance_pp(Point p1, Point p2)
{
    return vabs(vsub(p2, p1));
}

/**
 * distance_pl - 计算点与直线间的距离
 * @p:     点	
 * @l:     直线	
 * @return: 点与直线间的距离
 */
static inline double distance_pl(Point p, Line l)
{
    Vector vl = vsub(l.p2, l.p1);   /* 直线 l 的方向向量 */
    Vector vpl = vsub(p, l.p1);    /* 向量 pp1 */
    return fabs(vcross(vl, vpl) / vabs(vl));
}

/**
 * distance_ps - 计算点与线段间的距离
 * @p:     点	
 * @s:     线段	
 * @return: 点与线段间的距离
 */
static inline double distance_ps(Point p, Segment s)
{
    double dist = 0.0;
    Vector vl = vsub(s.p2, s.p1);   /* 直线 l 的方向向量 */
    Vector vpp1 = vsub(p, s.p1);    /* 向量 pp1 */
    Vector vpp2 = vsub(p, s.p2);    /* 向量 pp2 */

    /* Note: 注意要同一起点!!! */
    if (vdot(vsub(s.p2, s.p1), vsub(p, s.p1)) < 0)          dist = distance_pp(p, s.p1);
    else if (vdot(vsub(s.p1, s.p2), vsub(p, s.p2)) < 0)     dist = distance_pp(p, s.p2);
    else                                                    dist = distance_pl(p, s);

    return dist;
}

/**
 * distance_ss - 计算线段与线段间的距离
 *      线段间的距离为:
 *  1. 相交, 距离为0
 *  2. s1.p1 与 s2 的距离, s1.p2 与 s2 的距离, s2.p1 与 s1 的距离, s2.p2 与 s1 的距离的最小值 
 * @s1:     线段	
 * @s2:     线段	
 * @return: 线段与线段间的距离
 */
static inline double distance_ss(Segment s1, Segment s2)
{
    double dist = 0.0;
    if (!intersect(s1, s2)) {
        dist = min(
                min(distance_ps(s1.p1, s2), distance_ps(s1.p2, s2)), 
                min(distance_ps(s2.p1, s1), distance_ps(s2.p2, s1))
                );
    }
    return dist;
}

/* 测试:
3 
0 0 1 0 0 1 1 1
0 0 1 0 2 1 1 2
-1 0 1 0 0 1 0 -1

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
        printf("%f\n", distance_ss(s1, s2));
    }

    return 0;
}