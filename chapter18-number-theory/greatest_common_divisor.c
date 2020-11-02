/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: greatest_common_divisor.c
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: 欧几里得算法求最大公约数
时间	   	: 2020-11-02 20:28
***************************************************************/
#include <stdio.h>
#include "../tools/tools.h"
#include "../tools/log.h"

/**
 * gcd - 欧几里得算法求最大公约数
 * @x:  待求数	
 * @y:  待求数	
 * @return: 最大公约数
 */
int gcd(int x, int y)
{
    int r = 0;
    if (x < y)
        swap(&x, &y);
    
    while (y > 0) {
        r = x % y;
        x = y;
        y = r;
    }
    
    return x;
}

/* 测试:
147 105 
 */
int main(int argc, char *argv[])
{
    // SET_DEFAULT_LEVEL(CONSOLE_LOGLEVEL_INFO);
    int x, y;

    scanf("%d %d", &x, &y);

    double start = START();
    printf("%d 与 %d 的最大公约数为: %d\n", x, y, gcd(x, y));   
    FINISH(start);
    return 0;
}