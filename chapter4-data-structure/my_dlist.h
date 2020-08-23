/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: my_dlist.h
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: 双向循环链表, head作为不作为一个节点
时间	   	: 2020-08-23 09:06
***************************************************************/
#ifndef __MY_DLIST_H__
#define __MY_DLIST_H__

#include <stdlib.h>

struct Node 
{
    int key;
    struct Node *prev;
    struct Node *next;
};

/**
 * initialize - 初始化双向循环列表
 * @head:	链表头
 * @return: 无
 */
static inline void initialize(struct Node *head)
{   
    head->next = head->prev = head;
}


/**
 * is_empty - 判断链表是否为空
 * @head:	链表头
 * @return: 空返回1, 非空返回0
 */
static inline int is_empty(struct Node *head)
{   
    return head->next == head;
}

/**
 * insert - 在表头添加含有键值x的节点
 * @head:	链表头
 * @x:      待插入键值
 * @return: 成功返回0, 失败返回-1
 */
static inline int insert(struct Node *head, int x)
{
    int ret = 0;
    struct Node *node = calloc(1, sizeof(struct Node)); 

    if (node) {
        node->key = x;

        if (is_empty(head)) {   
            node->next = node->prev = head;
            head->prev = head->next = node;
        } else {
            node->next = head->next;
            node->prev = head;
            node->next->prev = node;
            head->next = node;
        }    
    } else
        ret = -1;
    
    return ret;
}


/**
 * delete_node - 删除p指向的节点
 * @p:      待删除节点	
 * @return: 成功返回0, 失败返回-1
 */
static inline void delete_node(struct Node *p)
{
    p->prev->next = p->next;
    p->next->prev = p->prev;
    free(p);
}

/**
 * delete - 删除第一个含有键值x的节点
 * @head:	链表头
 * @x:      待删除的键
 * @return: 成功返回0, 失败返回-1
 */
static inline int delete(struct Node *head, int x)
{
    int ret = 0;
    struct Node *p = head->next;

    if (is_empty(head)) {
        ret = -1;
        return ret;
    }

    while (p != head && p->key != x) 
        p = p->next;
    
    if (p != head)
        delete_node(p);

    return ret;
}


/**
 * delete_frist - 删除链表的表头节点
 * @head:	链表头
 * @return: 成功返回0, 失败返回-1
 */
static inline int delete_frist(struct Node *head)
{
    int ret = 0;
    struct Node *p = head;
    if (!is_empty(head)) {    
        head = p->next;
        delete_node(p);
    } else 
        ret = -1;
    return ret;
}

/**
 * delete_last - 删除链表的表尾节点
 * @head:	链表头
 * @return: 成功返回0, 失败返回-1
 */
static inline int delete_last(struct Node *head)
{
    int ret = 0;
    if (!is_empty(head))     
        delete_node(head->prev);
    else 
        ret = -1;
    return ret;
}

/**
 * free_list - 释放全部链表节点
 * @head:	链表头
 * @return: 成功返回0, 失败返回-1
 */
static inline void free_list(struct Node *head)
{
    struct Node *p = head->next, *temp;

    while (p != head) {
        temp = p;
        p = p->next;
        delete_node(temp);
    }
}
#endif // !__MY_DLIST_H__