/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: tree_walk.c
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: 树的遍历
时间	   	: 2020-09-04 09:31
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
    POST_ORDER = 2,  
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

    /* 1. 递归退出条件 */
    if (node->type == LEAF) {
        op(tree, id, father);
        return;
    }

    if (type == PRE_ORDER) 
        op(tree, id, father);
    
    traversal(tree, node->child[0], id, type, op);
    if (type == IN_ORDER) 
        op(tree, id, father);
    traversal(tree, node->child[1], id, type, op);

    if (type == POST_ORDER) 
        op(tree, id, father);

}

/**
 * show - 显示节点信息
 * @tree:   树
 * @id:     节点编号
 * @father: 父节点编号	
 * @return: 无
 */
void show(Node *tree, int id, int father)
{   
    printf("%d ", id);
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
    traversal(tree, 0, -1, POST_ORDER, clearup_node);
}

/* 
测试:
9
0 1 4
1 2 3
2 -1 -1
3 -1 -1 
4 5 8
5 6 7
6 -1 -1
7 -1 -1
8 -1 -1
 */
const int MAX = 100;
int main(int argc, char *argv[])
{
    SET_DEFAULT_LEVEL(CONSOLE_LOGLEVEL_INFO);
    int n, i, j;
    int id, degree;
    int child[2];
    
    scanf("%d", &n);

    Node *tree = calloc_buf(n, Node);
    
        for (i = 0; i < n; i++) {
        scanf("%d", &id);
        degree = 0;
        for (j = 0; j < 2; ++j) {
            scanf("%d", child + j);
            if (child[j] != -1)
                ++degree;
        }
        insert(tree, id, degree, child);
    }
    double start = START();
    
    printf("Preorder\n");
    traversal(tree, 0, -1, PRE_ORDER, show);
    printf("\nInorder\n");
    traversal(tree, 0, -1, IN_ORDER, show);
    printf("\nPostorder\n");
    traversal(tree, 0, -1, POST_ORDER, show);
    printf("\n");
    clearup(tree);
    free_buf(tree);

    FINISH(start);
    return 0;
}