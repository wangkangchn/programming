/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: is_prime.c
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: 质数检验
时间	   	: 2020-11-02 19:21
***************************************************************/
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "../tools/tools.h"
#include "../tools/log.h"

/**
 * is_prime - 质数检验
 * @x:      待检验数	
 * @return: true: 质数
 */
bool is_prime(int x)
{
    bool ret = true;
    int upper = 0;
    int i = 0;

    if (x > 2) {
        if ( !(x % 2) ) {
            ret = false;
            return ret;
        }

        /* 对于大于 2 的整数, 只要能被 2 ~ x ^(1/2) 中的任意整数整除, 就说明该数不是质数  */
        upper = (int)sqrt(x);
        for ( i = 3; i <= upper; i += 2) {
            if (x % i) {
                ret = false;
                break;
            }
        }
    } else if (x == 2) { 
        ;
    } else if ( x < 2 ) { 
        ret = false;
    }
    
    return ret;
}

/**
 * eratos - 埃拉托色尼筛选法列举指定范围内的所有质数
 * @x:      范围上界 	
 * @buf:    存储范围内的质数
 * @buf_size:    buf 大小
 * @return: 范围内质数的个数
 */
int eratos(int x, int *buf, size_t buf_size)
{
    /* isprime 下标为待检测整数
        isprime 值标识该整数是否为质数 */
    bool *isprime = calloc_buf(x, bool);
    int i = 0, j = 0;
    int count = 0;

    for (i = 2; i <= x; ++i) {
        isprime[i] = true;
    }

    for (i = 2; i <= x; ++i) {
        if (!isprime[i])
            continue;

        /* 保留最小整数, 删除最小整数的倍数 */
        for (j = i + i; j <= x; j += i) {
            isprime[j] = false;
        }
    }
    
    for (i = 2, j = 0; i <= x && i < buf_size; ++i) {
        if (isprime[i]) {
            buf[j++] = i;
            ++count;
        }
    }
    free_buf(isprime);
    return count;
}

/* 
测试:
6
2
3
4
5
6
7


 */
const int MAX = 100;
int main(int argc, char *argv[])
{
    // SET_DEFAULT_LEVEL(CONSOLE_LOGLEVEL_INFO);
    int n, i;
    int x = 0; 
    int count = 0;

    // scanf("%d", &n);

    // for (i = 0; i < n; ++i) {
    //     scanf("%d", &x);
    //     count += is_prime(x);
    
    // }

    // printf("%d\n", count);

    x = 60;
    printf("%d 以内的质数有 ", x);
    int *buf = calloc_buf(MAX, int);

    count = eratos(x, buf, MAX);
    printf("%d 个:\n", count);
    trace(buf, count);

    free_buf(buf);
    return 0;
}