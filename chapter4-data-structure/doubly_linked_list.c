/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: doubly_linked_list.c
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: 
时间	   	: 2020-08-23 09:46
***************************************************************/
/*  Note: 
        1. 头插入 O(1)
        2. 搜索 O(N)
 */
#include <stdio.h>
#include <string.h>
#include "/home/wkangk/utils/tools/tools.h"
#include "/home/wkangk/utils/tools/log.h"

#include "my_dlist.h"

// int my_initialize(struct Node *head)    /* 对这里的head和传入的head是用两块内存保存的, 所以没法用这种方始初始化 */
// {   
//     int ret = 0;
//     head = calloc(1, sizeof(struct Node)); 
//     if (head) {
//         head->next = head->prev = head;
//     } else
//         ret = -1;
//     return ret;
// }


int main(int argc, char *argv[])
{
    int ret = 0;
    int n, key, i = 0;
    char s[100];

    struct Node *head = calloc(1, sizeof(struct Node)); 
    if (head) 
        initialize(head);
    else
        pr_err("error: initialize.\n");

    struct Node *p, *temp;
    

    scanf("%d", &n);
    
    for (size_t i = 0; i < n; ++i) {
        
        scanf("%s %d", s, &key);
    
        if (strcmp(s, "insert") == 0) {

            if(insert(head, key) < 0)
                pr_err("error: insert(space insufficient).\n");

        } else if (strcmp(s, "delete") == 0) {

            if(delete(head, key) < 0)
                pr_err("error: delete(list empty).\n");

        } else if (strcmp(s, "delete_frist") == 0) {

            if(delete_frist(head) < 0)
                pr_err("error: delete_frist(list empty).\n");
        
        } else if (strcmp(s, "delete_last") == 0) {
            
            if(delete_last(head) < 0)
                pr_err("error: delete_last(list empty).\n");
        }
    }


    p = head->next;

    while (p != head) {
        temp = p;
        p = p->next;
        if (i > 0)
            printf(" ");
        printf("%d", temp->key);
        ++i;
        delete_node(temp);
    }
    printf("\n");
    free(head);

LAB(return):
    return ret;
}