/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: priority_queue.c
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: 优先级队列
        Note:
            1. 插入删除操作时间复杂度均为 O(logn)
时间	   	: 2020-09-09 13:52
***************************************************************/
#include <stdio.h>
#include <string.h>
#include "../tools/tools.h"
#include "../tools/log.h"

typedef int heap_element;

typedef struct heap {
    size_t count;
    heap_element *heap;
} heap;

#define parnet(id)      ({ (id) >> 1; })
#define left(id)        ({ (id) << 1; })
#define right(id)       ({ ( (id) << 1 ) + 1; })

const heap_element INFIY = 1 << (sizeof(heap_element) * 8 - 2);     /* 最大值 */

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
 * insert - 向二叉堆中插入键值 
 *      1. 先将元素插入最右 heap[++count]
 *      2. 而后从叶向上遍历找到该键值适合的位置
 * @heap:   二叉堆
 * @count:  新键待插入的位置      	
 * @return: 无
 */
void insert(heap *H, heap_element key)
{   
    if (key < -INFIY)   
        return;
    H->heap[++H->count] = key;
    for (size_t i = H->count; (i > 1) && (H->heap[parnet(i)] < H->heap[i]); i = parnet(i))
        swap(H->heap + i, H->heap + parnet(i));
}

/**
 * delete - 获取优先队列的最大值而后删除
 * @H:	    优先队列
 * @return: 优先队列中的最大值
 */
heap_element delete(heap *H)
{   
    assert(H->count);

    heap_element max = H->heap[1];
    H->heap[1] = H->heap[H->count--];
    max_henpify(H->heap, H->count, 1);
    return max;
}

/* 测试:
insert 8
insert 2
extract 
insert 10
extract 
insert 11
extract 
extract 
end

*/
const int MAX = 100;
const int root = 1;
int main(int argc, char *argv[])
{
    // SET_DEFAULT_LEVEL(CONSOLE_LOGLEVEL_INFO);
    int i;
    size_t count = 0;
    char cmd[20];

    heap H = {
        .count = 0,
        .heap = calloc_buf(MAX, heap_element),
    };

    heap_element key;

    double start = START();
    for (; ;) {
        scanf("%s", cmd);
        /* 插入树根, 而后向下调整 */
        if (strcmp(cmd, "insert") == 0) {
            scanf("%d", &key);
            insert(&H, key);


        /* 删除, 将最后一个节点键值上提到树根, 而后向下调整 */
        } else if (strcmp(cmd, "extract") == 0) {
             printf("%d\n", delete(&H));

        } else {
            free_buf(H.heap);
            break;
        }
    }
    FINISH(start);
    return 0;
}