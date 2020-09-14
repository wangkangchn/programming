/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: matrix_chain_multiplication.c
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: 矩阵链乘法
时间	   	: 2020-09-14 20:38
***************************************************************/
#include <stdio.h>
#include <string.h>
#include "../tools/tools.h"
#include "../tools/log.h"

/**
 * matrix_chain_multiplication - 矩阵链乘法标量相乘的最小次数
 * @p:	    矩阵链中各个矩阵的形状 Mi = pi-1行 * p1列, p 的中元素个数为 count + 1
 * @count:  矩阵链中矩阵的个数
 * @return: 矩阵链乘法标量相乘的最小次数
 */
int matrix_chain_multiplication(int *p, size_t count)
{
    int i = 0, j = 0, k = 0;

    int m[count + 1][count + 1];    /* 保存 Mi...Mj 相乘的最小代价(乘法次数) */
    memset(m, 0, (count + 1) * (count + 1) * sizeof(int));

    /* 因为求长的矩阵链时需要用到短矩阵链的最小代价, 所以再求长矩阵链之前要先算处端的矩阵链的最小代价,
    因此这个 for 循环就从最短的 2 个矩阵相乘开始, 两矩阵相乘最小代价就是从左到右标量相乘的次数 */
    for (int num = 2; num <= count; ++num) {

        /* 这个循环保证从左到右能够遍历所有连续 num 个矩阵相乘 */
        for (i = 1; i <= count - num + 1; ++i) {
            /* 此次矩阵链的右边界 */
            j = i + num - 1;    
            m[i][j] = (1 << 21);    /* 先保存一个最大代价 */

            /* 因为在一般情况下矩阵链乘法 (MiMi+1...Mj) 的最优解就是 (MiMi+1...Mk)(Mk1...Mj) 的最小成本, 
            所以在此循环中, k 从 1 开始计算*/
            for (k = i; k <= j - 1; ++k) {
                /* 此时 (Mi...Mj) 的最小代价为, m[i][k] + m[k+1][j] + 前面两部分相乘的代价 和 之前计算的 m[i][j] 的最小值, 
                在这一步中是计算 k 中情况的最小代价 */
                m[i][j] = min(m[i][j], m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j]);
            }
        }
    }

    return m[1][count];
}

/* 测试:
6
30 35
35 15
15 5
5 10
10 20
20 25
 */
const int MAX = 100;
int main(int argc, char *argv[])
{
    // SET_DEFAULT_LEVEL(CONSOLE_LOGLEVEL_INFO);
    int n = 0, i;

    scanf("%d", &n);

    int p[n + 1];           /* 保存 n 个矩阵的形状 Mi = pi-1行 * p1列 */
    memset(p, 0, (n + 1) * sizeof(int));

    for (i = 1; i <= n; ++i) 
        scanf("%d %d", p + i - 1, p + i);

    double start = START();
    printf("%d\n", matrix_chain_multiplication(p, n));
    FINISH(start);
    return 0;
}