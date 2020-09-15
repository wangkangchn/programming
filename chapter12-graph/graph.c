/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: graph.c
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: 图的表示, 以邻接表为输入, 输出图的邻接矩阵表示
时间	   	: 2020-09-15 08:54
***************************************************************/
#include <stdio.h>
#include <string.h>
#include "../tools/tools.h"
#include "../tools/log.h"

/* 测试:
4
1 2 2 4
2 1 4
3 0
4 1 3

*/

const int MAX = 100;
int main(int argc, char *argv[])
{
    // SET_DEFAULT_LEVEL(CONSOLE_LOGLEVEL_INFO);
    int n = 0, i, j;
    int u, k, vertex;

    scanf("%d", &n);
    int G[n + 1][n + 1];    /* 1 起点*/
    memset(G, 0, (n + 1) * (n + 1) * sizeof(int));

    for (i = 1; i <= n; ++i) {
        scanf("%d %d", &u, &k);
        for (j = 0; j < k; ++j) {
            scanf("%d", &vertex);
            G[u][vertex] = 1;
        }
    }
        
    for (i = 1; i <= n; ++i) {
        for (j = 1; j <= n; ++j) {
            printf("%d ", G[i][j]);
        }
        printf("\n");
    }

    double start = START();
    
    FINISH(start);
    return 0;
}


