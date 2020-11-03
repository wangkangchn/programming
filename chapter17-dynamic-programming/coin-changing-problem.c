/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: coin-changing-problem.c
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: 硬币问题, 求获得指定的钱数所需的最少硬币数
时间	   	: 2020-11-03 08:41
***************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../tools/tools.h"
#include "../tools/log.h"

int compare(const void *arg1, const void *arg2)
{
    int __arg1 = *(int *)arg1;
    int __arg2 = *(int *)arg2;

    if (__arg1 == __arg2)   return 0;
    else if (__arg1 < __arg2)           return -1;
    else                                return 1;
}


/**
 * get_number_of_coin - 在硬币集 coins 中, 求获得指定钱数 n 所需的硬币数
 * @n:              待获取的金额	
 * @coins:          硬币集	
 * @coins_size:     硬币集中硬币的个数	
 * @return:         硬币个数
 */
int get_number_of_coin(int n, int *coins, size_t coins_size)
{   
    int count = 0;
    int  res = 0;

    for (size_t i = coins_size; i >= 0; --i) {
        res = n - coins[i];
        if (res > 0) { 
            ++count;
            n -= coins[i];
            ++i;
        } else if (res == 0) {
            ++count;
            break;
        }
    }
    
    return count;
}

/**
 * get_least_number_of_coin - 在给定的硬币集中获取指定钱数 n 的最小硬币个数
 * @n:              待获取的金额	
 * @coins:          硬币集	
 * @coins_size:     硬币集中硬币的个数	
 * @return:         最少硬币个数
 */
int get_least_number_of_coin(int n, int *coins, size_t coins_size)
{   
    int i = 0;
    int count = 0;
    int *counts = calloc_buf(coins_size, int);
    
    for (size_t i = coins_size; i >= 1; --i) {
        counts[i-1] = get_number_of_coin(n, coins, i);
    }

    qsort(counts, coins_size, sizeof(int), compare);
    
    for (i = 0; i < coins_size; ++i) {
        count = counts[i];
        // printf("%d\n", count);
        if (count > 0) 
            break;
    }

    free_buf(counts);
    return count;
}

/**
 * get_least_number_of_coin_dp - 使用动态规划求解硬币问题
 * @n:              待获取的金额	
 * @coins:          硬币集	
 * @coins_size:     硬币集中硬币的个数	
 * @return:         最少硬币个数
 */
int get_least_number_of_coin_dp(int n, int *coins, size_t coins_size)
{   
    int i = 0, j = 0;

    unsigned int *T = malloc(n * sizeof(unsigned int));
    memset(T, 0xff, n * sizeof(unsigned int));
    T[0] = 0;

    /* 1. 计算使用 0 ~ i 种硬币支付 j 元的最少硬币个数 */
    for (i = 0; i < coins_size; ++i) {
        /* 支付 j 元时分为使用第 i 种硬币和不使用第 i 种硬币, 比较的就是这两种情况中的小值 */
        for (j = coins[i]; j < n; ++j) {
            /* 之前 T[j] 保存的是未使用 coins[i] 的最小硬币数 */
            T[j] = min(T[j], T[j - coins[i]] + 1);
        }
    }
    return T[n-1];
}
/* 测试:
15 6
1 2 7 8 12 50

 */
const int MAX = 100;
int main(int argc, char *argv[])
{
    // SET_DEFAULT_LEVEL(CONSOLE_LOGLEVEL_INFO);
    int m, n, i;
    int *coins = NULL;

    scanf("%d %d", &n, &m);
    coins = calloc_buf(m, int);

    for (i = 0; i < m; ++i)  
        scanf("%d", &coins[i]);

    double start = START();
    
    printf("%d\n", get_least_number_of_coin(n, coins, m));
    printf("%d\n", get_least_number_of_coin_dp(n, coins, m));


    FINISH(start);
    free_buf(coins);
    return 0;
}