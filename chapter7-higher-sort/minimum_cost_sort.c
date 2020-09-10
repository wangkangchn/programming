/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: minimum_cost_sort.c
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: 最小成本排序
时间	   	: 2020-09-06 09:58
***************************************************************/
#include <stdio.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>
#include "../tools/tools.h"
#include "../tools/log.h"
#include "../tools/queue.h"
#include "../tools/stack.h"
#include "../tools/list.h"

typedef struct point {
    int x, y;
} point;


DEFINE_STACK_ELEMENT_TYPE(point, stack);
DEFINE_QUEUE_ELEMENT_TYPE(int, queue);

/* 使用链表保存圆 */
struct circle_list {
    struct list_head list;
    queue *Q;
};

/* x 是否在 pt 内 */
#define in(val, __pt)   ({ ( (__pt).x == (val) || (__pt).y  == (val) ) ? 1 : 0; })

/**
 * check_Q_elem - 检查待插入值是否已在队列中存在
 * @Q:	    队列
 * @key:    待插入键
 * @return: 存在返回 true, 不存在返回 false
 */
bool check_Q_elem(queue *Q, int key)
{   
    bool exist = false;
    int n = qsize(Q);
    for (int i = 0; i < n; ++i) {
        if (key == Q->data[i]) {
            exist = true;
            break;
        }
    }
    return exist;
}

/**
 * circle - 画单个圆
 * @param:	
 * @return: 成功返回0, 失败返回-1
 */
void circle(stack *S, stack *Stemp, struct list_head *header, int num)
{   
    /* 一个圆使用一个 list node 保存 */
    size_t i = 0;
    struct circle_list *node = calloc_buf(1, struct circle_list);
    node->Q = calloc_buf(1, queue);
    assert(qinit(node->Q, num));
    
    pr_debug("Q创建成功\n");

    point pt = spop(S);
    pr_debug("当前欲存入队列的数对: (%d, %d)\n", pt.x, pt.y);
    point temp;

    qpush(node->Q, pt.x); qpush(node->Q, pt.y);

    while(!sis_empty(S)) {
        temp = spop(S);
        pr_debug("当前欲存入队列的数对: (%d, %d)\n", temp.x, temp.y);
        if (in(temp.x, pt)) {
            pr_debug("待存入: %d\n", temp.y);
            if (!check_Q_elem(node->Q, temp.y)) {
                pr_debug("存入: %d\n", temp.y);
                qpush(node->Q, temp.y);
                pt = temp;
            } else {
                pr_debug("队列中已存在 %d\n" , pt.y);
            }
        } else if (in(temp.y, pt)) {
            if (!check_Q_elem(node->Q, temp.x)) {
                pr_debug("存入: %d\n", temp.x);
                qpush(node->Q, temp.x);
                pt = temp;
            }
        } else 
            spush(Stemp, temp);    /* temp不是当前圆中的节点, 则保存到另一个栈 */
    }

    pr_debug("队列长度: %d\n", qsize(node->Q));
    for (size_t i = 0; i < qsize(node->Q); i++) {
        pr_debug("%d\n", node->Q->data[i]);
    }
    
    list_add(&(node->list), header);
}
        
/**
 * draw_circle - 拆解元素
 * @A:      待排序数组	
 * @num:    数组元素个数
 * @header: 保存所有圆的链表
 * @return: 无
 */
void draw_circle(int A[], int num, struct list_head *header)
{   
    stack *S1 = calloc_buf(1, stack);
    stack *S2 = calloc_buf(1, stack);
    assert(sinit(S1, num * 0.5 + 1));
    assert(sinit(S2, num * 0.5 + 1));

    int i, j, minj, ret = 0; 
    point pt, temp;
    struct circle_list *node;

    /* 保存所有交换对 */
    for (i = 0; i < num - 1; ++i) { 
        minj = i;
        for (j = i; j < num; ++j) {
            if (A[j] < A[minj]) 
                minj = j;   
        }
        /* 保存交换的两个数 */
        if (i != minj) {
            pt.x = A[i];
            pt.y = A[minj];
            pr_debug("保存数对: (%d, %d)\n", pt.x, pt.y);
            spush(S1, pt);
            swap(A + i, A + minj);
        }
    }

    /* 根据选择的交换对画圆 */
    while (!sis_empty(S1) || !sis_empty(S2)) {
        pr_debug("画圆\n");
        if (!sis_empty(S1))
            circle(S1, S2, header, num);
        else if (!sis_empty(S2))
            circle(S2, S1, header, num);
    }
}

/**
 * compute_cost - 计算最小代价
 * @header: 保存所有圆的链表
 * @return: 最小代价
 */
int compute_cost(struct list_head *header, int global_min_w)
{   
    
    struct circle_list *node;
    int cost = 0;
    int no_borrow, borrow;      /* 向外面借元素与不借元素的代价 */
    int min_w = INT_MAX, w;                  /* 圆中最小的代价 */
    int n;                      /* 保存队列的元素数 */
    list_for_each_entry(node, header, list) {
        pr_debug("借: %d\n", global_min_w);
        n = qsize(node->Q);

        for (size_t i = 0; i < qsize(node->Q); i++) {
            pr_debug("队列元素: %d\n", node->Q->data[i]);
        } 

        min_w = INT_MAX;
        borrow = no_borrow = 0;
        /* 计算 sum(wi) */
        while (!qis_empty(node->Q)) {
            w = qpop(node->Q);
            no_borrow += w;
            if (w < min_w) 
                min_w = w;
        }
        /* 计算外借的代价 */
        borrow = no_borrow + min_w + (n + 1) * global_min_w;
        pr_debug("borrow: %d\n", borrow);
        /* 计算不外借的代价 */
        no_borrow += (min_w * (n - 2));
        pr_debug("no_borrow: %d\n", no_borrow);

        cost += (no_borrow <= borrow ? no_borrow : borrow);
    }
    return cost;
}

/**
 * clear_list - 删除链表
 * @header:	待删除链表
 * @return: 无
 */
void clear_list(struct list_head *header)
{
    struct circle_list *node;
    struct list_head *pos, *q;
    list_for_each_safe(pos, q, header) {
        node = list_entry(pos, struct circle_list, list);
        if (node->Q)
            qclear(node->Q);
        list_del(pos);
        free_buf(node);
    }
}

/* 测试：
5
1 5 3 4 2 

7
4 3 2 7 1 6 5

6
2 1 8 10 7 9
*/
const int MAX = 100;
int main(int argc, char *argv[])
{
    SET_DEFAULT_LEVEL(CONSOLE_LOGLEVEL_INFO);
    int n = 0, i;
    int A[MAX];
    struct list_head *header = calloc_buf(1, struct list_head);
    INIT_LIST_HEAD(header);

    scanf("%d", &n);

    for (i = 0; i < n; ++i) 
        scanf("%d", &A[i]);

    double start = START();
    draw_circle (A, n, header);

    printf("\n最小代价: %d\n", compute_cost(header, A[0]));

    clear_list(header);
    free_buf(header);
    FINISH(start);
    return 0;
}