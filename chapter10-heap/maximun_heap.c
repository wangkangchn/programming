/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: maximun_heap.c
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: 使用给定数组生成 最大堆
        Note:
            1. 时间复杂度 O(n) n为堆大小
时间	   	: 2020-09-09 09:45
***************************************************************/
#include <stdio.h>
#include "../tools/tools.h"
#include "../tools/log.h"

typedef int heap_element;

#define parnet(id)      ({ (id) >> 1; })
#define left(id)        ({ (id) << 1; })
#define right(id)       ({ ( (id) << 1 ) + 1; })

/**
 * max_henpify - 从根结点 i 向叶结点方向寻找 A[i] 值的恰当位置
 * @A:      堆
 * @n:      堆中元素个数
 * @i:      待调整的根结点	
 * @return: 无 
 */
void max_henpify(heap_element *A, size_t n, int i)
{
    int left = left(i);
    int right = right(i);
    int largest;        /* 根与子树中值较大的节点序号 */

    /* 因为 i 的子树已经为最大堆, 现在只要判断根 i 和其左右结点的关系就好, 为了满足最大堆, 需要找到
根, 左, 右中最大的一个, 将其提上到根. 
    1. 当 i 为最大值的时候, 不需要调整
    2. 当 左/右 子树为最大值的时候, 交换根与子树的值, 从交换的子树处向下重新调整
堆, 因为交换后不能保证子树仍满足最大堆的性质 */
    largest = i;
    if ( (left <= n) && (A[left] > A[i]) )
        largest = left;
    
    if ( (right <= n) && (A[right] > A[largest]) )
        largest = right;
    
    /* 子节点值大时, 交换根与子节点, 同时向下调整子树 */
    if (largest != i) {
        swap(A + i, A + largest);
        max_henpify(A, n, largest);
    }
}

/**
 * bulid_max_heapify - 将数组 A 构建成最大堆
 * @A:      待构建数组	
 * @n:      数组实际元素个数
 * @return: 无
 */
int bulid_max_heapify(heap_element *A, size_t n)
{
    /* 从最右根开始向上构建最大堆 */
    for (size_t i = n >> 1; i > 0; --i) 
        max_henpify(A, n, i);
}   

/* 测试:
10
4 1 3 2 16 9 10 14 8 7

 */
const int MAX = 100;
int main(int argc, char *argv[])
{
    // SET_DEFAULT_LEVEL(CONSOLE_LOGLEVEL_INFO);
    int n = 0, i;
    heap_element A[MAX];

    scanf("%d", &n);

    for (i = 1; i <= n; ++i) 
        scanf("%d", &A[i]);

    double start = START();
    bulid_max_heapify(A, n);
    for (i = 1; i <= n; ++i) { 
        if (i > 1) printf(" ");     
        printf("%d", A[i]);         
    }                               
    printf("\n");
    FINISH(start);
    return 0;
}