/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: the_num_of_inversions.c
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: 逆序数(使用归并排序计算逆序数)
时间	   	: 2020-09-02 19:30
***************************************************************/
#include <stdio.h>
#include "../tools/tools.h"
#include "../tools/log.h"

/**
 * merge - 将已排序好的两部分归并到一起
 * @A:      待排序数组
 * @left:   左边界(闭)
 * @middle: 中间
 * @right:  右边界(开)   	
 * @return: 该部分的逆序数
 */
int merge(int *A, int left, int middle, int right)
{
    size_t ret = 0;             
    size_t i = 0, j = left, k = middle;     /* i 遍历temp, j 遍历前半部分, k遍历后半部分  */
    size_t count = right - left;               /* 临时保存两边合并结果 */
    int temp[count];

    for (; i < count; ++i) 
        /* 当有一部分遍历完成后, 直接将另一组拷贝到数组中 */
        if (j == middle) 
            temp[i] = A[k++];
        else if (k == right) 
            temp[i] = A[j++];
        else {
            if (A[j] > A[k]) {
                temp[i] = A[k++];
                /* 在归并排序的每个部分中, 当前半部分的值>后半部分的值时, 这说明就存在一个逆序
                因为在两个部分中先放入temp的是最小的, 
                1. 当前半部分某一个元素 > 后半部分一个元素时(一个逆序),
                将后半部分那个元素放入temp, 再次从后半部分元素逐一比较, 这样不会漏掉任何一个逆序
                2. 当后半部分全部排完后, 前半部分还存在元素, 剩下元素的逆序与最后一个移动的逆序一致  */
                ret += (middle - j);               
            } else 
                temp[i] = A[j++];
            
        }


    /* 将合并后的结果拷贝到原数组 */
    for (i = 0, j = left; i < count; ++i, ++j) 
        A[j] = temp[i];

    pr_debug("left: %d, right: %d, ret = %zd\n", left, right, ret);
    return ret;
}

/**
 * merge_sort - 归并排序[lest, riht)
 * @A:      待排序数组
 * @left:   左边界(闭)
 * @right:  右边界(开)   	
 * @return: 比较运算的次数
 */
int merge_sort(int *A, int left, int right)
{   
    size_t ret = 0;
    /* 递归结束条件 */
    if (left + 1 == right) return 0;

    int middle = (left + right) / 2;

    /* 1. devide */
    ret += merge_sort(A, left, middle);
    ret += merge_sort(A, middle, right);

    /* 2. slove and conquer */
    ret += merge(A, left, middle, right);
    return ret;
}

/* 测试:
5
3 5 2 1 4
*/
const int MAX = 100;
int main(int argc, char *argv[])
{   
    SET_DEFAULT_LEVEL(CONSOLE_LOGLEVEL_INFO);
    int n = 0, i;
    size_t count = 0;
    int A[MAX];
    
    scanf("%d", &n);

    for (i = 0; i < n; ++i) 
        scanf("%d", &A[i]);

    double start = START();
    count = merge_sort(A, 0, n);
    // trace(A, n);
    printf("%zd\n", count);
    FINISH(start);
    return 0;
}