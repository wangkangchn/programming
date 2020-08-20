/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: stable_sort.c
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: 判断算法是否为稳定排序
时间	   	: 2020-08-20 15:46
***************************************************************/
#include <stdio.h>
// #include "tools.h"

struct Card
{
    char suit;
    int value;
};

/**
 * bubble_sort - 冒泡排序 升序
 * @C:      待排序数组	
 * @num:    数组元素个数
 * @return: 无
 */
int bubble_sort(struct Card *C, int N)
{   
    int count = 0;
    int j, i;
    struct Card temp; 
    int is_disorder = 1;    /* 是否存在属性相反的元素, 即标记排序数列是否是无序的 */

    /* 从后向前, 小的浮底 */
    for (i = 0; i < N - 1; ++i) {
        for (j = N - 1; j > i; --j) {
            /* 交换 */
            if (C[j].value < C[j - 1].value) {
                temp = C[j];
                C[j] = C[j - 1];
                C[j - 1] = temp;
            }
        }   
    }
    return count;
}


/**
 * selection_sort - 选择排序, 升序
 * @C:      待排序数组	
 * @num:    数组元素个数
 * @return: 无
 */
void selection_sort(struct Card C[], int num)
{   
    struct Card temp;
    int i, j, minj; 

    for (i = 0; i < num - 1; ++i) { /* 同样最后一次不需要遍历, 因为每次会排序好前面的元素 */
        minj = i;
        for (j = i; j < num; ++j) {
            if (C[j].value < C[minj].value) 
                minj = j;   /* 保存此次循环的最小值 */
        }
        /* 交换 */
        if (i != minj) {
            temp = C[i];
            C[i] = C[minj];
            C[minj] = temp;
        }
    }
}

static const int MAX = 100;


int main(int argc, char *argv[])
{
    int n = 0, i, count = 0;
    struct Card C1[MAX], C2[MAX];
    char temp[3];

    scanf("%d", &n);
    
    for (i = 0; i < n; ++i) {
        scanf("%s", temp);
        C1[i].suit = temp[0];
        C1[i].value = temp[1] - '0'; 
        C2[i].suit = temp[0];
        C2[i].value = temp[1] - '0'; 
    }
    
    bubble_sort(C1, n);
    for (i = 0; i < n; ++i) {
        if (i > 0) printf(" "); /* 仅在量元素之间输出空格 */
        printf("%c%d", C1[i].suit, C1[i].value);
    }
    printf("\nStable\n");

    selection_sort(C2, n);
    for (i = 0; i < n; ++i) {
        if (i > 0) printf(" "); /* 仅在量元素之间输出空格 */
        printf("%c%d", C2[i].suit, C2[i].value);
    }
    for (i = 0; i < n; ++i) {
        
        if ((C1[i].suit == C2[i].suit) && (C1[i].value == C2[i].value)) 
            continue;
        else 
            break;

    }
    if (i == n)
        printf("\nStable\n");
    else
        printf("\nNot stable\n");
    

    return 0;
}
