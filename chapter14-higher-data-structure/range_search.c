/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: range_search.c
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: 范围搜索 (KD 树)
时间	   	: 2020-09-23 09:22
***************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "../tools/tools.h"
#include "../tools/log.h"
#include "../tools/pqueue.h"

DEFINE_PQUEUE_ELEMENT_TYPE(int, pqueue);

const int NIL = -1;

typedef struct point {
    int id;
    int x, y;
} point;

typedef struct kd_tree_node {
    point pt;
    int l, r;
} kd_tree_node;

typedef struct kd_tree {
    int count;
    kd_tree_node *tree;
} kd_tree;

/**
 * init - 初始化 kd 树
 * @tree:	kd 树指针
 * @num:	树中节点个数
 * @return: 无
 */
static void init(kd_tree *tree, int num)
{
    tree->tree = calloc_buf(num, kd_tree_node);
    tree->count = -1;
}

int compare_x(const void *arg1, const void *arg2)
{
    int ret = 0;
    point __arg1 = *(point *)arg1;
    point __arg2 = *(point *)arg2;

    if (__arg1.x < __arg2.x) ret = -1;
    else if (__arg1.x > __arg2.x) ret = 1;

    return ret;
}

int compare_y(const void *arg1, const void *arg2)
{
    int ret = 0;
    point __arg1 = *(point *)arg1;
    point __arg2 = *(point *)arg2;

    if (__arg1.y < __arg2.y) ret = -1;
    else if (__arg1.y > __arg2.y) ret = 1;

    return ret;
}

int compare_id(const void *arg1, const void *arg2)
{
    int ret = 0;
    point __arg1 = *(point *)arg1;
    point __arg2 = *(point *)arg2;

    if (__arg1.id < __arg2.id) ret = -1;
    else if (__arg1.id > __arg2.id) ret = 1;

    return ret;
}

/**
 * make_2D_tree - 建立二维 KD 树
 * @tree:   kd tree
 * @pts:	点集    
 * @num:	点个数
 * @depth:	树的深度, 当深度为偶数时以 x 为基准进行划分,
 *                   当深度为奇数时以 y 为基准进行划分,
 * @return: 插入树中的当前节点的编号, -1 表示没有子树
 */
int make_2D_tree(kd_tree *tree, point *pts, int num, int depth)
{   
    static int count = 0;
    int id, mid;

    point pt;
    pr_info("num = %d \n", num);
    if (num <= 0)
        return NIL;
    
    /* 1. 根据 depth 选择基准对点集进行排序 */
    if (depth % 2 == 0) 
        qsort(pts, num, sizeof(point), compare_x);
    else
        qsort(pts, num, sizeof(point), compare_y);

    /* 2. 选取中点为根 */
    mid = num / 2;
    pr_debug("mid = %d \n", mid);

    // if (++count >= 10)
    //     return NIL;
    id = ++tree->count;
    tree->tree[id].pt = pts[mid];
    tree->tree[id].l = make_2D_tree(tree, pts, mid, depth + 1);    /* 左闭右开 */
    pr_warning("进入右子树\n");
    tree->tree[id].r = make_2D_tree(tree, pts + mid + 1, num - mid - 1, depth + 1);
    
    return id;
}

/**
 * find_2D - 在二维点集上搜索指定范围内的点
 * @tree:   kd tree
 * @id:     搜索的起始点
 * @x_lower:   x下界
 * @x_upper:   x上界
 * @y_lower:   y下界
 * @y_upper:   y上界
 * @depth:	树的深度, 当深度为偶数时以 x 为基准进行划分,
 *                   当深度为奇数时以 y 为基准进行划分
 *                   当为 d 维时, 利用 depth % d, 每次对一个维度进行排序, 而后进行划分
 * @Q:     保存点坐标
 * @return:    无
 */
int find_2D(kd_tree *tree, int id, 
                int x_lower, int x_upper, 
                int y_lower, int y_upper, 
                int depth, pqueue *Q)
{
    static int count = -1;
    kd_tree_node *node;
    point pt;
    int x, y;
    if (id != NIL) {
        node = tree->tree + id;
        pt = node->pt;
        x = pt.x;
        y = pt.y;
        if (x >= x_lower && x <= x_upper && y >= y_lower && y <= y_upper) {
            pqpush(Q, -1 * pt.id);
            pr_debug("top: %d\n", pqtop(Q));
        }
        
        if (depth % 2 == 0) {
            if (x >= x_lower) 
                find_2D(tree, node->l, x_lower, x_upper, y_lower, y_upper, depth + 1, Q);
            
            if (x <= x_upper)
                find_2D(tree, node->r, x_lower, x_upper, y_lower, y_upper, depth + 1, Q);

        } else {
            if (y >= y_lower) 
                find_2D(tree, node->l, x_lower, x_upper, y_lower, y_upper, depth + 1, Q);
            
            if (y <= y_upper)
                find_2D(tree, node->r, x_lower, x_upper, y_lower, y_upper, depth + 1, Q);
        }
    }
}

/**
 * show_pqueue - 显示优先级队列中的内容
 * @Q:      优先级队列	
 * @return: 无
 */
void show_pqueue(pqueue *Q)
{   
    int id;
    while (!pqis_empty(Q)) {
        id = pqpop(Q);
        printf("%d\n", -1 * id);
    }
}
/* 测试:
6
2 1
2 2
4 2
6 2
3 3
5 4
2
2 4 0 4
4 10 2 5

 */
const int MAX = 100;
int main(int argc, char *argv[])
{

    SET_DEFAULT_LEVEL(CONSOLE_LOGLEVEL_FATAL);
    int n, i, q, count;
    int x_lower, x_upper, y_lower, y_upper;
    
    point *pts;
    kd_tree *tree = calloc_buf(1, kd_tree);

    scanf("%d", &n);
    init(tree, n);
    pts = calloc_buf(n, point);

    pqueue *Q = calloc(1, sizeof(pqueue));
    pqinit(Q, n + 1, compare_id);

    for (i = 0; i < n; ++i) {
        scanf("%d %d", &((pts + i)->x), &((pts + i)->y));
        (pts + i)->id = i;
    }

    make_2D_tree(tree, pts, n, 0);

    scanf("%d", &q);
    for (i = 0; i < q; ++i) {
        scanf("%d %d %d %d", &x_lower, &x_upper, &y_lower, &y_upper);
        find_2D(tree, 0, x_lower, x_upper, y_lower, y_upper, 0, Q);


        show_pqueue(Q);

        printf("\n");
    }

    free_buf(tree);
    free_buf(pts);

    return 0;
}
