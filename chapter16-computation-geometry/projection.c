/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: projection.c
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: 投影
时间	   	: 2020-10-05 16:23
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

/* 测试:
0 0 3 4
1 
2 5

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
        show_point(projection(p, s));
    }

    double start = START();
    
    FINISH(start);
    return 0;
}