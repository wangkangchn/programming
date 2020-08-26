/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: stack.c
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: 数组栈
时间	   	: 2020-08-20 20:00
***************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* 全局变量 栈顶指针 */
int top;
int *S = NULL;
int MAX;

int initialize(int max);
int is_empty(void);
int is_full(void);
int push(int val);
int pop(void);

int main(int argc, char *argv[])
{
    char s[100];
    int a,b;
    initialize(1000);

    while (scanf("%s", s) != EOF) { /* linux 中 scanf 是自己抛弃换行啊 */
        switch (s[0])
        {
        case '+':
            push(pop() + pop());
            break;
        
        case '-':
            a = pop();
            b = pop();
            printf("%d\n", b-a);
            push(b-a);
            break;
        
        case '*':
            push(pop() * pop());
            break;

        case '#':
            goto lab_ret;
            break;

        default:
            push(atoi(s));
            break;
        }
        
    }
lab_ret:
    printf("%d\n", pop());
    return 0;
}


/**
 * initialize - 初始化栈顶指针, 分配栈空间
 * @max:	栈最大长度
 * @return: 成功返回0, 失败返回-1
 */
inline int initialize(int max)
{
    top = -1;
    MAX = max;
    S = calloc(1, MAX);
    if (S)
        return 0;
    return -1;
}

/**
 * is_empty - 判断栈是否为空
 * @return: 空返回1, 非空返回0
 */
inline int is_empty(void) { return top < 0; }

/**
 * is_full - 判断栈是否为满
 * @return: 满返回1, 非满返回0
 */
inline int is_full(void) { return top >= MAX - 1; }

/**
 * push - 向栈顶添加元素
 * @val:	待插入值
 * @return: 成功返回0, 失败返回-1
 */
inline int push(int val)
{
    int ret = 0;
    if (!is_full()) 
        S[++top] = val;
    else 
        ret = 0;
    return ret;
}

/**
 * pop - 弹出栈顶元素
 * @val:	待插入值
 * @return: 成功返回栈顶元素, 失败返回-1
 */
inline int pop(void)
{
    int ret = -1;
    if (!is_empty()) 
        ret = S[top--];
    return ret;
}