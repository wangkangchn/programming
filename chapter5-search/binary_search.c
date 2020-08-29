/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: binary_search.c
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: 二分查找
时间	   	: 2020-08-29 14:10
***************************************************************/
/* Note:
    1. 算法复杂度 O(logn), 每次搜索范围减半
    2. 当数据量少的时候, 可以先排序后使用二分查找 */
#include <stdio.h>

/**
 * binary_search - 二分查找
 * @S:      待查找数列
 * @num:	S的大小
 * @key:    待查找的键
 * @return: 成功返回0, 失败返回-1
 */
int binary_search(int *S, int num, int key)
{   
    /* 递归结束条件 */
    if (num != 0) {
        int middle = num / 2;

        if (S[middle] == key) 
            return 1;     
        /* 右侧递归搜索 */
        else if (S[middle] < key) 
            return binary_search(S + middle + 1, num - middle, key);
        /* 左侧递归搜索 */
        else 
            return binary_search(S, middle, key);      
    } else 
        return 0;
}

const int MAX = 100;
int main(int argc, char *argv[])
{
    int n = 0, q = 0, key, i = 0, count = 0;
    int S[MAX];

    scanf("%d", &n);

    for (i = 0; i < n; ++i) 
        scanf("%d", &S[i]);
    
    scanf("%d", &q);
    for (i = 0; i < q; ++i) {
        scanf("%d", &key);
        count += binary_search(S, n, key);
    }
    printf("%d\n", count);

    return 0;
}