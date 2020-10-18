/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: polygon_point_containment.c
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: 计算点的内包
时间	   	: 2020-10-18 09:22
***************************************************************/
#include <stdio.h>
#include <stdbool.h>
#include "../tools/tools.h"
#include "../tools/log.h"
#include "../tools/geometry.h"

/**
 * contains - 判断一个点是否在多边形内
 * @g:	    多边形
 * @p:      待确定点
 * @return: p 在 g 内返回 2, p 在 g 的边上返回 1, 否则返回 0 
 */
int contains(Polygon g, Point p)
{
    int n = g.count;
    Point *pts = g.pts;
    bool x = false;
    Point a, b;
    for (size_t i = 0; i < n; ++i) {
        a = vsub(pts[i], p);
        b = vsub(pts[i + 1], p);
        pr_debug("fabs(vcross(a, b)): %lf\n", fabs(vcross(a, b)));
        pr_debug("vdot(a, b):　%lf\n", vdot(a, b));
        if (fabs(vcross(a, b)) < EPSILON && vdot(a, b) < EPSILON) {
            return 1;
        }

        if (a.y > b.y)
            swap(&a, &b);
        
        /* 判断射线是否穿过边, 奇数为 true 
        a.y < EPSILON && b.y > EPSILON 保证设想不和 gi gi+1 的端点相交 */
        if (a.y < EPSILON && b.y > EPSILON && vcross(a, b) > EPSILON)
            x = x ? false : true;
    }
    return x ? 2 : 0;
}
/* 测试:
4 
0 0
3 1
2 3
0 3
3 
2 1
0 2
3 2

  */
const int MAX = 100;
int main(int argc, char *argv[])
{
    SET_DEFAULT_LEVEL(CONSOLE_LOGLEVEL_INFO);
    int i;
    int n, q;
    Polygon g;
    Point p;

    scanf("%d", &n);
    g.pts = calloc_buf(n, Point);
    g.count = n;

    for (i = 0; i < n; ++i) 
        scanf("%lf %lf", &g.pts[i].x, &g.pts[i].y);
    
    scanf("%d", &q);
    for (i = 0; i < q; ++i) {
        scanf("%lf %lf", &p.x, &p.y);
        printf("%d\n", contains(g, p));
    }
    double start = START();
    
    FINISH(start);
    free_buf(g.pts);
    return 0;
}