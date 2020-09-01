/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: merge_sort.c
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: 归并排序
            归并排序与二分查找类似, 只不过一个是进行排序一个是进行搜索, 
        归并排序是使用分治的思想是:
        1. 将整个一路2分割到底, 最后只有两个元素(devide)
        2. 比较相邻元素大小(slove)
        3. 从下向上对已排好的子序列进一步的排序(conquer), 这个向上整理应该是可以用任何一种排序方法吧
    Note:
        由此看来分治法总是先分割成最小问题, 而后解决, 接着向上返回整理结果

    小记:
        1. 一般来说n个数据大致会分为logn层, 每层执行merge的总复杂读为O(n), 所以总共的时间复杂度为O(nlogn)
        2. 是稳定的排序算法
        3. 在进行合并的过程中, 不应该使用普通的排序算法, 这样完全没有考虑部分已有序的性质, 会大大增加算法的
    复杂度, 采用的是将合并结果直接拷贝到临时数组, 再拷贝回去的方法
时间	   	: 2020-09-01 11:24
***************************************************************/
#include <stdio.h>
#include "../tools/tools.h"
#include "../tools.h"

/**
 * merge - 将已排序好的两部分归并到一起
 * @A:      待排序数组
 * @left:   左边界(闭)
 * @middle: 中间
 * @right:  右边界(开)   	
 * @return: 比较运算的次数
 */
int merge(int *A, int left, int middle, int right)
{
    size_t ret = 0;
    int count = right - left;     /* 临时保存两边合并结果 */
    int temp[count];
    size_t i = 0, j = left, k = middle;     /* i 遍历temp, j 遍历前半部分, k遍历后半部分  */
    for (; i < count; ++i) 
        /* 当有一部分遍历完成后, 直接将另一组拷贝到数组中 */
        if (j == middle) 
            temp[i] = A[k++];
        else if (k == right) 
            temp[i] = A[j++];
        else {
            if (A[j] > A[k]) temp[i] = A[k++];
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


const int MAX = 100;
int main(int argc, char *argv[])
{
    int n = 0, i;
    size_t count = 0;
    int A[] = {8,5,9,2,6,3,7,1,10,4};

    // scanf("%d", &n);

    // for (i = 0; i < n; ++i) 
    //     scanf("%d", &A[i]);

    count = merge_sort(A, 0, ARRAY_SIZE(A));
    trace(A, ARRAY_SIZE(A));
    printf("%d\n", count);
    return 0;
}