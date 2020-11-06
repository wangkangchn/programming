/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: longest_increasing_subsequence.c
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: 最长递增子序列
时间	   	: 2020-11-06 09:03
***************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../tools/tools.h"
#include "../tools/log.h"


int compare(const void *arg1, const void *arg2)
{
    int __arg1 = *(int *)arg1;
    int __arg2 = *(int *)arg2;

    if (__arg1 == __arg2)   return 0;
    else if (__arg1 < __arg2)           return -1;
    else                                return 1;
}

/**
 * longest_increasing_subsequence - 求数列的最长递增子序列, 并不要求子序列元素连续
 * @A:      待计算序列	
 * @n_A:    序列长度	
 * @return: 最长自序列个数
 */
int longest_increasing_subsequence(int *A, size_t n_A)
{
    int i = 0, tail = 0;
    int *T = calloc_buf(n_A, int);
    T[0] = 1 << 30;

    for (i = 0; i < n_A; ++i) {
        if (T[tail] <= A[i]) {
            T[++tail] = A[i];
        } else {
            if (T[tail - 1] <= A[i]) {
                T[tail] = A[i];
            }
        }
    }

    trace(T, tail+1);
    free_buf(T);
    return tail + 1;
}

/**
 * LIS - 动态规划求 LIS
 * @A:      待计算序列	
 * @n_A:    序列长度	
 * @return: 最长自序列个数
 */
int LIS(int *A, size_t n_A)
{   
    int *_A =  calloc_buf(n_A + 1, int);     /* 保存选择 A[i] 时 LIS 的长度 */
    int *L =  calloc_buf(n_A + 1, int);     /* 保存选择 A[i] 时 LIS 的长度 */
    int *P =  calloc_buf(n_A + 1, int);     /* 保存选择 A[i] 时 LIS 前一个元素的下标 */
    int l = 0;
    int i = 0, j = 0;
    int k = 0;

    memcpy(_A + 1, A, sizeof(int) * n_A);
    qsort(_A + 1, n_A, sizeof(int), compare);
    _A[0] = _A[1]-1;
    memcpy(_A + 1, A, sizeof(int) * n_A);

    for (i = 1; i <= n_A; ++i) {
        k = 0;  /* 记录 i 前半部分的最长 LIS 对应的下标 */
        for (j = 0; j <= i - 1; ++j) {   /* i 的前半部分 */
            if (A[i] >= A[j] && L[j] >= L[k]) { /* i 比 前面某一个元素大并且该元素对应的 LIS 的长度比现在已遍历前半部分 LIS 的最大长度还要
                                            长, 就将 i 插入该元素 LIS 的后面 */
                k = j;
            }            
        }
        L[i] = L[k] + 1;
        P[i] = k;     
    }

    trace(L, n_A + 1);
    qsort(L, n_A + 1, sizeof(int), compare);
    l = L[n_A];

    free_buf(L);
    free_buf(P);
    return l;
}


/**
 * binary_search - 二分查找
 * @L:      待查找数列
 * @num:	S的大小
 * @key:    待查找的键
 * @return: 成功返回0, 失败返回-1
 */
int binary_search(int *L, int num, int key)
{   
    int middle = 0;
    int lower = 0, upper = num; /* 左闭右开 */
    int last = 0;   /* 上一次查询的结果, 0代表小于, 1代表大于
                要查找的是 */
    while (lower <= upper) {
        middle = (upper - lower) / 2;
        // printf("middle: %d\n", middle);
        if (L[middle] == key)
            return middle; 
        else if (L[middle] < key) { 
            if (L[middle + 1] >= key)
                return middle + 1;
            lower = middle + 1;
        } else {    /* L中值大于 key  */
            if (L[middle - 1] < key)
                return middle;
            upper = middle;
        }
    }
}

/**
 * LIS - 动态规划 + 二分搜索求 LIS
 * @A:      待计算序列	
 * @n_A:    序列长度	
 * @return: 最长自序列个数
 */
int LIS_binary_search(int *A, size_t n_A)
{   
    int *L = calloc_buf(n_A, int);  /* L[i] i + 1 是 LIS 长度, 值为 LIS 中末尾最小的一个(因为可能存在多个相同长度的 LSI)  */
    int l = 0;
    int i = 0, j = 0;

    L[l] = A[0];
    for (i = 1; i < n_A; ++i) {
        if (A[i] > L[l]) {
            L[++l] = A[i];
        } else {
            /* 当前元素小于当前 LSI 末尾最小元素时, 说明其所在的位置应该在之前的序列, 就向前搜索找到第一个大于
            等于的元素, 如果小于该元素就说明他比此 LSI 末尾元素还要小, 就必须再向前 */
            j = binary_search(L, l+1, A[i]);
            printf("%d\n", j);
            L[j] = A[i];
        }
    }
    free_buf(L);
    return l+1;
}

/* 测试:
8

3
4
5

1
2
3
4
5


 */
int main(int argc, char *argv[])
{
    // SET_DEFAULT_LEVEL(CONSOLE_LOGLEVEL_INFO);
    int n, i;

    scanf("%d", &n);
    int *A = calloc_buf(n, int);

    for (i = 0; i < n; ++i) 
        scanf("%d", &A[i]);

    double start = START();
    printf("%d\n", longest_increasing_subsequence(A, n));

    printf("LIS\n");
    printf("%d\n", LIS(A, n));

    printf("LIS_binary_search\n");
    printf("%d\n", LIS_binary_search(A, n));
    FINISH(start);
    free_buf(A);
    return 0;
}