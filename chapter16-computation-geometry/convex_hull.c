/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: convex_hull.c
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: 凸包
时间	   	: 2020-10-19 14:10
***************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../tools/tools.h"
#include "../tools/log.h"
#include "../tools/geometry.h"

/* 函数指针, 用于比较优先级队列元素, 其返回值必须满足
    arg1 < arg2时， 返回值 < 0;
    arg1 == arg2时，返回值 = 0;
    arg1 > arg2时， 返回值 > 0. */
int compare(const void *arg1, const void *arg2)
{
    int ret = 0;
    Point __arg1 = *(Point *)arg1;
    Point __arg2 = *(Point *)arg2;

    if (!vequals(__arg1, __arg2))  
        if (vless(__arg1, __arg2))
            ret = -1;
        else
            ret = 1;

    return ret;
}

/* 向凸包中添加元素 */
static inline void push_back(Polygon *G, Point pt)
{
    G->pts[G->count++] = pt;
}
// #define push_back(G, pt)    ({   (G).pts[(G).count++] = cPoint((pt).x, (pt).y); })

/* 从凸包中删除元素 */
static inline void pop_back(Polygon *G) 
{
    G->count--;    
}

/**
 * convex_hull - 计算点集的凸包
 * @pts:        待计算点积的凸包	
 * @count:      点积中点的数目	
 * @H:          保存点积的凸包
 * @return:     无
 */
Polygon convex_hull(Point *pts, size_t count, Polygon *H)
{   
    int i, j;

    /* 1. 将点积按 x 排序 */
    Point *_pts = calloc_buf(count, Point);
    memcpy(_pts, pts, count *sizeof(Point));
    qsort(_pts, count, sizeof(Point), compare);

    /* 2. 确定凸包的上边界 */
    Polygon U;
    U.count = 0;
    U.pts = calloc_buf(count, Point);
    push_back(&U, _pts[0]);
    push_back(&U, _pts[1]);

    for (i = 2; i < count; ++i) {
        for (j = U.count; j >= 2; --j) { 
            /* 当待加入的点位于倒数第一, 二个点的逆时针方向, 则删除倒数第一个点, 加入该点 */
            if (COUNTER_CLOCKWISE == ccw(U.pts[j - 2], U.pts[j - 1], _pts[i])) {
                pop_back(&U);
            }
        }
        push_back(&U, _pts[i]);
    }

    printf("上边界\n");
    for (i = 0; i < U.count; ++i) 
        printf("%d %d\n", (int)U.pts[i].x, (int)U.pts[i].y);

    /* 3. 确定凸包的下边界 */
    Polygon L;
    L.count = 0;
    L.pts = calloc_buf(count, Point);
    push_back(&L, _pts[count - 1]);
    push_back(&L, _pts[count - 2]);
    pr_debug("压入: ");
    show_point(_pts[count - 1]);
    show_point(_pts[count - 2]);
    for (i = count - 3; i >= 0; --i) {
        pr_debug("处理: ");
        show_point(_pts[i]);
        for (j = L.count; j >= 2; --j) { 
            /* 当待加入的点位于倒数第一, 二个点的逆时针方向, 则删除倒数第一个点, 加入该点 */
            if (COUNTER_CLOCKWISE == ccw(L.pts[j - 2], L.pts[j - 1], _pts[i])) {
                pop_back(&L);
                pr_debug("弹出:　");
                show_point(L.pts[L.count]);
            }
        }
        push_back(&L, _pts[i]);
        pr_debug("压入: ");
        show_point(_pts[i]);

    }

    printf("下边界\n");
    for (i = 0; i < L.count; ++i) 
        printf("%d %d\n", (int)L.pts[i].x, (int)L.pts[i].y);

    /* 4. 合并上下边界 */
    H->count += U.count;
    memcpy(H->pts, U.pts, U.count * sizeof(Point));
    memcpy(H->pts + H->count, L.pts + 1, (L.count - 1 ) * sizeof(Point));
    H->count += (L.count - 2);

    free_buf(U.pts);
    free_buf(L.pts);
}

/* 测试:
7
2 1
0 0
1 2
2 2
4 2
1 3
3 3

 */
const int MAX = 100;
int main(int argc, char *argv[])
{
    // SET_DEFAULT_LEVEL(CONSOLE_LOGLEVEL_INFO);
    int n, i;
    int A[MAX];

    scanf("%d", &n);

    Point *pts = calloc_buf(n, Point);
    
    Polygon H;
    H.count = 0;
    H.pts = calloc_buf(n, Point);

    for (i = 0; i < n; ++i) 
        scanf("%lf %lf", &pts[i].x, &pts[i].y);

    convex_hull(pts, n, &H);

    printf("%d\n", H.count);

    printf("%d %d\n", (int)H.pts[0].x, (int)H.pts[0].y);
    for (i = H.count - 1; i >= 1; --i) 
        printf("%d %d\n", (int)H.pts[i].x, (int)H.pts[i].y);

    free_buf(pts);
    return 0;
}