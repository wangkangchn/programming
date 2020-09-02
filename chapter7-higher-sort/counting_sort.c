/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: counting_sort.c
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: 计数排序(桶排序或箱排序)
        Note：
            1. 排序结束后的数组B, 要从1开始输出, 因为 C 中保存的是元素的累计计数, 
        当 C[i] == 0 也就意味着 i 从来没有出现过, 而 A[i] 取得都是存在的元素, 因此在 
        B[C[A[i]]] = A[i]; 中 B 永远不会取到 B[0], 所以 B 的第一个元素总是 0.
            2. 最后一步从后往前遍历A为稳定, 若从前往后相同元素需要逆序放置在B中.
            3. 默认A[i] >= 0
            4. 能够在 O(n + k) 内完成处理
时间	   	: 2020-09-02 09:49
***************************************************************/
#include <stdio.h>
#include <string.h>
#include "../tools/tools.h"
#include "../tools/log.h"

/**
 * counting_sort - 计数排序(桶排序或箱排序)
 * @A:      待排序数组
 * @B:      存放排序完成的数组
 * @count:  A中元素数目
 * @val_max: A中元素的最大值
 * @return: 无
 */
void counting_sort(int *A, int *B, size_t count, int val_max)
{   
    /* 1. 初始化数组C为0 */
    int C[val_max + 1];
    memset(C, 0, sizeof(int) * (val_max + 1));

    /* 2. 统计A中个元素出现的次数 */
    int i;
    for (i = 0; i < count; ++i) 
        ++C[A[i]];

    /* 3. 累加C */
    for (i = 1; i <= val_max; ++i) 
        C[i] += C[i - 1]; 
    printf("C: ");
    trace(C, val_max + 1);
    /* 4. 从后向前排序 */
    for (i = count - 1; i >= 0; --i) {
        B[C[A[i]]] = A[i];
        --C[A[i]];
    }
}

const int MAX = 100;
int main(int argc, char *argv[])
{
    int n = 0, i;
    size_t count = 0;
    int A[] = {8,5,9,2,6,3,7,1,10,4};
    int B[MAX];
    memset(B, 0, sizeof(int) * MAX);

    // scanf("%d", &n);

    // for (i = 0; i < n; ++i) 
    //     scanf("%d", &A[i]);
    printf("A: ");
    count = ARRAY_SIZE(A);
    trace(A, count);
    
    counting_sort(A, B, count, 10);
    printf("B: ");
    trace((B ), count+ 2);
    return 0;
}