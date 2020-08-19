/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: insertion_sort.cpp
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: 插入排序
时间	   	: 2020-08-19 10:43
***************************************************************/
/* Note:
    1. 排序的次数严重受到数据的顺序的影响, 顺序最快, 逆序最慢
    2. O(N^2)
 */
#include "stdio.h"

static const int MAX = 100;

/**
 * function - 按顺序输出数组元素
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
 * function - 插入排序
 * @A:      待排序数组	
 * @num:    数组元素个数
 * @return: 无
 */
void insert_sort(int *A, int num)
{   
    int v;
    int j, i, k, m; 

    for (i = 1; i < num; ++i) {
        v = A[i];   /* 待排序位置的后一个元素 */
        for (j = 0; j <= i - 1; ++j) {
            if (v < A[j]) { 
                /* 从当前j开始向后移动 */
                for (k = i; k > j ; --k) 
                    A[k] = A[k - 1]; 
                A[j] = v;   /* 交换 */
                break;
            }
        }
        
        trace(A, num);
    }
}

int main(int argc, char *argv[])
{
    int n = 0, i;
    int A[MAX];

    scanf("%d", &n);
    
    for (i = 0; i < n; ++i) 
        scanf("%d", &A[i]);
    

    trace(A, n);
    insert_sort(A, n);

    return 0;
}
