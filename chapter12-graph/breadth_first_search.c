/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: breadth_first_search.c
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: 广度优先搜索
时间	   	: 2020-09-16 08:27
***************************************************************/
#include <stdio.h>
#include <assert.h>
#include "../tools/tools.h"
#include "../tools/log.h"
#include "../tools/queue.h"
#include "../tools/list.h"

const int MAX = 100;

typedef struct Vertex {
    int id;
    int dist;   /* 顶点 1 到该顶点的距离*/
    struct list_head list;
} Vertex;

/* 邻接表顶点 */
typedef struct adj_node {
    int id;
    struct list_head list;
} adj_node;


DEFINE_QUEUE_ELEMENT_TYPE(int, queue);

/**
 * breadth_first_search - 广度优先搜索得到从顶点1到某个顶点的最短距离
 * @G:      图(邻接表表示)	
 * @id:     搜索的起点
 * @return: 无
 */
void breadth_first_search(Vertex *G, int id)
{
    Vertex *vertex;
    adj_node *node;
    int vertex_id, dist = -1;
    queue *Q = calloc_buf(1, queue);
    assert(qinit(Q, MAX));

    (G + id)->dist = 0; /* 初始化起点距离为0 */
    qpush(Q, id);

    /* 因为广度优先搜索时先搜索顶点的所有邻接顶点, 搜索完所有邻接顶点后会从第一个邻接顶点继续
    广度搜索他的邻接顶点, 而后搜索第二个顶点的所有邻接顶点, 这样搜索的顺序就和上一步搜索的顺序一致
    所以用队列最方便实现. */
    while(!qis_empty(Q)) {
        /* 获取待搜索顶点 */
        vertex_id = qpop(Q);
        
        pr_debug("搜索 %d\n", vertex_id);

        vertex = G + vertex_id;

        /* 搜索其邻接顶点 */
        list_for_each_entry(node, &(vertex->list), list) {
            pr_debug("搜索 %d 的邻接顶点 %d\n", vertex_id, node->id);
            qpush(Q, node->id);
            if (((G + node->id)->dist) == -1) {
                (G + node->id)->dist = vertex->dist + 1;
                pr_debug("增加 %d 距离\n", node->id);
            }
        }
    }
    free_buf(Q);
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
        printf("%d %d\n", vertex->id, vertex->dist);
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
    for (size_t i = 0; i < count; ++i) 
        INIT_LIST_HEAD(&((G + i)->list));
}



/* 测试:
4
1 2 2 4
2 1 4
3 0
4 1 3

*/
int main(int argc, char *argv[])
{
    SET_DEFAULT_LEVEL(CONSOLE_LOGLEVEL_INFO);
    int n = 0, i, u, k, j;
    int vertex;
    adj_node *node;

    scanf("%d", &n);

    Vertex *G = calloc_buf(n + 1, Vertex);
    /* 初始化距离为-1 */
    for (i = 1; i <= n; ++i)
        (G + i)->dist = -1;
    init(G, n + 1);

    for (i = 1; i <= n; ++i) {
        scanf("%d %d", &u, &k);
        (G + i)->id = u;
        for (j = 0; j < k; ++j) {
            scanf("%d", &vertex);
            insert(G, u, vertex);
        }
        // /* 开始遍历顶点 id 的邻接点 */
        // printf("插入: ");
        // list_for_each_entry(node, &((G + i)->list), list) 
        //     printf("%d ", node->id);
        
        // printf("\n");
    }

    double start = START();

    breadth_first_search(G, 1);
    show(G, n+1);
    clear_G(G, n+1);
    free_buf(G);
    FINISH(start);
    return 0;
}