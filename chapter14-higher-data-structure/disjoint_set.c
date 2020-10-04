/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: disjoint_set.c
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: Union Find Tree
时间	   	: 2020-09-23 08:26
***************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "../tools/tools.h"
#include "../tools/log.h"


/**
 * find_set - 求包含元素 x 的集合的代表元素
 * @@set:   所有的集合
 * @x:	    带求元素
 * @return: x 的集合的代表元素(根)
 */
int find_set(int *set, int x)
{
    int parent;
    int temp = x;
    /* 1. 寻找代表元素 */
    while (true) {
        parent = set[temp];
        if (parent == temp)
            break;
        else
            temp = parent;
    }

    /* 2. 压缩路径 */
    while (true) {
        if (set[x] == x)    /* 不是根 */
            break;
        else {
            temp = set[x];  
            set[x] = parent;/* 调整路径上节点的父直接指向代表元素 */
            x = temp;
        }
    }
    return parent;
}

/**
 * link - 合并两个集合, 将较低的树合并到较高的树中
 * @set:    所有的集合
 * @rank:   记录各节点为根时的树高
 * @x:      树代表元素
 * @y:	    树代表元素
 * @return: 无
 */
void link(int *set, int *rank, int x, int y)
{   
    int father = x, child = y;

    /* x 合并进 y */
    if (rank[x] < rank[y]) {
        father = y;
        child = x;
    }
    ++rank[father];
    set[child] = father;
}


/**
 * unite - 合并指定元素 x, y
 * @set:    所有的集合
 * @rank:   记录各节点为根时的树高
 * @x:      待合并元素
 * @y:	    待合并元素
 * @return: 无
 */
inline void unite(int *set, int *rank, int x, int y)
{
    link(set, rank, find_set(set, x), find_set(set, y));
}

/**
 * same - 判断两元素是否属于同一集合
 * @set:    所有的集合
 * @x:      带判断元素
 * @y:	    带判断元素
 * @return: 同一集合返回 true, 否则返回 false
 */
inline bool same(int *set, int x, int y)
{
    return find_set(set, x) == find_set(set, y);
}


/* 测试:
5 12
0 1 4
0 2 3
1 1 2
1 3 4
1 1 4
1 3 2
0 1 3
1 2 4
1 3 0
0 0 4
1 0 2
1 3 0
 */
int main(int argc, char *argv[])
{
    // SET_DEFAULT_LEVEL(CONSOLE_LOGLEVEL_INFO);
    int n, q, i;

    scanf("%d %d", &n, &q);
    int cmd[q], x[q], y[q];

    int rank[n];    /* 以各节点为根的树的高度 */
    int set[n];     /* 互质集合, 下标为元素, 数组值为该元素父节点 */
    memset(rank, 0, n);

    /* 初始时元素父节点执行自身 */
    for (i = 0; i < n; ++i) 
        set[i] = i;
    
    for (i = 0; i < q; ++i) {
        scanf("%d %d %d", cmd + i, x + i, y + i);
    }    

    for (i = 0; i < q; ++i) {
        switch (cmd[i])
        {
        /* unite */
        case 0:
            unite(set, rank, x[i], y[i]);
            break;
        
        case 1:
            printf("%d\n", same(set, x[i], y[i]) ? 1 : 0);
            break;
        
        default:
            break;
        }
    }

    

    double start = START();
    
    FINISH(start);
    return 0;
}