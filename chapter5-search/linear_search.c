/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: linear_search.c
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: 线性搜索
时间	   	: 2020-08-26 20:27
***************************************************************/
#include <stdio.h>

#include "../tools.h"

/**
 * linear_search - 线性搜索(不带标记)
 * @A:	    待搜索数组
 * @num:    A的个数
 * @key:    欲搜索的键值
 * @return: 搜索到key返回1, 否则返回0
 */
int linear_search(int A[], int num, int key)
{   
    int i;
    for (i = 0; i < num; ++i) {
        if (A[i] != key)
            continue;
        break;
    }
    return i != num;
}

/**
 * linear_search_flag - 线性搜索(带标记)
 * @A:	    待搜索数组
 * @num:    A的个数
 * @key:    欲搜索的键值
 * @return: 搜索到key返回1, 否则返回0
 */
int linear_search_flag(int A[], int num, int key)
{   
    int i = 0;
    A[num] = key;   /* 这种方式好简答 */
    while (A[i] != key) 
        ++i;

    return i != num;
}

const int MAX = 100;
int main(int argc, char *argv[])
{
    int n = 0, q = 0, i = 0, j = 0;
    int S[MAX], key;
    int count = 0;

    scanf("%d", &n);

    for (i = 0; i < n; ++i) 
        scanf("%d", &S[i]);

    scanf("%d", &q);

    for (i = 0; i < q; ++i) {
        scanf("%d", &key);
        count += linear_search_flag(S, n, key);
    }
    printf("%d\n", count);

    return 0;
}

