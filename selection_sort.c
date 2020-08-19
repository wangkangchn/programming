/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: selection_sort.c
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: 插入排序
时间	   	: 2020-08-19 20:29
***************************************************************/
/* Note:
    1. 不稳定排序
    2. O(N^2)
    3. 不管数据是什么顺序, 该比较多少次就比较多少次, 不会减少 */
#include <stdio.h>
#include "tools.h"
#include <math.h>
static const int MAX = 100;

/**
 * selection_sort - 选择排序, 升序
 * @A:      待排序数组	
 * @num:    数组元素个数
 * @return: 元素交换的次数
 */
int selection_sort(int A[], int num)
{   
    int i, j, minj, count = 0; 

    for (i = 0; i < num - 1; ++i) { /* 同样最后一次不需要遍历, 因为每次会排序好前面的元素 */
        minj = i;
        for (j = i; j < num; ++j) {
            if (A[j] < A[minj]) 
                minj = j;   /* 保存此次循环的最小值 */
        }
        /* 交换 */
        if (i != minj) {
            swap(A, num, i, minj);
            ++count;
        }
    }
    return count;
}


int main(int argc, char *argv[])
{
    int n = 0, i, count = 0;
    int A[MAX];

    scanf("%d", &n);
    
    for (i = 0; i < n; ++i) 
        scanf("%d", &A[i]);
    
    count = selection_sort(A, n);
    trace(A, n);
    printf("%d\n", count);

    return 0;
}

