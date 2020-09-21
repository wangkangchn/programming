/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: single_source_shortest_path_2.c
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: Dijkstra 算法(优先级队列)实现单源最短路径
        Note:
            1. 向优先级队列中插入删除元素时间复杂度都是 O(logn)
            2. Dijkstra 需要从队列中取出 |V| 次顶点, 所以取出操作时间复杂度为 O(|V| * log|V|),
            Dijkstra 需要向队列插入 |E| 次边(对邻接顶点进行更新, 这里的实现插入的不仅仅是 |E|, 
            因为会多次对队列中已存在的节点进行距离更新, 此时是直接插入了相同 id 的顶点, 而没有做更新
            处理, 因此插入的次数不仅仅是 |E|, 但是也不会多太多, 因为每次确定一个顶点的最短路径, 越往后
            需要更改的值越少)(不对, 就算是更新, 也是图中已有的边, 所以插入次数就是|E|), 所以插入操作时间复杂度为 O(|E| * log|E|),
            因此使用优先级队列实现 Dijkstra 的时间复杂度为 O((|V| + |E|) * log|V|)
            2. 优先级队列 Dijkstra 就是将普通 Dijkstra 中循环选择 min_w, 使用优先级队列实现
时间	   	: 2020-09-21 09:37
***************************************************************/
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>
#include "../tools/tools.h"
#include "../tools/list.h"
#include "../tools/pqueue.h"
#include "../tools/log.h"

#define iteration(count)    \
    for (size_t i = 0; i < count; ++i) 

const int MAX = 100;
const int INFTY = (1 << 20);

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
 * dijkstra - Dijkstra 算法(优先级队列)实现单源最短路径
 * @G:      图(邻接表)
 * @n:      图中顶点的个数  
 * @s:      欲求的最短路径的起点	
 * @d:      保存顶点 s 到到 i 的最短路径成本      
 * @p:      i 在最短路径树中的父节点
 * @return: 无
 */
void dijkstra(Vertex *G, size_t n, int s, int *d, int *p)
{   
    pqueue *Q = calloc(1, sizeof(pqueue));
    pqinit(Q, MAX, compare);

    pair temp;
    int i, u;
    
    adj_node *node;

    bool state[n];
    memset(state, 0, n * sizeof(bool));

    /* 初始化所有顶点与 s 的距离为 INFTY */
    for (i = 0; i < n; i++)
        d[i] = INFTY;
    
    /* 设置起点本身的成本与父节点索引(-1), 将起点加入优先级队列 */
    d[s] = 0; p[s] = -1; 
    pqpush(Q, make_pair(s, -1 * d[s]));

    while (!pqis_empty(Q)) {
        /* 获取当前 V - S 中的最小路径 */
        temp = pqpop(Q);
        u = temp.id;
        state[u] = true;

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

void dijkstra1(Vertex *G, size_t n, int s, int *d, int *p)
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

/* 测试:
5
0 3 2 3 3 1 1 2
1 2 0 2 3 4
2 3 0 3 3 1 4 1
3 4 2 1 0 1 1 4 4 3
4 2 2 1 3 3

 */

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

    printf("优先级队列: \n");
    double start = START();

    dijkstra(G, n, 0, d, p);
    
    for (i = 0; i < n; ++i)
        printf("%d %d\n", i, d[i]);
    
    FINISH(start);

    memset(d, 0, n * sizeof(n));
    memset(p, 0, n * sizeof(n));
    
    printf("普通实现: \n");
    start = START();
    dijkstra(G, n, 0, d, p);
    
    for (i = 0; i < n; ++i)
        printf("%d %d\n", i, d[i]);
    FINISH(start);

    clear_G(G, n);
    free_buf(G);
    
    return 0;
}
