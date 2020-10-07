/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: intersection.c
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: 判断两线段是否相交
时间	   	: 2020-10-07 09:44
***************************************************************/
#include <stdio.h>
#include <stdbool.h>
#include "../tools/tools.h"
#include "../tools/log.h"
#include "../tools/geometry.h"

typedef enum LOCATION {
    COUNTER_CLOCKWISE = 1,
    CLOCKWISE = -1,
    ONLINE_BACK = 2,
    ONLINE_FRONT = -2,
    ON_SEGMENT = 0,
} LOCATION;


/**
 * ccw - 判断 p0, p1, p2 三个点的顺序
 * @p0, p1, p2: 待计算点	
 * @return: 
 *       p0, p1, p2 成顺时针, 返回 CLOCKWISE
 *       p0, p1, p2 成逆时针, 返回 COUNTER_CLOCKWISE
 *       p2, p0, p1 依次排列在同一条直线上(即 p2 位于 线段p0p1的左后方), 返回 ONLINE_BACK
 *       p0, p1, p2 依次排列在同一条直线上(即 p2 位于 线段p0p1的右前方), 返回 ONLINE_FRONT
 *       p0, p2, p1 依次排列在同一条直线上(即 p2 位于 线段p0p1的内部), 返回 ON_SEGMENT
 */
LOCATION ccw(Point p0, Point p1, Point p2)
{
    LOCATION result;
    Vector v01 = vsub(p1, p0);
    Vector v02 = vsub(p2, p0);

    /* 因为叉乘满足右手定则, 当 cross(a, b) > 0 逆时针, < 0 顺时针 */
    if (vcross(v01, v02) > EPSILON)
        result = COUNTER_CLOCKWISE;
    else if (vcross(v01, v02) < -1 * EPSILON)
        result = CLOCKWISE;
    
    /* 下面为三点在一条线上 */
    else if (vdot(v01, v02) < -1 * EPSILON)
        result = ONLINE_BACK;
    else if (vabs(v01) < vabs(v02))
        result = ONLINE_FRONT;
    else
        result = ON_SEGMENT;
    
    return result;
}

/**
 * intersect - 判断两直线是否相交
 * @l1:     第一条直线	
 * @l2:     第二条直线	
 * @return: 相交返回 true, 不相交返回 false
 */
bool intersect(Line l1, Line l2)
{   
    /* < 0 说明点位于直线的两侧, == 0 说明点位于直线上 */
    return (
        (ccw(l1.p1, l1.p2, l2.p1) * ccw(l1.p1, l1.p2, l2.p2) <= 0) &&
        (ccw(l2.p1, l2.p2, l1.p1) * ccw(l2.p1, l2.p2, l1.p2) <= 0)
    );
}

/* 测试:
3 
0 0 3 0 1 1 2 -1
0 0 3 0 3 1 3 -1
0 0 3 0 0 -2 5 0

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
        printf("%d\n", intersect(s1, s2));
    }

    return 0;
}