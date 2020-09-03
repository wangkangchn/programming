/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: the_num_of_inversions.c
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: 逆序数
时间	   	: 2020-09-02 19:30
***************************************************************/
#include <stdio.h>
#include "../tools/tools.h"
#include "../tools/log.h"

const int MAX = 100;
int main(int argc, char *argv[])
{
    // SET_DEFAULT_LEVEL(CONSOLE_LOGLEVEL_INFO);
    int n = 0, i;
    int A[MAX];

    scanf("%d", &n);

    for (i = 0; i < n; ++i) 
        scanf("%d", &A[i]);

    return 0;
}