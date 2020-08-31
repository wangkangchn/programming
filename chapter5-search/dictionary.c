/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: dictionary.c
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: 散列法 (拉链法解决冲突)
时间	   	: 2020-08-29 14:36
***************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../tools/list.h"
#include "../tools/log.h"

/* 链表节点 */
struct list_node
{   
    struct list_head list;      /* 链表头 */
    char *key;
};

/**
 * list_node - 创建结点, 并保存值
 * @msg:	    待保存的值
 * @return: 新节点
 */
struct list_node *create_node(char *msg)
{
    struct list_node * node = calloc(1, sizeof(struct list_node));
    node->key = calloc(20, sizeof(char));
    strncpy(node->key, msg, strlen(msg));
    return node;
}

/**
 * hashed_value - 散列函数, 计算散列值, 将字符串各字符的ascii值相加之后与散列表的大小取余
 *                  sum(msg[i]) % hash_size
 * @msg:	带计算散列值的键
 * @return: 计算的散列值
 */
static inline int hashed_value(char *msg, int size)
{
    int ret = 0;
    for (size_t i = 0; i < strlen(msg); ++i) 
        ret += msg[i];
    
    return ret & (size - 1);
}

/**
 * search - 在散列表中搜索指定的值
 * @dictionary:	    散列表
 * @size:           散列表大小
 * @msg:            待搜索的值
 * @return:         搜索到返回1, 未搜索到返回0
 */
int search(struct list_head *dictionary, int size, char *msg)
{
    int ret = 0;
    struct list_node *node;

    struct list_head *head = dictionary + hashed_value(msg, size);

    if (!list_empty(head)) {
        list_for_each_entry(node, head, list) {           /* 这个就是不断变量链表元素, node保存每一个节点值 */
            if (strcmp(node->key, msg) != 0)
                continue;
            else {
                ret = 1;
                break;
            }
        }
    }
    return ret;
}

/**
 * insert - 向散列表中插入值
 * @dictionary:	    散列表
 * @size:           散列表大小
 * @msg:            待搜索的值
 * @return:         无
 */
static inline void insert(struct list_head *dictionary, int size, char *msg)
{
    list_add(&(create_node(msg)->list), dictionary + hashed_value(msg, size));
}


/**
 * clearup_dict - 清空散列表分配的空间
 * @dictionary:	散列表
 * @size:       散列表大小
 * @return:     无
 */
void clearup_dict(struct list_head *dictionary, int size) 
{   
    struct list_node *node;
    struct list_head *pos, *q;

    if (dictionary) {
        for (size_t i = 0; i < size; ++i) {
            list_for_each_safe(pos, q, &dictionary[i]){
                node = list_entry(pos, struct list_node, list);
                list_del(pos);          /* 处理链表 */
                free(node);             /* 删除数据 */ 
            }      
        }
        free(dictionary);
    }

}

/**
 * init_dict - 初始化散列表各项链表头
 * @dictionary:	散列表
 * @size:       散列表大小
 * @return:     无
 */
void init_dict(struct list_head *dictionary, int size)
{
    for (size_t i = 0; i < size; ++i) 
        INIT_LIST_HEAD(dictionary + i);   
}

const int dictionary_size = 8;  /* 散列表大小, 必须是2的幂指数倍 */    

int main(int argc, char *argv[])
{
    int n = 0, i;
    char cmd[10], msg[20];

    /* 申请头指针(散列表) */
    struct list_head *dictionary = calloc(dictionary_size, sizeof(struct list_head));
    init_dict(dictionary, dictionary_size);

    scanf("%d", &n);

    for (i = 0; i < n; ++i) {
        scanf("%s %s", cmd, msg);

        switch (cmd[0])
        {
        /* 插入 */
        case 'i':
            // printf("insert: 散列值为: %d\n", hashed_value(msg, dictionary_size));
            list_add(&(create_node(msg)->list), 
                        &(dictionary[hashed_value(msg, dictionary_size)]));
            break;
        
        /* 查找 */
        case 'f':
            // printf("find: 散列值为: %d\n", hashed_value(msg, dictionary_size));
            if(search(dictionary, dictionary_size, msg))
                printf("yes\n");
            else
                printf("no\n");
            break;

        default:
            break;
        }
    }
    clearup_dict(dictionary, dictionary_size);
    return 0;
}