/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: cross_point_of_a_circle_and_a_line.c
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: 圆与直线的交点
时间	   	: 2020-10-09 13:51
***************************************************************/
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include "../tools/tools.h"
#include "../tools/log.h"
#include "../tools/geometry.h"

/**
 * intersect_cl - 判断圆直线是否相交
 * @param:	
 * @return: 成功返回0, 失败返回-1
 */
#define intersect_cl(c, l) ({ distance_pl(c.c, l) <= c.r; })

/**
 * cross_point_cl - 计算圆与直线的交点
 * @c:      圆
 * @l:      直线	
 * @return: 无
 */
void cross_point_cl(Circle c, Line l)
{
    assert(intersect_cl(c, l));
    Point pr = projection(c.c, (Segment)l);  /* 圆心在直线上的投影 */
    Vector e = vdiv(vsub(l.p2, l.p1), vabs(vsub(l.p2, l.p1)));                    /* 直线l的单位向量 */
    double d = sqrt(c.r * c.r - vnorm(vsub(pr, c.c)));     /* 切线长的一半 */
    Point p1 = vadd(pr, vmul(e, d));
    Point p2 = vsub(pr, vmul(e, d));

    if (vless(p1, p2))
        printf("%lf %lf %lf %lf\n", p1.x, p1.y, p2.x, p2.y);
    else
        printf("%lf %lf %lf %lf\n", p2.x, p2.y, p1.x, p1.y);
}


/* 测试:
2 1 1
2
0 1 4 1
3 0 3 3

 */
const int MAX = 100;
int main(int argc, char *argv[])
{
    // SET_DEFAULT_LEVEL(CONSOLE_LOGLEVEL_INFO);
    int q, i;
    Circle c;
    Line l;

    scanf("%lf %lf %lf", &c.c.x, &c.c.y, &c.r);
    scanf("%d", &q);

    for (i = 0; i < q; ++i) { 
        scanf("%lf %lf %lf %lf", &l.p1.x, &l.p1.y, &l.p2.x, &l.p2.y);
        cross_point_cl(c, l);
    }

    return 0;
}