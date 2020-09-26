/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: all_pairs_shortest_path.c
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: 计算所有点对间的最短路径(Floyd)
时间	   	: 2020-09-26 10:42
***************************************************************/
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <stdbool.h>
#include "../tools/tools.h"
#include "../tools/log.h"
#include "../tools/list.h"

#define iteration(count)    \
    for (size_t i = 0; i < count; ++i) 

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


/**
 * floyd - 任意两点间的最短路径(Floyd)
 * @G:      待计算图(邻接表)
 * @n:      图中顶点的个数
 * @d:      图中任意两点间的最短路径长度, 如: d[i][j] 为 i -> j 的最短路径长度
 * @p:      图中任意两点间的最短路径上的最后一个节点, 如: p[i][j] == k, 即 i -> j 最短路径上
 *          的最后一个顶点为 k, 通过递归向前搜索就可以得到整条路径
 * @return: 无
 */
void floyd(int **G, size_t n, int **d, int **p)
{   
    int i, j, k;
    int temp, temp_k;
    /* 初始化 d 为 G, 初始化 p 为 -1 */
    for (i = 0; i < n; ++i) {
        for (j = 0; j < n; ++j) {
            *(((int *)d + i * n) + j) = *(((int *)G + i * n) + j);
            *(((int *)p + i * n) + j) = -1;
        }
    }

    /* 绕行顶点 k */
    for (k = 0; k < n; ++k) {
        for (i = 0; i < n; ++i) {
            for (j = 0; j < n; ++j) {
                temp = *(((int *)d + i * n) + j);
                temp_k = *(((int *)d + i * n) + k) + *(((int *)d + k * n) + j);
                if (temp > temp_k) {
                    *(((int *)d + i * n) + j) = temp_k;
                    *(((int *)p + i * n) + j) = k;
                }
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

/**
 * list2matrix - 将图的邻接表表示法表示为邻接矩阵
 * @G:      图的邻接表
 * @n:      图中顶点的个数
 * @matrix: 转换后的邻接矩阵
 * @return: 无
 */
void list2matrix(Vertex *G, int n, int **matrix)
{
    /* 1. 初始化邻接矩阵权重为 INFTY */
    int i, j, temp;
    adj_node *node;

    for (i = 0; i < n; ++i) 
        for (j = 0; j < n; ++j) {
            temp = INFTY;
            if (i == j)
                temp = 0;
            *(((int *)matrix + i * n) + j) = temp;
        }
        
    /* 2. 转换 */
    for (i = 0; i < n; ++i) 
        list_for_each_entry(node, &((G + i)->list), list) 
            *(((int *)matrix + i * n) + node->id) = node->w;
}

/**
 * show_matrix - 显示矩阵元素
 * @matrix:     矩阵元素
 * @row:          矩阵行数
 * @col:        矩阵列数
 * @return:     无
 */
bool show_matrix(int w)
{
    printf("%d ", w);
    return true;
}

/**
 * traverse_matrix - 遍历矩阵
 * @matrix:     矩阵元素
 * @row:          矩阵行数
 * @col:        矩阵列数
 * @op:         对矩阵元素执行的操作
 * @return:     全部遍历完成返回 true, 否则返回 false
 */
bool traverse_matrix(int **matrix, size_t row, size_t col, bool (*op)(int))
{   
    int i, j, w; 
    for (i = 0; i < row; ++i)  {
        for (j = 0; j < col; ++j) {
            w = *(((int *)matrix + i * row) + j);
            if (op(w))
                continue;
            else {
                return false;
            }
        }
        printf("\n");
    }
    return true;
}

/**
 * show_path - 显示各顶点间的最短路径长度, 不存在时输出 INF
 * @w:        路径长度
 * @return:   true
 */
bool show_path(int w)
{   
    if (w != INFTY)     
        printf("%d ", w);
    else                
        printf("INF ");
    return true;
}

/**
 * check_degative_cycle - 检查图中是否存在负环
 * @G:      图(邻接矩阵)	
 * @return: 存在负环返回 true, 否则返回 false
 */
bool check_degative_cycle(int w)
{
    if (w < 0) {
        printf("DEGATIVE CYCLE\n");
        return false;
    } else 
        return true;
}

/* 测试:
5
0 3 2 3 3 1 1 2
1 2 0 2 3 4
2 3 0 3 3 1 4 1
3 4 2 1 0 1 1 4 4 3
4 2 2 1 3 3

4 6
0 1 1
0 2 5
1 2 2
1 3 4
2 3 1
3 2 7

4 6
0 1 1
0 2 -5
1 2 2
1 3 4
2 3 1
3 2 7

4 6
0 1 1
0 2 5
1 2 2
1 3 4
2 3 1
3 2 -7

测试 无向图
5 14
0 2 3 
0 3 1 
0 1 2
1 0 2 
1 3 4
2 0 3
2 3 1
2 4 1
3 2 1 
3 0 1 
3 1 4 
3 4 3
4 2 1 
4 3 3

5 14
0 2 -3 
0 3 -1 
0 1 -2
1 0 -2 
1 3 -4
2 0 -3
2 3 -1
2 4 -1
3 2 -1 
3 0 -1 
3 1 -4 
3 4 -3
4 2 -1 
4 3 -3

 */
const int MAX = 100;
int main(int argc, char *argv[])
{
    SET_DEFAULT_LEVEL(CONSOLE_LOGLEVEL_INFO);
    int n, e, i, s, t, w;
    int vertex;
    adj_node *node;
    
    scanf("%d %d", &n, &e);

    Vertex *G = calloc_buf(n, Vertex);
    init(G, n + 1);

    int p[n]; memset(p, 0, n * sizeof(n));
    int d[n]; memset(d, 0, n * sizeof(n));
    

    for (i = 0; i < e; ++i) {
        scanf("%d %d %d", &s, &t, &w);
        (G + s)->id = s;
        insert(G, s, t, w);
    }

    double start = START();

    int matrix[n][n];
    int matrix_d[n][n];
    int matrix_p[n][n];

    list2matrix(G, n, (int **)matrix);

    start = START();
    
    floyd((int **)matrix, n, (int **)matrix_d, (int **)matrix_p);

    pr_debug("检查负环\n");
    if (traverse_matrix((int **)matrix_d, n, n, check_degative_cycle)) {
        pr_debug("显示路径\n");
        traverse_matrix((int **)matrix_d, n, n, show_path);
    }

    FINISH(start);

    clear_G(G, n);
    free_buf(G);
    
    return 0;
}
