/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: queue.c
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: 环形队列
时间	   	: 2020-08-22 19:44
***************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "/home/wkangk/utils/tools/tools.h"
#include "/home/wkangk/utils/tools/log.h"

#include "my_queue.h"

const int MAX_LENGTH = 100;

int main(int argc, char *argv[])
{
    int ret = 0;
    int n, q, total = 0;
    struct Node temp;
    initialize(MAX_LENGTH);
    scanf("%d %d", &n, &q);
    for (size_t i = 0; i < n; ++i) {
        scanf("%s %d", temp.name, &temp.time);
        // printf("输出: %s\n", temp.name);
        enqueue(temp);
    }

    printf("输出: \n");

    while (!is_empty()) {
        temp = dequeue();   /* 获取队首元素 */
        // printf("啊哈哈 %s %d\n", temp.name, temp.time);
        if (temp.time > q) {
            temp.time -= q;
            enqueue(temp);
            total += q;
        } else {
            total += temp.time;
            printf("%s %d\n", temp.name, total);
        }
    }

    

LAB(return):
    return ret;
}
