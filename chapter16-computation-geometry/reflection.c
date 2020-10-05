/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: reflection.c
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: 映象 (点)
时间	   	: 2020-10-05 17:06
***************************************************************/
#include <stdio.h>
#include "../tools/tools.h"
#include "../tools/log.h"
#include "../tools/geometry.h"

/**
 * projection - 点 p 在线段s上的投影
 * @p:      点
 * @s:      线段
 * @return: 投影点坐标
 */
static inline Point projection(Point p, Segment s)
{
    Vector segment = vsub(s.p2, s.p1);      /* 线段的向量表示 */
    double seg_length = vabs(segment);      /* 线段的长度 */
    double t = vdot((vsub(p, s.p1)), segment) / seg_length;  /* 点 p 在线段上的投影长度 */
    double r = t / seg_length;              /* 投影在线段所占的比例 */
    return vadd(s.p1, vmul(segment, r));
}

/**
 * reflection - 点 p 关于线段 s 的映象点 p'
 * @p:      点
 * @s:      线段
 * @return: 映象点 p'
 */
static inline Point reflection(Point p, Segment s)
{   
    /* 1. 首先求 p 在 s 上的投影点 */
    Point t = projection(p, s);

    /* 2. 将 p->pro_pt 放伸展 2 倍, 即为映象点坐标 */
    Vector pt = vsub(t, p);    /* Note: 需要注意的是向量只有方向和大小, 在不人为指定起点的情况下, 
                                向量是没有起点的 */
    Point p_ = vadd(p, vmul(pt, 2.0));
    return p_;
}

/* 测试:
0 0 3 4
3 
2 5
1 4
0 3

 */
int main(int argc, char *argv[])
{
    // SET_DEFAULT_LEVEL(CONSOLE_LOGLEVEL_INFO);
    int q, i;
    Segment s;
    Point p;

    scanf("%lf %lf %lf %lf", &s.p1.x, &s.p1.y, &s.p2.x, &s.p2.y);

    scanf("%d", &q);
    for (i = 0; i < q; ++i) { 
        scanf("%lf %lf", &p.x, &p.y);
        show_point(reflection(p, s));
    }

    double start = START();
    
    FINISH(start);
    return 0;
}