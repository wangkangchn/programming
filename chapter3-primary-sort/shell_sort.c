/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: shell_sort.c
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: 希尔排序, 相距g的为一组, 对这一组进行插入排序, 不断缩小g至1
时间	   	: 2020-08-20 16:43
***************************************************************/
/* Note:
    1. 稳定排序
    2. 当g为1时, 为普通插入排序
    3. g = 3 * g + 1 算法复杂度基本维持在 O(N^1.25) 正序产出g, 逆序使用
        g必须是递减数列, 并且最后一个为1
        for (int g = 1; ;) {
            if (g > n) 
                break;
            else
                添加进G;
            g = 3 * g + 1
        }
    4. 为什么说如果遇到2的幂指数等g=1之前几乎不需要排序的数列,希尔排序法的效率会大打折扣? 不明白
*/
#include <stdio.h>
#include "tools.h"

static const int MAX = 100;

/**
 * insert_sort - 插入排序, 以g为间隔进行插入排序
 * @A:      待排序数组	
 * @n:      数组元素个数
 * @g:      分组间隔
 * @return: 返回交换次数
 */
int insert_sort(int *A, int n, int g)
{   
    int v;
    int j, i; 
    int cnt = 0;    /* 交换次数 */

    for (i = g; i < n; ++i) {
        v = A[i];   /* 待排序位置的后一个元素 */
        j = i - g;
        while (j >= 0 && A[j] > v) {    /* 将小的前移 */
            A[j + g] = A[j];  /* 元素后移 */
            j -= g;
            ++cnt;
        }

        A[j + g] = v;   /* 交换 */
    }
    return cnt;
}

/**
 * shell_sort - 希尔排序
 * @A:      待排序数组	
 * @n:      数组元素个数
 * @return: 无
 */
void shell_sort(int A[], int n)
{
    int cnt = 0;
    int m = 3;  /* 分组数 */
    int G[] = {n >> 1, n >> 2, 1};

    for (int i = 0; i < m; ++i) {
        cnt += insert_sort(A, n, G[i]);
    }
    
    printf("%d\n", m);
    trace(G, m);
    printf("%d\n", cnt);
    for (size_t i = 0; i < n; ++i) 
        printf("%d\n", A[i]);
}

int main(int argc, char *argv[])
{
    int n = 0, i, count = 0;
    int A[MAX];

    scanf("%d", &n);
    
    for (i = 0; i < n; ++i) 
        scanf("%d", &A[i]);
    
    shell_sort(A, n);
    return 0;
}

