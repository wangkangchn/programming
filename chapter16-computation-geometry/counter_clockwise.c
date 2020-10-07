/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: counter_clockwise.c
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: 逆时针方向
时间	   	: 2020-10-07 09:47
***************************************************************/
#include <stdio.h>
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

/* 测试：
0 0 2 0
5
-1 1 
-1 -1 
-1 0
0 0 
3 0

 */
const int MAX = 100;
int main(int argc, char *argv[])
{
    // SET_DEFAULT_LEVEL(CONSOLE_LOGLEVEL_INFO);
    int q, i;
    Point p0, p1, p2;

    scanf("%lf %lf %lf %lf", &p0.x, &p0.y, &p1.x, &p1.y);

    scanf("%d", &q);
    for (i = 0; i < q; ++i) { 
        scanf("%lf %lf", &p2.x, &p2.y);
        switch (ccw(p0, p1, p2))
        {
        case COUNTER_CLOCKWISE:
            printf("COUNTER_CLOCKWISE\n");
            break;

        case CLOCKWISE:
            printf("CLOCKWISE\n");
            break;

        case ONLINE_BACK:
            printf("ONLINE_BACK\n");
            break;

        case ONLINE_FRONT:
            printf("ONLINE_FRONT\n");
            break;

        case ON_SEGMENT:
            printf("ON_SEGMENT\n");
            break;
        
        default:
            break;
        }
    }

    double start = START();
    
    FINISH(start);
    return 0;
}