/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: dictionary.c
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: 散列法 
时间	   	: 2020-08-29 14:36
***************************************************************/
#include <stdio.h>
#include <stdlib.h>

#include "../tools/list.h"

/* 链表节点 */
struct list_node
{   
    struct list_head list;      /* 链表头 */
    char *key;
};

/**
 * list_node - 创建结点, 并保存值
 * @s:	    待保存的值
 * @return: 新节点
 */
struct list_node *create_node(char *s)
{
    struct list_node * node = calloc(1, sizeof(struct list_node));
    node->key = calloc(20, sizeof(char));
    return node;
}

/**
 * function - 
 * @param:	
 * @return: 成功返回0, 失败返回-1
 */
int search(char *msg)
{
    int ret = 0;
    for (j = 0; j < dictionary_size; ++j) {
    struct list_head *head = &dictionary[sum & (dictionary_size - 1)];
    if (!list_empty(head)) 
        list_for_each_entry(node, head, list)            /* 这个就是不断变量链表元素, node保存每一个节点值 */
        if (strcmp(node->key, msg) != 0)
            return 1;
    }
    return 0;
    return ret;
}

const int MAX = 100;
const int dictionary_size = 8;  /* 散列表大小 */    
int main(int argc, char *argv[])
{
    int n = 0, i, j, sum = 0;
    char cmd[10], msg[20];
    struct list_node *node;

    /* 申请头指针(散列表) */
    struct list_head *dictionary = calloc(dictionary_size, sizeof(struct list_head));
    
    scanf("%d", &n);

    for (i = 0; i < n; ++i) {
        scanf("%s %s", cmd, msg);
        sum = 0;
        for (j = 0; j < strlen(cmd); ++j) 
            sum += cmd[j]; 
        switch (cmd[0])
        {
        /* 插入 */
        case 'i':
               
            list_add(&(create_node(msg)->list), &(dictionary[sum & (dictionary_size - 1)]));
            break;
        
        /* 查找 */
        case 'f':

                
            break;

        default:
            break;
        }
    }
    // int *A = calloc(2, sizeof(int));
    // A[0] = 1;
    // A[1] = 2;
    // for (size_t i = 0; i < 2; ++i) {
    //     printf("%d\n", A[i]);
    // }
    // free(head);
    return 0;
}