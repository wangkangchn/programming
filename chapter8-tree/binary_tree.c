/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: binary_tree.c
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: 二叉树的表达
时间	   	: 2020-09-03 10:18
***************************************************************/
#include <stdio.h>
#include <string.h>
#include <time.h>
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
    int height;
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
 * @op_pre: 先根操作
 * @oop_post: 后根操作
 * @return: 无
 */
void traversal(Node *tree, int id, int father, void (*op_pre)(Node *, int, int), void (*op_post)(Node *, int, int))
{
    Node *node = tree + id;

    /* 1. 先序遍历对节点执行的操作 */
    op_pre(tree, id, father);

    /* 2. 递归退出条件 */
    if (node->type == LEAF) {
        /* 后序遍历对节点执行的操作 */
        op_post(tree, id, father);
        return;
    }

    /* 3. 由左到右对子树进行遍历 */
    for (size_t i = 0; i < node->degree; ++i) 
        traversal(tree, node->child[i], id, op_pre, op_post);

    /* 4. 后序遍历对节点执行的操作 */
    op_post(tree, id, father);
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

    printf("node %d: ", id);
    printf("parent = %d, ", father);
    printf("sibling = ");
    if (father == -1) printf("%d, ", -1);

    pr_debug("id: %d \n", id);
    for (size_t i = 0; i < tree[father].degree; ++i) {
        
        pr_debug("%d \n", tree[father].child[i]);
        if (tree[father].child[i] != id) {  
            printf("%d, ", tree[father].child[i]);
            break;
        }
    }
    printf("degree = %d, ", node->degree);
    printf("depth = %d, ", node->depth);
    printf("height = %d, ", node->height);

    switch (node->type)
    {
    case INTERNAL_NODE:
        printf("internal node");
        break;
    
    case LEAF:
        printf("leaf");
        break;

    case ROOT:
        printf("root");
        break;

    default:
        break;
    }
    printf("\n");
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
 * ftree - 显示树信息
 * @tree:	树
 * @return: 无
 */
void show(Node *tree)
{
    traversal(tree, 0, -1, show_node, clearup_node);
}

/**
 * compute_node_height - 计算节点深度
 * @tree:   树
 * @id:     节点编号
 * @father: 父节点编号	
 * @return: 无
 */
void compute_node_depth(Node *tree, int id, int father)
{
    /* 计算高度 */
    Node *node = tree + id;

    /* 计算深度 */    
    if (id != 0)
        tree[id].depth = tree[father].depth + 1;  
    else
        tree[id].depth = 0;
}

/**
 * compute_node_height - 计算节点高度 
 * @tree:   树
 * @id:     节点编号
 * @father: 父节点编号	
 * @return: 无
 */
void compute_node_height(Node *tree, int id, int father)
{
    /* 计算高度 */
    int lh = 0, rh = 0;
    pr_debug("id = %d\n", id);
    Node *node = tree + id;   
    if (node->type == LEAF)
        node->height = 0;
    /* 取左右子树高度的较大值 */
    else {
        for (size_t i = 0; i < node->degree; ++i) {
            if (i > 0) {
                rh = tree[node->child[1]].height;
                break;
            }
            lh = tree[node->child[0]].height;
        }
        node->height = max(lh, rh) + 1;
    }
}

/**
 * compute_height - 计算树中各节点的深度个高度
 * @tree:   树	
 * @return: 无
 */
void compute(Node *tree)
{
    traversal(tree, 0, -1, compute_node_depth, compute_node_height);
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
    int child[MAX];
    
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

    compute(tree);
    pr_debug("compute_height没问题\n");
    show(tree);
    pr_debug("show没问题\n");

    free_buf(tree);

    printf( "%f seconds\n", FINISH(start));
    return 0;
}