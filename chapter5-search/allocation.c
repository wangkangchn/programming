/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: allocation.c
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: 计算最优解
时间	   	: 2020-08-30 15:58
***************************************************************/
/* 这种问题是, 假设可能的最大值的最大值而后使用二分查找向下搜索 O(logn) */

#include <stdio.h>
#include "../tools/tools.h"

/**
 * compute_goods_num - 依据指定的最大载重量和货车数, 计算所能装载的货物数量 
 * @w:      货物重量数组
 * @num:    数组w的大小 
 * @P:      最大装载量
 * @k:      卡车数	
 * @return: 所能装载的最大货物数量
 */
int compute_goods_num(int *w, int num, int P, int k)
{
    int i = 0, j = 0, single = 0;   /* j 记录已使用的货车数 */
    
    for (i = 0; i < num; ++i) {
        single += w[i];     /* 一辆车的装载量 */
        if (single < P)     /* 单辆车没有满足最大载货量 */
            continue;
        else if (single > P) 
            --i;    /* 退回上一包货物 */

        if (++j < k) 
            single = 0;
        else 
            break;
    }
    // if (P == 10)
    //     printf("i = %d num = %d\n", i, num);
    return i == num ? i : ++i;
}

/**
 * rightP - 从小向大进行二分搜索
 * @w:      货物重量数组
 * @num:    数组w的大小 
 * @P:      最大装载量
 * @k:      卡车数	
 * @leftP:	搜索P的左界线
 * @rightP: 搜索P的右界线
 * @return: 最小的载重量
 */
int search(int *w, int num, int k, int leftP, int rightP)
{
    int goods_num = 0;
    int middleP = (rightP + leftP) / 2;
    // printf("left: %d middle: %d right: %d\n", leftP, middleP, rightP);
    if (leftP < rightP) {
        /* 计算在当前最大P时, 所有货车所能装载的最大货物 */
        goods_num = compute_goods_num(w, num, middleP, k);   
        /* 小于规定的货物数, 在右侧搜索 */  
        if (goods_num < num)
            return search(w, num, k, middleP + 1, rightP);
        /* == 规定的货物数, 在左侧搜索 */
        else if (goods_num == num) 
            return search(w, num, k, leftP, middleP);
    } else 
        return rightP;
}

const int MAX = 100;

int main(int argc, char *argv[])
{
    int n = 0, k = 0, i;
    int A[MAX];     /* 记录货物重量 */
    int P = 0;

    scanf("%d %d", &n, &k);

    for (i = 0; i < n; ++i) {
        scanf("%d", &A[i]);
        P += A[i];
    }
    
    printf("最小载重量: %d\n", search(A, n, k, 1, P));

    return 0;
}