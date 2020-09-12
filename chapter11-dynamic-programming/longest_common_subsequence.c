/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: longest_common_subsequence.c
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: 求最长公共子序列
        Note:
            1. 需要注意的是动态规划不仅仅是我只前想的那样, 在操作之外还有一个数组来保存前面的结果,
            而是可以直接在数组上进行操作, 利用前面计算的结果计算后面的结果
时间	   	: 2020-09-11 09:33
***************************************************************/
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include "../tools/tools.h"
#include "../tools/log.h"


/**
 * lcs - 求解两个字符串的最长公共长度
 * @X:	第一个字符串
 * @Y:      第二个字符串
 * @return: 返回最小公共长度
 */
int lcs(char *X, char * Y)
{
    size_t m = strlen(X);
    size_t n = strlen(Y);
    pr_debug("m: %zd n: %zd\n", m, n);

    char buf_X[m+2];
    char buf_Y[n+2];

    sprintf(buf_X, " %s", X);
    sprintf(buf_Y, " %s", Y);
    pr_debug("buf_X:%s\n", buf_X);
    pr_debug("buf_Y:%s\n", buf_Y);

    int i, j;
    int maxv;
    int c[m + 1][n + 1];
    memset(c, 0, (m + 1) * (n + 1) * sizeof(int));

    for (i = 1; i <= m; ++i) {
        for (j = 1; j <= n; ++j) {
            if (buf_X[i] == buf_Y[j])
                c[i][j] = c[i - 1][j - 1] + 1;
            else 
                c[i][j] = max(c[i - 1][j], c[i][j - 1]);
            maxv = max(maxv, c[i][j]);
        }
    }
    
    return maxv;
}

/* 测试：
3
abcbdab
dbcaba
abc
abc
abc
bc
 */
const int MAX = 100;
int main(int argc, char *argv[])
{
    SET_DEFAULT_LEVEL(CONSOLE_LOGLEVEL_INFO);
    int q = 0, i;
    int c[MAX][MAX];    /* 保存各子序列的 LCS */
    int m, n;
    char X[1024], Y[1024];     /* 保存输入的字符串 */

    scanf("%d", &q);    

    double start = START();
    for (i = 0; i < q; ++i) {
        scanf("%s", X);
        scanf("%s", Y);
        printf("%d\n", lcs(X, Y));
    }
    FINISH(start);
    return 0;
}