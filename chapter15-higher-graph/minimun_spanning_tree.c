/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: minimun_spanning_tree.c
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: kruskal 实现最小生成树
时间	   	: 2020-10-04 16:07
***************************************************************/
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../tools/tools.h"
#include "../tools/log.h"
#include "../tools/graph.h"
#include "../tools/queue.h"
#include "../tools/disjoint_set.h"

typedef struct edge {
    int s, t;
    int w;
} edge;

DEFINE_QUEUE_ELEMENT_TYPE(int, queue);

int compare(const void *arg1, const void *arg2)
{
    int ret = 0;
    edge __arg1 = *(edge *)arg1;
    edge __arg2 = *(edge *)arg2;

    if (__arg1.w < __arg2.w) ret = -1;
    else if (__arg1.w > __arg2.w) ret = 1;

    return ret;
}

/**
 * kruskal - 实现最小生成树
 * @E:      边的集合
 * @en:     边的个数
 * @return: 最小生成树的各边权值之和
 */
int kruskal(edge *E, size_t en)
{   
    int i;
    int weight = 0;
    edge e;
    queue *S = calloc(1, sizeof(queue));
    assert(qinit(S, en));

    /* 1. 构建初始的 union find 集合 */
    disjoint_set *set = calloc_buf(1, disjoint_set);
    make_set(set, en);

    /* 1. 将边集 E 进行升序排序 */
    qsort(E, en, sizeof(*E), compare);

    /* 2. 先合并权重最小的边 */
    for (i = 0; i < en; ++i) { 
        e = E[i];
        
        /* 判断边 e 两端的顶点是否有公共的父节点, 即将该边加入最小生成树时
        是否会构成回路 */
        if (!same(set, find_set(set, e.s), find_set(set, e.t))) {
            /* 不会构成环时, 将 e 加入最小生成树, 即在 set 中将两者合并 */
            pr_debug("添加边: %d %d %d\n", e.s, e.t, e.w);
            unite(set, e.s, e.t);
            qpush(S, e.w);
        }
    }
    
    while(!qis_empty(S))
        weight += qpop(S);
    
    free(S);
    free_buf(set);
    return weight;
}

/* 测试:
6 9
0 1 1
0 2 3
1 2 1
1 3 7
2 4 1
1 4 3
3 4 1
3 5 1 
4 5 6

  */
int main(int argc, char *argv[])
{
    SET_DEFAULT_LEVEL(CONSOLE_LOGLEVEL_INFO);
    int i, j;
    int n, e, s, t, w;

    scanf("%d %d", &n, &e);
    edge E[n];
    memset(E, 0, n * sizeof(edge));

    for (i = 0; i < e; ++i) {
        scanf("%d %d %d", &s, &t, &w);
        /* 加入边集 */
        E[i].s = s;
        E[i].t = t;
        E[i].w = w;
    }

    double start = START();
    
    printf("%d\n", kruskal(E, e));

    FINISH(start);
    return 0;
}