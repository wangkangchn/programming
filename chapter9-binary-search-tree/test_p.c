/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: test_p.c
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: 测试指针
时间	   	: 2020-10-29 09:20
***************************************************************/
#include <stdio.h>
#include "../tools/tools.h"
#include "../tools/log.h"

typedef struct Node {
    struct Node *next;
} Node;

int main(int argc, char *argv[])
{

    Node *head = calloc_buf(1, Node);
    head->next = calloc_buf(1, Node);

    // pr_debug("&(head->next): %p, &(head->next): %p");
    printf("asdsda\r12");
  
    return 0;
}