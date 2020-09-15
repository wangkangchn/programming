/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: depth_first_search.c
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: 深度优先搜索
时间	   	: 2020-09-15 09:10
***************************************************************/
#include <stdio.h>
#include "../tools/tools.h"
#include "../tools/log.h"
#include "../tools/list.h"

typedef struct Vertex {
    int id;
    int d;  /* 该顶点的发现时刻 */
    int f;  /* 该顶点的结束时刻*/
    struct list_head list;
} Vertex;

/* 邻接表顶点 */
typedef struct adj_node {
    int id;
    struct list_head list;
} adj_node;

/**
 * depth_first_search - 深度优先搜索
 * @G:	    邻接表表示的图
 * @id:     带搜索
 * @return: 无
 */
void depth_first_search(Vertex *G, int id)
{
    static int time = 0;

    adj_node *node;
    Vertex *vertex = G + id;

    pr_debug("访问 %d\n", id);
    /* 保存时间 */
    if (G[id].d == 0)
        G[id].d = ++time;   /* 第一次访问的时候要增加时间, 二次访问不算时间 */
    
    if (G[id].f != 0) {
        return;
    }
    /* 开始遍历顶点 id 的邻接点 */
    list_for_each_entry(node, &((G + id)->list), list) {
        depth_first_search(G, node->id);
    }

    /* 当节点没有邻接节点时, 增加遍历自身的时间 */
    G[id].f = ++time;
}

/**
 * insert - 向邻接表中插入节点(尾插法, 保证小的序号在前)
 * @G:      邻接表
 * @id:     顶点
 * @vertex: 与 id 邻接的顶点	
 * @return: 无
 */
void insert(Vertex *G, int id, int vertex)
{
    adj_node *node = calloc_buf(1, adj_node);
    node->id = vertex;

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
 * show - 从小到大显示节点信息
 * @G:	    图
 * @count:  图中节点个数
 * @return: 无
 */
int clear_G(Vertex *G, size_t count)
{
    for (size_t i = 1; i < count; ++i) 
        clear_list(&((G + i)->list));
}

/**
 * show - 从小到大显示节点信息
 * @G:	    图
 * @count:  图中节点个数
 * @return: 无
 */
int show(Vertex *G, size_t count)
{
    Vertex *vertex;
    for (size_t i = 1; i < count; ++i) {
        vertex = G + i;
        printf("%d %d %d\n", vertex->id, vertex->d, vertex->f);
    }
}

/**
 * init - 初始化队列头邻接表
 * @G:	    图
 * @count:  图中节点个数
 * @return: 无
 */
void init(Vertex *G, size_t count)
{
    for (size_t i = 0; i < count; ++i) {
        INIT_LIST_HEAD(&((G + i)->list));
    }
}

const int MAX = 100;

/* 测试:
6
1 2 2 3
2 2 3 4
3 1 5
4 1 6
5 1 6
6 0

*/

int main(int argc, char *argv[])
{
    // SET_DEFAULT_LEVEL(CONSOLE_LOGLEVEL_INFO);
    int n = 0, i, u, k, j;
    int vertex;
    adj_node *node;

    scanf("%d", &n);

    Vertex *G = calloc_buf(n + 1, Vertex);
    init(G, n + 1);

    for (i = 1; i <= n; ++i) {
        scanf("%d %d", &u, &k);
        (G + i)->id = u;
        for (j = 0; j < k; ++j) {
            scanf("%d", &vertex);
            insert(G, u, vertex);
        }
        /* 开始遍历顶点 id 的邻接点 */
        printf("插入: ");
        list_for_each_entry(node, &((G + i)->list), list) 
            printf("%d ", node->id);
        
        printf("\n");


    }

    double start = START();
    
    FINISH(start);
    depth_first_search(G, 1);
    show(G, n+1);
    clear_G(G, n+1);
    free_buf(G);
    return 0;
}