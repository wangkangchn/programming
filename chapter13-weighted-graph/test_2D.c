/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: test_2D.c
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: 测试向函数传递二维数组
时间	   	: 2020-09-19 10:14
***************************************************************/
#include <stdio.h>
#include <string.h>
#include "../tools/tools.h"
#include "../tools/log.h"

// 然后作为实参传递时，也不能直接使用a传递，因为类型不匹配，必须定义新的变量p，然后把a的值赋给p，再传递给foo函数。
void show(int **G, int num)
{
    printf("\n");
    for (int i = 0; i < num; ++i) {
        for (int j = 0; j < num; ++j)
            printf("%d ", *(((int *)G + i * num) + j));
        printf("\n");
    }

}

/* 测试:
5
-1 2 3 1 -1
2 -1 -1 4 -1
3 -1 -1 1 1
1 4 1 -1 3
-1 -1 1 3 -1

*/

const int MAX = 100;
int main(int argc, char *argv[])
{
    // SET_DEFAULT_LEVEL(CONSOLE_LOGLEVEL_INFO);
    int n = 0, i, j;

    scanf("%d", &n);

    int G[n][n];

    for (i = 0; i < n; ++i) 
        for (j = 0; j < n; ++j)  
            scanf("%d", &G[i][j]);

    // for (i = 0; i < n; ++i) 
    //     p[i] = G[i];
    printf("%zd\n", sizeof(G));
    double start = START();
    show((int **)G, n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j)
            printf("%d ", *(((int *)G + i * n) + j));   /* ooo 我明白了, 要先把 G 转为 int *, 不然G+1加的是整个数组的大小  */
        printf("\n");
    // }

    FINISH(start);
    return 0;
}

