/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: single_source_shortest_path_1.c
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: Dijkstra 算法实现单源最短路径
时间	   	: 2020-09-21 07:57
***************************************************************/
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>
#include "../tools/tools.h"
#include "../tools/list.h"
#include "../tools/log.h"

#define iteration(count)    \
    for (size_t i = 0; i < count; ++i) 

const int INFTY = INT_MAX;

typedef enum vertex_state {
    NOT_VISIT,
    VISITED,
} vertex_state;

typedef struct Vertex {
    int id;
    struct list_head list;
} Vertex;

/* 邻接表顶点 */
typedef struct adj_node {
    int id;
    int w;                  /* 权重 */ 
    struct list_head list;
} adj_node;


/**
 * dijkstra - Dijkstra 算法实现单源最短路径
 * @G:      图(邻接表)
 * @n:      图中顶点的个数  
 * @s:      欲求的最短路径的起点	
 * @d:      保存顶点 s 到到 i 的最短路径成本      
 * @p:      i 在最短路径树中的父节点
 * @return: 无
 */
void dijkstra(Vertex *G, size_t n, int s, int *d, int *p)
{   
    int i;
    int min_w, min_w_index;
    
    adj_node *node;
    
    /* 设置所有顶点状态为未访问, false 未访问过, true 访问过*/
    bool state[n];
    memset(state, 0, n * sizeof(bool));

    /* 初始化所有顶点与 s 的距离为 INFTY */
    for (i = 0; i < n; i++)
        d[i] = INFTY;
    
    /* 设置起点本身的成本与父节点索引(-1) */
    d[s] = 0; p[s] = -1; 
    
    /* 每次选取从 s 开始成本最小的一条路径, 更新终点 i 的所有邻接点 (j,...) 的成本.
    也就是判断一下若起点 s 到终点 j 的路径在节点 i 处中转一次, 是否可以减少成本, 是则更新
    路径, 否则跳过. */
    while (true) {
        min_w = INFTY;
        
        /* 选取从 s 开始成本最小的一条路径 */
        for (i = 0; i < n; i++) {
            if (!state[i] && d[i] < min_w) {
                min_w = d[i];
                min_w_index = i;
            }
        }
        
        /* 所有顶点已选择完 */
        if (min_w == INFTY)
            break;

        pr_debug("选择顶点: %d 权: %d\n", min_w_index, min_w);
        /* 将选择到的节点从 state 中删除, 即将其加入到最短路径树中 */
        state[min_w_index] = true;

        /* 判断一下若起点 s 到终点 j 的路径在节点 i 处中转一次, 是否可以减少成本, 是则更新
        路径, 否则跳过 */
        list_for_each_entry(node, &((G + min_w_index)->list), list) {
            if (state[node->id])
                continue;
            /* u: node_id 
            当 u 从 min_w_index 中转后权重会减少, 则将其父节点更新为 min_w_index */
            pr_debug("遍历邻接顶点: %d\n", node->id);
            if ((min_w + node->w) < d[node->id]) {
                d[node->id] = min_w + node->w;
                p[node->id] = min_w_index;
            } 
        }
    }
}

/**
 * insert - 向邻接表中插入节点(尾插法, 保证小的序号在前)
 * @G:      邻接表
 * @id:     顶点
 * @vertex: 与 id 邻接的顶点
 * @w:      权	
 * @return: 无
 */
void insert(Vertex *G, int id, int vertex, int w)
{
    adj_node *node = calloc_buf(1, adj_node);
    node->id = vertex;
    node->w = w;

    list_add_tail(&(node->list), &((G + id)->list));
}

/**
 * clear_list - 释放队列节点
 * @header:	待清理链表的头指针
 * @return: 无
 */
void clear_list(struct list_head *header)
{
    struct list_head *pos, *q;
    adj_node *node;

    list_for_each_safe(pos, q, header){
        node = list_entry(pos, adj_node, list);
        list_del(pos);
        free_buf(node);
    }
}

/**
 * clear_G - 从小到大显示节点信息
 * @G:	    图
 * @count:  图中节点个数
 * @return: 无
 */
int clear_G(Vertex *G, size_t count)
{
    iteration(count) 
        clear_list(&((G + i)->list));
}

/**
 * init - 初始化队列头邻接表
 * @G:	    图
 * @count:  图中节点个数
 * @return: 无
 */
void init(Vertex *G, size_t count)
{
    iteration(count) {
        INIT_LIST_HEAD(&((G + i)->list));
    }
}


/* 测试:
5
0 3 2 3 3 1 1 2
1 2 0 2 3 4
2 3 0 3 3 1 4 1
3 4 2 1 0 1 1 4 4 3
4 2 2 1 3 3
 */
const int MAX = 100;
int main(int argc, char *argv[])
{
    SET_DEFAULT_LEVEL(CONSOLE_LOGLEVEL_INFO);
    int n = 0, i, u, k, j, w;
    int vertex;
    adj_node *node;

    scanf("%d", &n);

    Vertex *G = calloc_buf(n, Vertex);
    init(G, n + 1);
    int p[n]; memset(p, 0, n * sizeof(n));
    int d[n]; memset(d, 0, n * sizeof(n));
    

    for (i = 0; i < n; ++i) {
        scanf("%d %d", &u, &k);
        (G + i)->id = u;
        for (j = 0; j < k; ++j) {
            scanf("%d %d", &vertex, &w);
            insert(G, u, vertex, w);
        }
    }

    double start = START();

    dijkstra(G, n, 0, d, p);
    
    for (i = 0; i < n; ++i)
        printf("%d %d\n", i, d[i]);
    
    clear_G(G, n);
    free_buf(G);
    FINISH(start);
    return 0;
}
