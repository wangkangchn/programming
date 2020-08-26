/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: compute_area.c
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: 计算积水面积
时间	   	: 2020-08-25 16:40
***************************************************************/
#include <stdio.h>
#include <string.h>

#include "../tools/stack.h"
#include "../tools/log.h"

DEFINE_ELEMENT_TYPE(int, stack);

void trace(int A[], int num);
int compute(char A[], int num, int areas[], struct stack *S);

const int MAX = 100;
int main(int argc, char *argv[])
{
    int i;
    char A[MAX];                /* 接受输入 */
    int areas[MAX], count_area = 0;  /* 保存各区域面积和区域个数 */
    int area = 0;
	struct stack *S = calloc(1, sizeof(struct stack));

    if (init(S, MAX) == 0)    
        pr_err("stack init failed.\n");

    scanf("%s", A);

    /* \\///\-/\/\\\\/-/\\/// 
    \\///\-/\/\\\\/-/\\///--\\\-\\/-\/-/\*/
    count_area = compute(A, strlen(A) + 1, areas, S);
    area = 0;
    for (i = 0; i < count_area; ++i)
        area += areas[i];
    printf("%d\n", area);
    trace(areas, count_area);
    
    return 0;
}

/**
 * trace - 按顺序输出数组元素
 * @A:      待排序数组	
 * @num:    数组元素个数
 * @return: 无
 */
void trace(int A[], int num) 
{
    int i;
    for (i = 0; i < num; ++i) {
        if (i > 0) printf(" "); /* 仅在量元素之间输出空格 */
        printf("%d", A[i]);
    }
    printf("\n");
}

/**
 * compute - 计算各区域面积, 每次计算一行
 * @A:      断面
 * @num:    数组A的大小
 * @areas:  保存各部分面积	
 * @S:      计算过程中使用的栈
 * @return: 区域个数
 */
int compute(char A[], int num, int areas[], struct stack *S)
{   
    int i, count_area = 0;
    int area = 0;    
    printf("%s\n", A);
    for (i = 0; i < num; ++i) {
        switch (A[i])
        {
        case '\\':
            /* 空栈并且遇到\认为一个区域开始 */
            if (is_empty(S)) {

                area = 0;
            }
            push(S, i);
            break;
        
        case '-':
            /* 忽略 - */
            break;
        
        case '/':
            /* 栈中已空说明右边高, 继续读取 */
            if (is_empty(S)) 
                break;

            area += (i - pop(S));

             if (is_empty(S)) 
                areas[count_area++] = area; /* 保存上一次结果 */
            break;

        default:
            break;
        }
    }

    if (is_empty(S) == 0) 
        areas[count_area++] = area;
    trace(areas, count_area);
    return count_area;
}
