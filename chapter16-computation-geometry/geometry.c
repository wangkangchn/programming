/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: geometry.c
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: 计算几何
时间	   	: 2020-10-05 14:21
***************************************************************/
#include <stdio.h>
#include "../tools/tools.h"
#include "../tools/log.h"
#include "geometry.h"
// #include   <math.h>

const int MAX = 100;
int main(int argc, char *argv[])
{
    // SET_DEFAULT_LEVEL(CONSOLE_LOGLEVEL_INFO);
    Point p1 = {1, 2};
    Point p2 = {2, 3};
    Point p3 = {1, 2};

    show_point(vadd(p1, p2));
    show_point(vsub(p1, vmul(p1, 2)));
    show_point(vmul(p1, 2));
    show_point(vdiv(p1, 2));
    
    printf("vabs(p1): %f\n", vabs(p1));
    printf("vabs(p1): %f\n", 1.0/2 );
    printf("fabs(p1): %f\n", fabs(-1.0) );
    printf("vequal(p1, p2): %d\n", vequals(p1, p3) );
    printf("vless(p1, p2): %d\n", vless(p1, p3) );
    printf("vcross(p1, p1): %f\n", vcross(p1, p1) );

    return 0;
}