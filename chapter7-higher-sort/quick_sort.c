/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: quick_sort.c
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: 快速排序
            1. 快速排序就是在分割的基础上, 对左右部分递归进行分割.
        因为在进行了一次分割后, 枢纽左侧的值均小于等于枢纽, 在这些小于的中继续进行分割
        会使它们进一步有序.
            2. 快速排序是一种不稳定的排序算法
时间	   	: 2020-09-01 20:47
***************************************************************/
#include <stdio.h>
#include "../tools/tools.h"
#include "../tools/log.h"

typedef struct card {
    char suit;
    int value;
} card;
    
/**
 * merge - 将已排序好的两部分归并到一起
 * @A:      待排序数组
 * @left:   左边界(闭)
 * @middle: 中间
 * @right:  右边界(开)   	
 * @return: 比较运算的次数
 */
int merge(card *A, int left, int middle, int right)
{
    size_t ret = 0;
    int count = right - left;     /* 临时保存两边合并结果 */
    card temp[count];
    size_t i = 0, j = left, k = middle;     /* i 遍历temp, j 遍历前半部分, k遍历后半部分  */
    for (; i < count; ++i) 
        /* 当有一部分遍历完成后, 直接将另一组拷贝到数组中 */
        if (j == middle) 
            temp[i] = A[k++];
        else if (k == right) 
            temp[i] = A[j++];
        else {
            if (A[j].value > A[k].value) temp[i] = A[k++];
            else temp[i] = A[j++];
            ++ret;
        }

    /* 将合并后的结果拷贝到原数组 */
    for (i = 0, j = left; i < count; ++i, ++j) 
        A[j] = temp[i];

    return ret;
}

/**
 * merge_sort - 归并排序[lest, riht)
 * @A:      待排序数组
 * @left:   左边界(闭)
 * @right:  右边界(开)   	
 * @return: 比较运算的次数
 */
int merge_sort(card *A, int left, int right)
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

/**
 * partition - 分割數組, 使數組数组中下标小于q的元素均小于等于A[q], 下标大于q的元素均大于A[q]
 * @A:      待分割的数组
 * @left:   左边界(闭)	
 * @right:  右边界(开)
 * @return: q的下标
 */
int partition(card *A, int left, int right)
{      
    card x = A[right - 1];   /* 以最后一个元素为基准进行分割 */
    size_t i = left - 1;    /* i 指示前面最近一次小于等于x的位置 */
    size_t j = left;
    /* 不对最后一个元素进行判断 */
    for (; j < right - 1; ++j) { 
        /* 小于基准元素, 就将其置换到前面, ++i指定了前方交换的位置 */
        if (A[j].value <= x.value) {
            ++i;
            swap(A + i, A + j);   
        }
    }
    ++i;
    swap(A + i, A + j);   
    return i;
}

/**
 * quick_sort - 快速排序
 * @A:      待分割的数组
 * @left:   左边界(闭)	
 * @right:  右边界(开)
 * @return: 无
 */
void quick_sort(card *A, int left, int right)
{
    /* 结束条件 */
    if (left < right) {
        /* 分割一次 */
        int p = partition(A, left, right);

        /* 对左右部分分别进行排序 */
        quick_sort(A, left, p);
        quick_sort(A, p + 1, right);
    }
}

const int MAX = 100;

/* 
6
D 3
H 2
D 1
 S 3
 D 2
C 1 */
int main(int argc, char *argv[])
{
    // SET_DEFAULT_LEVEL(CONSOLE_LOGLEVEL_INFO);
    int n = 0, i;
    card A[MAX];
    card B[MAX];

    scanf("%d", &n);

    for (i = 0; i < n; ++i) {
        scanf("%s %d", &A[i].suit, &A[i].value);
        B[i] = A[i];
    }
        

    quick_sort(A, 0, n);
    merge_sort(B, 0, n);
    
    /* 验证稳定性 */
    int stable = 1;
    for (i = 0; i < n; ++i)
        if (B[i].suit == A[i].suit) 
            continue;
        else {
            stable = 0;
            break;
        }

    printf("%s\n", stable ? "Stable" : "Not stable");
    for (i = 0; i < n; ++i) 
        printf("%c %d\n", A[i].suit, A[i].value);         


    return 0;
}