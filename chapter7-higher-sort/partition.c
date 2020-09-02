/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: partition.c
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: 分割 
            因为要遍历整个数组, 所以算法复杂度为 O(n)
时间	   	: 2020-09-01 19:23
***************************************************************/
#include <stdio.h>
#include "../tools/tools.h"
#include "../tools/log.h"



/**
 * partition - 分割數組, 使數組数组中下标小于q的元素均小于等于A[q], 下标大于q的元素均大于A[q]
 * @A:      待分割的数组
 * @left:   左边界(闭)	
 * @right:  右边界(开)
 * @return: q的下标
 */
int partition(int *A, int left, int right)
{
    int x = A[right - 1];   /* 以最后一个元素为基准进行分割 */
    size_t i = left - 1;    /* i 指示前面最近一次小于等于x的位置 */
    size_t j = left;
    int temp;
    
    /* 不对最后一个元素进行判断 */
    for (; j < right - 1; ++j) { 
        /* 小于基准元素, 就将其置换到前面, ++i指定了前方交换的位置 */
        if (A[j] <= x) {
            pr_debug("交换前A[i] = %d, A[j] = %d\n", A[i+1], A[j]);
            ++i;  
            temp = A[i]; A[i] = A[j]; A[j] = temp;  
            pr_debug("交换后A[i] = %d, A[j] = %d\n", A[i], A[j]);
        }
    }
    ++i;
    temp = A[i]; A[i] = A[j]; A[j] = temp;  
    pr_debug("x = %d\n", x);

    return i;
}

const int MAX = 100;

int main(int argc, char *argv[])
{
    SET_DEFAULT_LEVEL(CONSOLE_LOGLEVEL_INFO);
    int n = 0, i;
    int A[] = {13,19,9,5,12,8,7,4,21,2,6,11};

    // scanf("%d", &n);

    // for (i = 0; i < n; ++i) 
    //     scanf("%d", &A[i]);
    i  = partition(A, 0, ARRAY_SIZE(A));

    for (size_t j = 0; j < ARRAY_SIZE(A); ++j) {
        if (j > 0) printf(" ");

        if (i == j) 
            printf("[%d]", A[j]);
        else
            printf("%d", A[j]);
    }
    printf("\n");
    return 0;
}