/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: my_queue.h
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: 环形队列 
时间	   	: 2020-08-22 21:23
***************************************************************/
// static inline void func(void) {printf("123\n");}   /* 头文件中的static是可以使用的, 
//                                             对对对对, 因为#include是将所有内容展开,
//                                             此时static就相当于定义在了.c中 */
#ifndef __MY_QUEUE_H__
#define __MY_QUEUE_H__

struct Node
{
    char name[5];
    int time;
};

int head;
int tail;
int MAX;
struct Node *Q;

/**
 * initialize - 初始化队列顶指针, 分配队列空间
 * @max:	队列最大长度
 * @return: 成功返回0, 失败返回-1
 */
static inline int initialize(int max)
{
    head = tail = 0;
    MAX = max;
    Q = calloc(1, MAX * sizeof(struct Node));
    if (Q)
        return 0;
    return -1;
}

/**
 * is_empty - 判断队列是否为空
 * @return: 空返回1, 非空返回0
 */
static inline int is_empty(void) { return head == tail; }

/**
 * is_full - 判断队列是否为满
 * @return: 满返回1, 非满返回0
 */
static inline int is_full(void) { return (tail + 1) % MAX == head; }

/**
 * enqueue - 向队列顶添加元素
 * @val:	待插入值
 * @return: 成功返回0, 失败返回-1
 */
static inline int enqueue(struct Node val)
{
    int ret = 0;
    if (!is_full()) {
        Q[tail] = val;
        tail = ++tail % MAX;
    } else 
        ret = 0;
    return ret;
}

/**
 * dequeue - 弹出队列顶元素
 * @val:	待插入值
 * @return: 成功返回队列顶元素, 失败返回0结构体
 */
static inline struct Node dequeue(void)
{
    struct Node ret = {0, 0};
    if (!is_empty()) {
        ret = Q[head];
        head = ++head % MAX;
    } 
    return ret;
}

#endif // !__MY_QUEUE_H__