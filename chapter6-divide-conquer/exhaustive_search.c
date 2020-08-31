/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: exhaustive_search.c
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: 穷举搜索
时间	   	: 2020-08-31 14:22
***************************************************************/
#include <stdio.h>
#include <stdbool.h>
#include "../tools/tools.h"

/**
 * slove - 计算第i个元素后面的元素是否可以得到m, 分两种情况计算, 
 * 使用 A[i] 和不使用 A[i], 只要二者有其一可以返回 true, 就认为该数列可以得到 m
 * @A:	    待搜索数组
 * @n:      A中元素数目
 * @i:      下标
 * @m:      欲求和
 * @return: 成功返回0, 失败返回-1
 */
bool slove(int *A, int *n, int i, int m)
{
    /* 数列能够得到 m, m == 0 说明用数列元素刚好可以将m减完 */
    if (m == 0) return true;
    /* m < 0 说明在这条分枝上已选择的元素和超过了 m, 因此后续也没有必要再运算, 
    提前退出减少递归分枝提高效率 */
    else if (m < 0) return false;

    /* 遍历完所有的数组元素了 */
    if (i >= *n) return false;

    /*         不使用 i + 1                    使用 i + 1         二者只要有一个满足就可以*/
    return slove(A, n, i + 1, m) || slove(A, n, i + 1, m - A[i]);
}

const int MAX = 100;
int main(int argc, char *argv[])
{
    int n = 0, i, q = 0;
    int A[MAX], Q[MAX];

    scanf("%d", &n);

    for (i = 0; i < n; ++i) 
        scanf("%d", &A[i]);

    scanf("%d", &q);

    for (i = 0; i < q; ++i) 
        scanf("%d", &Q[i]);

    for (i = 0; i < q; i++) 
        printf("%s\n", slove(A, &n, 0, Q[i]) ? "yes" : "no");
    
    return 0;
}