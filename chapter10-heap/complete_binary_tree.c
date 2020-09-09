/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: complete_binary_tree.c
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: 数组形式实现完全二叉树 (要从1开始, 不能从0开始!!!)
        Note:
            1. 使用数组形式存储完全二叉树的时候, 第一个索引要从1开始
时间	   	: 2020-09-09 08:53
***************************************************************/
#include <stdio.h>
#include "../tools/tools.h"
#include "../tools/log.h"

#define parnet(id)      ({ (id) >> 1; })
#define left(id)        ({ (id) << 1; })
#define right(id)       ({ ( (id) << 1 ) + 1; })

/* 测试:
5
7 8 1 2 3
 */
const int MAX = 100;
int main(int argc, char *argv[])
{
    // SET_DEFAULT_LEVEL(CONSOLE_LOGLEVEL_INFO);
    int n = 0, i;
    int A[MAX];
    int parent, l, r;

    scanf("%d", &n);

    for (i = 1; i <= n; ++i) {
        scanf("%d", &A[i]);
    }

    for (i = 1; i <= n; ++i) {
        printf("node %d: key = %d, ", i, A[i]);
        parent = parnet(i);
        if (parent != 0)
            printf("parent key = %d, ", A[parent]);
        
        l = left(i);
        if (l <= n)
            printf("left key = %d, ", A[l]);

        r = right(i);
        if (r <= n)
            printf("right key = %d, ", A[r]);
        printf("\n");  
    }

    double start = START();
    
    FINISH(start);
    return 0;
}