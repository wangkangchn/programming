/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: topological_sort.c
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: 拓扑排序
        Note:
            1. 使用深度优先搜索和广度优先搜索的时间复杂度均为 O(|V| + |E|), 
            遍历所有的顶点与边, 但是当深度优先搜索由递归实现时, 可能造成栈不足
时间	   	: 2020-09-27 08:37
***************************************************************/
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "../tools/tools.h"
#include "../tools/log.h"
#include "../tools/queue.h"
#include "../tools/graph.h"

DEFINE_QUEUE_ELEMENT_TYPE(int, queue);

const int MAX = 100;


/**
 * dfs - 深度优先搜索
 * @G:      图(邻接表表示)	
 * @id:     搜索的起点
 * @indeg:  各顶点的入度
 * @state:  各顶点的访问状态, false 未访问过
 * @out:    保存拓扑排序结果
 * @return: 无
 * @return: 无
 */
void dfs(_Vertex_ *G, int id, int *indeg, bool *state, queue *out)
{   
    int v;
    _adj_node_ *node;
    _Vertex_ *vertex = G + id;

    pr_debug("访问: %d\n", id);
    state[id] = true;

    /* 访问与 id 邻接的顶点 */
    list_for_each_entry(node, &((G + id)->list), list) 
        if (state[node->id] == false)
            dfs(G, node->id, indeg, state, out);

    /* 因为是深度搜索, 一搜到底, 最低下的是依赖前面最多的节点, 
    先输出依赖最多的节点, 这样 out 保存的就是逆序拓扑排序的结果 */
    qpush(out, id);
    pr_info("保存: %d\n", id);
}

/**
 * bfs - 广度优先搜索得到从顶点1到某个顶点的最短距离
 * @G:      图(邻接表表示)	
 * @id:     搜索的起点
 * @indeg:  各顶点的入度
 * @state:  各顶点的访问状态, false 未访问过
 * @out:    保存拓扑排序结果
 * @return: 无
 */
void bfs(_Vertex_ *G, int id, int *indeg, bool *state, queue *out)
{
    _Vertex_ *vertex;
    _adj_node_ *node;

    int u, v;
    queue *Q = calloc_buf(1, queue);
    assert(qinit(Q, MAX));

    qpush(Q, id);
    while(!qis_empty(Q)) {
        /* 1. 获取队列中入度为 0 的顶点 */
        u = qpop(Q);
        
        /* 2. 保存入度为 0 的顶点 */
        qpush(out, u);
        state[u] = true;
        pr_info("保存: %d\n", u);

        /* 3. 删除与 u 邻接的顶点的入度 */
        vertex = G + u;
        list_for_each_entry(node, &(vertex->list), list) {
            v = node->id;
            pr_debug("%d 邻接 %d\n", u, v);
            indeg[v] -= 1;

            /* 4. 因为是广度优先搜索, 所以当邻接点入度变为 0 时, 应优先搜索 */
            if (indeg[v] == 0 && state[v] == false) {
                qpush(Q, v);
                pr_debug("入队: %d\n", v);
                
            } else 
                pr_debug("%d 入度不为 0\n", v);
        }
    }
    free_buf(Q);
}


/**
 * topological_sort - 拓扑排序
 * @G:      图邻接表
 * @count:  顶点个数
 * @count:  各顶点入度
 * @indeg:  各顶点的入度
 * @out:    保存拓扑排序结果
 * @op:     对各个顶点的操作
 * @return: 无
 */
void topological_sort(_graph_ *G, size_t count, int *indeg, queue *out, 
                    void (*op)(_Vertex_ *, int, int *, bool *, queue *))
{
    int i;
    bool state[count];
    memset(state, 0, count * sizeof(bool));
    for (i = 0; i < count; ++i) {
        /* 入度为0, 且为访问过就访问 */
        if (indeg[i] == 0 && state[i] == false) {
            pr_debug("遍历 %d\n", i);
            op(G, i, indeg, state, out);
        }
    }
}

/**
 * show - 显示拓扑排序结果
 * @out:	保存拓扑排序结果的队列
 * @return: 无
 */
void show(queue *out)
{
    pr_debug("size(out): %d\n", qsize(out));
    while (!qis_empty(out)) 
        printf("%d ", qpop(out));
    printf("\n");
}

/**
 * show_reverse - 显示队列结果
 * @out:	逆序保存的拓扑排序结果的队列
 * @return: 无
 */
void show_reverse(queue *out)
{
    for (size_t i = qsize(out) - 1; i >= 0; --i) 
        printf("%d ", out->data[i]);
}

/* 测试:
6 6
0 1
1 2
3 1
3 4
4 5
5 2

 */

int main(int argc, char *argv[])
{
    SET_DEFAULT_LEVEL(CONSOLE_LOGLEVEL_ERR);
    int i;
    int n, e, s, t;

    queue *out = calloc_buf(1, queue);
    assert(qinit(out, MAX));

    int vertex;
    _adj_node_ *node;
    
    scanf("%d %d", &n, &e);

    _Vertex_ *G = calloc_buf(n, _Vertex_);
    init(G, n);
    int indeg[n];
    memset(indeg, 0, n * sizeof(int));

    for (i = 0; i < e; ++i) {
        scanf("%d %d", &s, &t);
        (G + s)->id = s;
        ++indeg[t];
        insert(G, s, t, 0);
    }
    // trace(indeg, n);

    double start = START();
    pr_debug("开始拓扑排序: 基于广度优先搜索\n");
    topological_sort(G, n, indeg, out, bfs);
    show(out);

    pr_debug("\n开始拓扑排序: 基于神度优先搜索\n");
    topological_sort(G, n, indeg, out, dfs);
    show(out);

    FINISH(start);

    clear_G(G, n);
    free_buf(G);
    return 0;
}