/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: fibonacci_number.c
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: 斐波那契数列(动态规划实现)
        Note:
            1. 使用记忆法实现, 快了不是一星半点
            2. 循环更快, 因为少了递归调用的栈操作
时间	   	: 2020-09-11 08:31
***************************************************************/
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include "../tools/tools.h"
#include "../tools/log.h"

/**
 * fib - 使用记忆化递归实现斐波那契数列
 * @n:      待计算的数	
 * @A:      记忆递归过程中计算的结果, 当再次遭遇之前计算的结果时, 直接使用
 *      不再次计算
 * @return: 返回指定数的计算结果
 */
int fib(int n, int *A)
{   
    if ((n == 1) || (n == 0)) 
        return A[n] = 1;
    
    if (A[n] != -1)
        return A[n];

    return A[n] = fib(n - 1, A) + fib(n - 2, A);
}


/**
 * fib1 - 递归实现斐波那契数列
 * @n:      待计算的数	
 * @return: 返回指定数的计算结果
 */
int fib1(int n)
{   
    if ((n == 1) || (n == 0))
        return 1;

    return fib1(n - 1) +fib1(n - 2);
}

const int MAX = 1000;
int main(int argc, char *argv[])
{
    // SET_DEFAULT_LEVEL(CONSOLE_LOGLEVEL_INFO);
    int n = 0, i;
    int A[MAX];

    scanf("%d", &n);

    memset(A, 0xff, (n+1) * sizeof(int));     /* 这样是初始化为-1 */


    double start = START();
    printf("动态规划: %d\n", fib(n, A));
    FINISH(start);

    start = START();
    printf("非动态规划: %d\n", fib1(n));
    FINISH(start);

    memset(A, 0xff, (n+1) * sizeof(int));
    start = START();
    printf("循环:");
    A[0] = A[1] = 1;
    for (i = 2; i <= n; ++i)
        A[i] = A[i-1] + A[i-2];
    printf("%d\n" ,A[n]);


    FINISH(start);

    return 0;
}