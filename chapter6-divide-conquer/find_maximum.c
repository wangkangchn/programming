/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: find_maximum.c
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: 分治法求解最大值
时间	   	: 2020-08-31 11:26
***************************************************************/
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "../tools/tools.h"

#define max(Val1, Val2) ({ Val1 >= Val2 ? Val1 : Val2; })
/**
 * function - 分治法求解最大值
 * @A:      待求解数组
 * @left:   A数组左边界
 * @right:  A数组右边界(不包含)	
 * @return: 成功返回0, 失败返回-1
 */
int find_max(int *A, int left, int right)
{
    int m = (left + right) / 2; /* 分组求解 */

    /* 递归退出条件: 当A只有一个数时退出 */
    if (left == (right - 1)) return A[m];

    /* 左右分别求解 */
    return max(find_max(A, left, m), find_max(A, m, right));      /* 聚合 */
}

int compare(const void *arg1, const void *arg2)
{
    int key = *(int *)(arg1);
    int item = *(int *)(arg2);
    if (key < item)
        return -1;
    else if (key == item)
        return 0;
    else
        return 1;
}

const int MAX = 100;

int main(int argc, char *argv[])
{
    int n = 0, i, count = 0, start;
    int A[] = {1, 8, 87, 54, 2, 4, 5, 3321, 45, 87};

    /* 很慢 */
    start = clock();
    printf("max: %d\n", find_max(A, 0, ARRAY_SIZE(A)));
    printf( "find_max: %f seconds\n", (double)(clock() - start) / CLOCKS_PER_SEC);

    start = clock();

    qsort(A, ARRAY_SIZE(A), sizeof(int), compare);
    printf( "qsort: %f seconds\n", (double)(clock() - start) / CLOCKS_PER_SEC);


    return 0;
}