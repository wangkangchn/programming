/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: disjoint_set.c
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: Union Find Tree
时间	   	: 2020-09-23 08:26
***************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "../tools/tools.h"
#include "../tools/log.h"
#include "disjoint_set.h"


/* 测试:
5 12
0 1 4
0 2 3
1 1 2
1 3 4
1 1 4
1 3 2
0 1 3
1 2 4
1 3 0
0 0 4
1 0 2
1 3 0
 */
int main(int argc, char *argv[])
{
    // SET_DEFAULT_LEVEL(CONSOLE_LOGLEVEL_INFO);
    int n, q, i;

    scanf("%d %d", &n, &q);
    int cmd[q], x[q], y[q];

    disjoint_set *set = calloc_buf(1, disjoint_set);
    make_set(set, n);
    
    for (i = 0; i < q; ++i) {
        scanf("%d %d %d", cmd + i, x + i, y + i);
    }    

    for (i = 0; i < q; ++i) {
        switch (cmd[i])
        {
        /* unite */
        case 0:
            unite(set, x[i], y[i]);
            break;
        
        case 1:
            printf("%d\n", same(set, x[i], y[i]) ? 1 : 0);
            break;
        
        default:
            break;
        }
    }

    

    double start = START();
    
    FINISH(start);
    return 0;
}