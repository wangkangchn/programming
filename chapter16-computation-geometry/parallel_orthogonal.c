/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: parallel_orthogonal.c
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: 直线正交/平行的判定
时间	   	: 2020-10-05 15:00
***************************************************************/
#include <stdio.h>
#include <stdbool.h>
#include "../tools/tools.h"
#include "../tools/log.h"
#include "geometry.h"

/**
 * is_parallel - 判断两直线是否平行 |a x b| == 0 
 * @p11:    line1 中的第一个点	
 * @p12:    line1 中的第二个点	
 * @p21:    line2 中的第一个点	
 * @p22:    line2 中的第二个点	
 * @return: 平行返回 true, 否则返回 false
 */
static inline bool is_parallel(Point p11, Point p12, Point p21, Point p22) 
{
    return equals(vcross(vsub(p12, p11), vsub(p22, p21)),  0.0);
}


/**
 * is_parallel - 判断两直线是否垂直 a . b == 0 
 * @p11:    line1 中的第一个点	
 * @p12:    line1 中的第二个点	
 * @p21:    line2 中的第一个点	
 * @p22:    line2 中的第二个点	
 * @return: 垂直返回 true, 否则返回 false
 */
static inline bool is_orthogonal(Point p11, Point p12, Point p21, Point p22) 
{
    return equals(vdot(vsub(p12, p11), vsub(p22, p21)), 0.0);
}

/* 测试:
3
0 0 3 0 0 2 3 2
0 0 3 0 1 1 1 4
0 0 3 0 1 1 2 2

 */
const int MAX = 100;
int main(int argc, char *argv[])
{
    // SET_DEFAULT_LEVEL(CONSOLE_LOGLEVEL_INFO);
    int n, q; 
    int i, result;
    Point p1, p2, p3, p4;

    scanf("%d", &n);

    for (i = 0; i < n; ++i) {
        scanf("%lf %lf %lf %lf %lf %lf %lf %lf", &p1.x, &p1.y, &p2.x, &p2.y, &p3.x, &p3.y, &p4.x, &p4.y);
        result = 0;
        if (is_orthogonal(p1, p2, p3, p4)) {
            result = 1;
        }
        if (is_parallel(p1, p2, p3, p4)) {
            result = 2;
        }
        printf("%d\n", result);
    }

    return 0;
}