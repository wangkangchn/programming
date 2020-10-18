/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: polygon_point_containment.c
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: 点的内包
时间	   	: 2020-10-11 10:05
***************************************************************/
#include <stdio.h>
#include "../tools/tools.h"
#include "../tools/log.h"

const int MAX = 100;
int main(int argc, char *argv[])
{
    // SET_DEFAULT_LEVEL(CONSOLE_LOGLEVEL_INFO);
    int n, i;
    int A[MAX];

    scanf("%d", &n);

    for (i = 0; i < n; ++i) 
        scanf("%d", &A[i]);

    double start = START();
    
    FINISH(start);
    return 0;
}