/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: priority_queue_while.c.c
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: 循环实现优先级队列
时间	   	: 2020-09-11 09:44
***************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../tools/tools.h"
#include "../tools/pqueue.h"
#include "../tools/log.h"

typedef int heap_element;

DEFINE_PQUEUE_ELEMENT_TYPE(heap_element, pqueue);

int compare(const void *arg1, const void *arg2)
{
    int ret = 0;
    heap_element __arg1 = *(heap_element *)arg1;
    heap_element __arg2 = *(heap_element *)arg2;

    if (__arg1 < __arg2) ret = -1;
    else if (__arg1 > __arg2) ret = 1;

    return ret;
}

/* 测试:
insert 8
insert 2
insert 10
insert 11
insert 5
insert 7
insert 3
insert 3
extract
extract
extract
extract
extract
extract
extract
extract
end


insert 10
extract 
insert 11
insert 3
insert 7
extract 
insert 5
extract 
insert 7
insert 3
extract 
extract 
end

*/
const int MAX = 100;
const int root = 1;
int main(int argc, char *argv[])
{
    // SET_DEFAULT_LEVEL(CONSOLE_LOGLEVEL_INFO);
    pqueue *Q = calloc(1, sizeof(pqueue));
    int i;
    size_t count = 0;
    char cmd[20];

    pqinit(Q, MAX, compare);

    heap_element key;

    double start = START();
    for (; ;) {
        scanf("%s", cmd);
        /* 插入树根, 而后向下调整 */
        if (strcmp(cmd, "insert") == 0) {
            scanf("%d", &key);
            pqpush(Q, key);
            
        /* 删除, 将最后一个节点键值上提到树根, 而后向下调整 */
        } else if (strcmp(cmd, "extract") == 0) {
            printf("%d\n", pqpop(Q));
            
        } else {
            pqclear(Q);
            break;
        }
    }

    FINISH(start);
    pqclear(Q);
    free_buf(Q);
    return 0;
}