/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: knapsack_problem.c
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: 背包问题, 在一定容量的前提下装价值最大的货物
时间	   	: 2020-11-04 14:27
***************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../tools/tools.h"
#include "../tools/log.h"

typedef struct {
    int w, v;
} Good;

/* 
    arg1 == arg2:   0
    arg1 < arg2:    -1
    arg1 > arg2:    1
    */
int compare(const void *arg1, const void *arg2)
{
    Good __arg1 = *(Good *)arg1;
    Good __arg2 = *(Good *)arg2;

    if (__arg1.w < __arg2.w)        return -1;
    else if (__arg1.w > __arg2.w)   return 1;
    else {
        if (__arg1.v > __arg2.v)    return -1;
        else if (__arg1.v < __arg2.v)    return 1;
        else return 0;
    }
}

/**
 * max_value - 最大价值
 * @goods:  货物集
 * @ngood:  货物个数
 * @W:      容量
 * @return: 装载货物的最大价值
 */
int max_value(Good *goods, size_t ngood, int W)
{   
    Good *__goods = calloc_buf(ngood, Good);
    memcpy(__goods, goods, ngood * sizeof(Good));

    int *V = calloc_buf(W + 1, int);
    int i = 0, j = 0;
    int current_w = 0;
    int w = 0, v = 0;

    /* 将货物按重量升序排序, 相同的价值大的在前 */
    qsort(__goods, ngood, sizeof(Good), compare);

    for (i = 1; i <= W; ++i) {
        current_w = 0;
        for (j = 0; j < ngood; ++j) {
            w = __goods[j].w;
            if (w > i) 
                break;
            v = __goods[j].v;
            if (i - current_w - w >= 0) {
                V[i] += v;
                current_w += w;
            } else {
                /* 取丢弃相同的货物加上该货物的价值, 与当前货物的价值大值 */
                V[i] = max(V[i], V[current_w - w] + v);
            }
        }
    }
    
    current_w = V[W];
    free_buf(V);
    free_buf(__goods);
    return current_w;
}

/* 测试:
4 5
4 2 
5 2 
2 1
8 3

0.032388000 seconds
 */
int main(int argc, char *argv[])
{
    // SET_DEFAULT_LEVEL(CONSOLE_LOGLEVEL_INFO);
    int v = 0, w = 0;
    int n = 0, W = 0;
    int i = 0;

    scanf("%d %d", &n, &W);
    Good *goods = calloc_buf(n, Good);

    for (i = 0; i < n; ++i) 
        scanf("%d %d", &goods[i].v, &goods[i].w);

    double start = START();
    printf("容量为 %d 时所能装载货物的最大价值为: %d\n", W, max_value(goods, n, W));
    FINISH(start);

    free_buf(goods);
    return 0;
}