/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: rooted_tree.c
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: 有根树的表达
时间	   	: 2020-09-02 20:34
***************************************************************/
#include <stdio.h>
#include "../tools/tools.h"
#include "../tools/log.h"

enum NodeType     
{   ROOT = 0,    
    INTERNAL_NODE = 1,  
    LEAF = 2,  
};

enum TraversalType     
{   PRE_ORDER = 0,    
    IN_ORDER = 1,  
    POST_OTDER = 2,  
};


typedef struct 
{
    int *child;

    int father;
    int depth;
    int degree;
    enum NodeType type;

} Node;

/**
 * insert - 向树中插入节点
 * @tree:	待插入树
 * @id:     节点编号
 * @degree: 节点度(含有多少子节点)
 * @child:  子树列表
 * @return:无
 */
void insert(Node *tree, int id, int degree, int *child)
{
    /* 确定类型 */
    if (id == 0) 
        tree[id].type = ROOT;

    if (degree != 0 ) {
        if (id != 0) 
            tree[id].type = INTERNAL_NODE;
    
        tree[id].degree = degree;
        tree[id].child = calloc_buf(degree, int);  
        /* 保存子节点 */ 
        for (size_t i = 0; i < degree; ++i) 
            tree[id].child[i] = child[i];
    } else 
        tree[id].type = LEAF;

}

/**
 * traversal - 遍历树(先根法)
 * @tree:	待遍历的树
 * @id:     节点编号
 * @father: 父节点编号
 * @type:   遍历类型(先根和后根)
 * @op:     遍历过程中执行的操作
 * @return: 无
 */
void traversal(Node *tree, int id, int father, enum TraversalType type, void (*op)(Node *, int, int))
{
    Node *node = tree + id;

    if (type == PRE_ORDER) {
        /* 1. 对节点执行操作 */
        op(tree, id, father);

        /* 2. 递归退出条件 */
        if (node->type == LEAF) 
            return;
    }

    /* 3. 由左到右对子树进行遍历 */
    for (size_t i = 0; i < node->degree; ++i) 
        traversal(tree, node->child[i], id, type, op);

    if (type == POST_OTDER) {
        /* 1. 对节点执行操作 */
        op(tree, id, father);

        /* 2. 递归退出条件 */
        if (node->type == LEAF) 
            return;
    }
}

/**
 * show - 显示节点信息
 * @tree:   树
 * @id:     节点编号
 * @father: 父节点编号	
 * @return: 无
 */
void show_node(Node *tree, int id, int father)
{   
    Node *node = tree + id;

    /* 计算深度 */    
    if (id != 0)
        tree[id].depth = tree[father].depth + 1;  
    else
        tree[id].depth = 0;

    printf("node %d: ", id);
    printf("parent = %d, ", father);
    printf("depth = %d, ", node->depth);

    switch (node->type)
    {
    case INTERNAL_NODE:
        printf("internal node, ");
        break;
    
    case LEAF:
        printf("leaf, ");
        break;

    case ROOT:
        printf("root, ");
        break;

    default:
        break;
    }
    printf("[");
    for (size_t i = 0; i < node->degree; ++i) {
        if (i > 0) printf(", ");
        printf("%d", node->child[i]);
    }
    printf("]\n");

}

/**
 * ftree - 显示树信息
 * @tree:	树
 * @return: 无
 */
void show(Node *tree)
{
    traversal(tree, 0, -1, PRE_ORDER, show_node);
}

/**
 * clearup_node - 清理节点 
 * @tree:   树
 * @id:     节点编号
 * @father: 父节点编号	
 * @return: 无
 */
void clearup_node(Node *tree, int id, int father)
{
    if ((tree + id)->child)
        free_buf((tree + id)->child);
}

/**
 * clearup - 清理节点中子节点使用的内存, 释放tree空间
 * @tree:   树	
 * @return: 无
 */
void clearup(Node *tree)
{
    traversal(tree, 0, -1, POST_OTDER, clearup_node);
}

/* 
测试:
13
0 3 1 4 10
1 2 2 3
2 0
3 0
4 3 5 6 7
5 0
6 0
7 2 8 9
8 0
9 0
10 2 11 12
11 0
12 0
 */
const int MAX = 100;
int main(int argc, char *argv[])
{
    SET_DEFAULT_LEVEL(CONSOLE_LOGLEVEL_INFO);
    int n, i, j;
    int id, degree;
    int child[MAX];
    
    scanf("%d", &n);

    Node *tree = calloc_buf(n, Node);
    
    for (i = 0; i < n; i++) {
        scanf("%d %d", &id, &degree);
        for (j = 0; j < degree; ++j) 
            scanf("%d", child + j);
        insert(tree, id, degree, child);
    }
    show(tree);
    pr_debug("show没问题\n");
    clearup(tree);
    pr_debug("clearup没问题\n");
    free_buf(tree);
    return 0;
}