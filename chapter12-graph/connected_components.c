/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: connected_components.c
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: 连通分量 (无向图)
时间	   	: 2020-09-17 10:21
***************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "../tools/tools.h"
#include "../tools/log.h"
#include "../tools/list.h"

typedef enum vertex_state {
    NOT_VISIT,
    VISITED,
} vertex_state;

typedef struct Vertex {
    int id;
    vertex_state state;
    struct list_head list;
} Vertex;

typedef struct adj_node {
    int id;
    struct list_head list;
} adj_node;

typedef struct Relationship {
    int master, friend;
} Relationship;

/**
 * search_relationship - 深度优先搜索的方式搜索是否存在朋友关系
 * @G:	        邻接表表示的图
 * @master_id:  待搜索的人的id
 * @friend_id:  待搜索的朋友的id
 * @return:     存在朋友关系返回 true, 否则返回 false
 */
bool search_relationship(Vertex *G, int master_id, int friend_id)
{
    bool exist = false; /* 默认不存在 */

    adj_node *node;

    /* 以深度搜索的方式遍历待搜索的人的朋友关系, 这样会得到其所有的朋友关系 */
    Vertex *master = G + master_id, *vertex;    
    master->state = VISITED;

    /* 开始遍历顶点 id 的邻接点 */
    list_for_each_entry(node, &(master->list), list) {
        vertex = G + node->id;
        if (vertex->state == NOT_VISIT) {
            if (vertex->id == friend_id) {
                exist = true;
                break;
            } 
            exist = search_relationship(G, vertex->id, friend_id);
        }
    }

    return exist;
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
    for (size_t i = 0; i < count; ++i) 
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
    for (size_t i = 0; i < count; ++i) {
        (G + i)->id = i;    /* 初始化用户 id */
        (G + i)->state = NOT_VISIT;
        INIT_LIST_HEAD(&((G + i)->list));
    }
}


const int MAX = 100;

/* 测试:
10 9
0 1
0 2
3 4
5 7
5 6
6 7
6 8
7 8
8 9
3
0 1
5 9
1 3

*/

int main(int argc, char *argv[])
{
    SET_DEFAULT_LEVEL(CONSOLE_LOGLEVEL_INFO);
    int n , m;          /* n 用户数, m 关系数 */
    int s, t;           /* 一对朋友 */
    int q;
    
    int i, j;
    int vertex;
    adj_node *node;

    scanf("%d %d", &n, &m);

    Vertex *G = calloc_buf(n, Vertex);
    init(G, n);

    for (i = 0; i < m; ++i) {
        scanf("%d %d", &s, &t);
        insert(G, s, t);
        insert(G, t, s);    /* 无向图 */
        /* 开始遍历顶点 id 的邻接点 */
        // printf("插入: ");
        // list_for_each_entry(node, &((G + i)->list), list) 
        //     printf("%d ", node->id);
        
        // printf("\n");
    }

    double start = START();

    scanf("%d", &q);
    Relationship Q[q];              /* 问题数 */
    memset(Q, 0, q * sizeof(*Q));

    for (i = 0; i < q; ++i) 
        scanf("%d %d", &((Q + i)->master), &((Q + i)->friend));
        
    for (i = 0; i < q; ++i) {
        printf("%s\n", search_relationship(G, (Q + i)->master, (Q + i)->friend) ? "yes" : "no");
        for (j = 0; j < n; ++j) 
            (G + j)->state = NOT_VISIT;
    }
    clear_G(G, n);
    free_buf(G);
    FINISH(start);
    return 0;
}