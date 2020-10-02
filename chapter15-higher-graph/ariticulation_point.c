/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: ariticulation_point.c
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: 计算关节点
时间	   	: 2020-09-30 08:31
***************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include "../tools/tools.h"
#include "../tools/list.h"
#include "../tools/log.h"
#include "../tools/graph.h"
#include "../tools/queue.h"

DEFINE_QUEUE_ELEMENT_TYPE(int, queue);

int compare(const void *arg1, const void *arg2);

/**
 * dfs - 深度优先搜索
 * @G:          图(邻接表表示)	
 * @current:    当前遍历的顶点
 * @prev:       当前遍历的顶点的父顶点
 * @prenum:     保存各顶点的遍历顺序
 * @lowest:     保存各顶点的访问结束的顺序, 为
 *                  1. prenum[u]
 *                  2. u 所有子树的 lowest
 *                  3. 存在回边 (u, v) 时, prebum[v]
 *              最小值
 * @parent:     保存顶点的父节点      
 * @state:      各顶点的访问状态, false 未访问过
 * @return: 无
 */
void dfs(_Vertex_ *G, int current, int prev, int *prenum, int *lowest, int *parent, bool *state)
{   
    static int time = 1;
    int v;
    _adj_node_ *node;
    _Vertex_ *vertex = G + current;

    /* 1. 初始化 lowest 与 prenum 一致 */
    prenum[current] = time;
    lowest[current] = time;
    ++time;

    /* 2. 标记该顶点已访问过 */
    state[current] = true;

    /* 3. 访问与 id 邻接的顶点 */
    list_for_each_entry(node, &(vertex->list), list) {
        if (state[node->id] == false) {
            /* 4. 设置父节点 */
            parent[node->id] = current;

            dfs(G, node->id, current, prenum, lowest, parent, state);

            /* 5. 单前 current 的 lowest, 为 lowest[current] 和 current 子树 lowest 的较小值 */
            lowest[current] = min(lowest[current], lowest[node->id]);

        /* 回边的处理, 将当前顶点的合并到回边所邻接的顶点上 */
        } else if (node->id != prev) {
            lowest[current] = min(lowest[current], prenum[node->id]);
        }
    }
}

/**
 * art_pts - 计算关节点
 * @G:	        图(邻接表)
 * @cout:	    图中顶点的个数
 * @out:	    保存关节点序号
 * @return:     无
 */
void art_pts(_Vertex_ *G, size_t count, queue *out)
{   
    int num = 0;    /* 根节点子树的个数 */
    int p;          /* 保存父节点索引 */
    int i;          
    
    /* 1. 所需要使用的变量 */
    bool state[count];
    int prenum[count];
    int lowest[count];
    int parent[count];

    /* 2. 初始化 */
    memset(state, 0, count * sizeof(bool));
    memset(prenum, 0, count * sizeof(int));
    memset(lowest, 0, count * sizeof(int));
    memset(parent, 0, count * sizeof(int));

    /* 3. 深度优先搜索确定各个数组的值, 其中根的父节点为 -1 */
    dfs(G, 0, -1, prenum, lowest, parent, state);

    /* 4. 依据数组的值判断关节点的个数 */
    for (i = 1; i < count; ++i) {
        p = parent[i];
        if (p == 0) {
            ++num;
        
        /* 设顶点 i 的父节点 p, 当 prenum[p] <= lowest[i], 则 p 为关节点  */
        } else if (prenum[p] <= lowest[i]) {
            qpush(out, p);
        }
    }

    /* 根节点有两个以上中的子节点, 则根节点为关节点 */
    if (num >= 2)   
        qpush(out, 0);
}

/* 测试:
4 4
0 1
0 2
1 2
2 3

4 8
0 1
1 0
0 2
2 0
1 2
2 1 
2 3
3 2 

 */
int main(int argc, char *argv[])
{
    // SET_DEFAULT_LEVEL(CONSOLE_LOGLEVEL_ERR);
    int i;
    int n, e, s, t;

    int vertex;
    _adj_node_ *node;
    
    scanf("%d %d", &n, &e);

    _Vertex_ *G = calloc_buf(n, _Vertex_);
    init(G, n);

    queue *out = calloc_buf(1, queue);
    assert(qinit(out, n + 1));

    for (i = 0; i < e; ++i) {
        scanf("%d %d", &s, &t);
        (G + s)->id = s;
        insert(G, s, t, 0);
    }

    double start = START();

    art_pts(G, n, out);

    qsort(out->data, qsize(out), sizeof(int), compare);
    trace(out->data, qsize(out));

    FINISH(start);

    clear_G(G, n);
    free_buf(G);
    return 0;
}

int compare(const void *arg1, const void *arg2)
{
    int ret = 0;
    int __arg1 = *(int *)arg1;
    int __arg2 = *(int *)arg2;

    if (__arg1 < __arg2) ret = -1;
    else if (__arg1 > __arg2) ret = 1;

    return ret;
}