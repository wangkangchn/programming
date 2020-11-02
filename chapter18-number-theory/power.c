/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: power.c
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: 幂乘
时间	   	: 2020-11-02 20:34
***************************************************************/
#include <stdio.h>
#include "../tools/tools.h"
#include "../tools/log.h"

/**
 * pos - 反复平方法求幂乘与 M 的余数
 * @m:  底数	
 * @n:  幂	
 * @M:  除数	
 * @return: 结果
 */
long long int pos(int m, int n, long long int M)
{   
    long long res = 1;
    while (n > 0) {
        /* 奇数 */
        if (n & 1) res = res * m % M;
        m = m * m % M;
        n >>= 1;    /* 减小两倍 */
    }
    
    return res;
}

/* 
5 8
 */
int main(int argc, char *argv[])
{
    // SET_DEFAULT_LEVEL(CONSOLE_LOGLEVEL_INFO);
    int m = 0, n = 0;
    long long int M = 1000000007;

    scanf("%d %d", &m, &n);

    printf("%d 的 %d 次方对 %lld 取余为: %lld\n", m, n, M, pos(m, n, M));
    return 0;
}