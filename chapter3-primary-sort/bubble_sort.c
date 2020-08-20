/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: bubble_sort.cpp
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: 冒泡排序
时间	   	: 2020-08-19 10:43
***************************************************************/
/* Note:
    1. 冒泡排序中的交换次数又称为反序数或逆序数, 用于体现数列的错乱程度
    2. 稳定排序
    3. O(N^2)
    4. 在不使用is_disorder的时候, 不管数据是什么顺序, 该比较多少次就比较多少次, 不会减少    
 */
#include <stdio.h>
#include "tools.h"

static const int MAX = 100;

/**
 * bubble_sort - 冒泡排序 升序
 * @A:      待排序数组	
 * @num:    数组元素个数
 * @return: 元素交换的次数
 */
int bubble_sort(int *A, int num)
{   
    int count = 0;
    int j, i, temp; 
    int is_disorder = 1;    /* 是否存在属性相反的元素, 即标记排序数列是否是无序的 */

    for (i = 0; i < num - 1; ++i) {
        if (is_disorder) {  /* 乱序执行, 顺序退出 */
            is_disorder = 0;
            for (j = 0; j < num - i; ++j) {
                /* 交换 */
                if (A[j] > A[j + 1]) {
                    temp = A[j];
                    A[j] = A[j + 1];
                    A[j + 1] = temp;
                    is_disorder = 1;
                    ++count;
                }
            }   
        } else
            break;
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
    

    trace(A, n);
    count = bubble_sort(A, n);
    trace(A, n);
    printf("%d\n", count);

    return 0;
}
