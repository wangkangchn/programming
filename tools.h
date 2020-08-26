/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: types.h
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: 常用工具
时间	   	: 2020-08-19 10:02
***************************************************************/
#ifndef __TYPES_H__
#define __TYPES_H__

/* ==================================================================
    自定义类型
    ----------------------------------------------------------------- */
    typedef __signed__ char __s8;
    typedef unsigned char __u8;

    typedef __signed__ short __s16;
    typedef unsigned short __u16;

    typedef __signed__ int __s32;
    typedef unsigned int __u32;

    #if defined(__GNUC__)
    __extension__ typedef __signed__ long long __s64;
    __extension__ typedef unsigned long long __u64;
    #endif
/* ================================================================== */

int swap(int A[], int num, int i, int j);

/**
 * trace - 按顺序输出数组元素
 * @A:      待排序数组	
 * @num:    数组元素个数
 */
#define trace(A, num) ({    \
    for (int i = 0; i < num; ++i) { \
        if (i > 0) printf(" ");     \
        printf("%d", A[i]);         \
    }                               \
    printf("\n");})

#endif // !__TYPES_H__