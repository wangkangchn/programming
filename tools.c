/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: tools.c
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: 
时间	   	: 2020-08-19 15:42
***************************************************************/
#include <stdio.h>
#include "tools.h"

/**
 * trace - 按顺序输出数组元素
 * @A:      待排序数组	
 * @num:    数组元素个数
 * @return: 无
 */
void trace(int A[], int num) 
{
    int i;
    for (i = 0; i < num; ++i) {
        if (i > 0) printf(" "); /* 仅在量元素之间输出空格 */
        printf("%d", A[i]);
    }
    printf("\n");
}

/**
 * swap - 交换数组元素
 * @A:      待交换元素的数组	
 * @num:    数组长度
 * @i:      待交换元素下标
 * @j:      待交换元素下标
 * @return: 成功返回0, 失败返回-1
 */
inline int swap(int A[], int num, int i, int j)
{
    if (i < num && j < num) {
        int temp = A[j];
        A[j] = A[i];
        A[i] = temp;
        return 0;
    } else 
        return -1;
}