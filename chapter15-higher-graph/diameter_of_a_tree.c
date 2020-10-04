/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: diameter_of_a_tree.c
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: 计算树的直径, 边上权为距离, 故树的直径是距离最远的两个结点间的距离
            1. 使用 Floyd 或者 Dijkstra 来求解所有节点对间的最远距离, 即为树的直径
            2. 
                (1) 任取一个结点 s, 求到 s 最远的结点 x 
                (2) 求到 x 最远的结点 y, x 与 y 之间的距离, 即为直径
时间	   	: 2020-10-04 14:10
***************************************************************/
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "../tools/tools.h"
#include "../tools/log.h"
#include "../tools/graph.h"
#include "../tools/pqueue.h"

typedef struct pair {
    int id;
    int cost;
} pair;

DEFINE_PQUEUE_ELEMENT_TYPE(pair, pqueue);

int compare(const void *arg1, const void *arg2)
{
    int ret = 0;
    pair __arg1 = *(pair *)arg1;
    pair __arg2 = *(pair *)arg2;

    if (__arg1.cost < __arg2.cost) ret = -1;
    else if (__arg1.cost > __arg2.cost) ret = 1;

    return ret;
}

#define make_pair(key, val) ({  \
    pair p = {  \
        .id = key,  \
        .cost = val,    \
    };   \
    p;  \
})

/**
 * dijkstra - Dijkstra 算法(优先级队列)实现单源最短路径, 求权值全负图的最长路径
 * @G:      图(邻接表)
 * @n:      图中顶点的个数  
 * @s:      欲求的最短路径的起点	
 * @d:      保存顶点 s 到到 i 的最短路径成本      
 * @p:      i 在最短路径树中的父节点
 * @return: 无
 */
void dijkstra(_Vertex_ *G, size_t n, int s, int *d, int *p)
{   
    pqueue *Q = calloc(1, sizeof(pqueue));
    pqinit(Q, n, compare);

    int i, u;
    _adj_node_ *node;
    pair temp;   
    
    bool state[n];
    memset(state, 0, n * sizeof(bool));

    /* 1. 初始化所有顶点与 s 的距离为 INFTY */
    for (i = 0; i < n; i++)
        d[i] = WEIGHT_INFTY;
    
    /* 设置起点本身的成本与父节点索引(-1), 将起点加入优先级队列 */
    d[s] = 0; p[s] = -1; 
    pqpush(Q, make_pair(s, -1 * d[s])); /* 这是构建的大根堆 */

    while (!pqis_empty(Q)) {
        /* 获取当前 V - S 中的最小路径 */
        
        temp = pqpop(Q);
        u = temp.id;
        state[u] = true;
        pr_debug("遍历: %d\n", u);
        if (d[u] < -1 * temp.cost)       /* 这一步是为了消除多次插入的相同元素 */
            continue;

        list_for_each_entry(node, &((G + u)->list), list) {
            if (state[node->id])
                continue;
            if ((temp.cost + node->w) < d[node->id]) {
                d[node->id] = -1 * temp.cost + node->w;
                p[node->id] = u;
                pqpush(Q, make_pair(node->id, d[node->id] * -1));
            } 
        }
    }

    pqclear(Q);
    free(Q);
}

/**
 * diameter_tree - 求树的直径, 因树就是一种特殊的图, 故可以使用图的最短路径搜索算法
 *              对树进行求解, 只不过, 这里的边上的权要全取一下相反数
 * @G:      图(邻接表)
 * @n:      图中顶点的个数  
 * @return:     树的直径
 */
int diameter_tree(_Vertex_ *G, size_t n)
{   
    int i, x;
    int diameter = 0;
    int p[n], d[n];

    /* 1. 任取一个结点 s, 求到 s 最远的结点 x */
    memset(d, 0, n * sizeof(int));
    memset(p, 0, n * sizeof(int));
    dijkstra(G, n, 0, d, p);    /* s = 0 */
    for (i = 0; i < n; ++i) {
        if (diameter < (-1 * d[i])) {
            diameter = -1 * d[i];
            x = i;
        }
    }

    /* 2. 求到 x 最远的结点 y, x 与 y 之间的距离, 即为直径 */
    diameter = 0;
    dijkstra(G, n, x, d, p);    /* s = 0 */
    for (i = 0; i < n; ++i) {
        if (diameter < (-1 * d[i])) {
            diameter = -1 * d[i];
        }
    }

    return diameter;
}

/* 测试:
4
0 1 2
1 2 1
1 3 3

 */
const int MAX = 100;
int main(int argc, char *argv[])
{
    SET_DEFAULT_LEVEL(CONSOLE_LOGLEVEL_INFO);
    int i, j;
    int n, e, s, t, w;

    _adj_node_ *node;
    
    scanf("%d", &n);

    /* 1. 分配初始化图 */
    _Vertex_ *G = calloc_buf(n, _Vertex_);
    init(G, n);

    /* 2. 插入 */
    for (i = 0; i < (n - 1); ++i) {
        scanf("%d %d %d", &s, &t, &w);
        (G + s)->id = s;
        /* 无向图 */
        insert(G, s, t, -1 * w);
        insert(G, t, s, -1 * w);
    }

    double start = START();
    
    printf("%d\n", diameter_tree(G, n));

    FINISH(start);
    clear_G(G, n);
    free_buf(G);
    return 0;
}