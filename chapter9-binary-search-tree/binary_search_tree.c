/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: binary_search_tree.c
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: 二叉搜索树(插入)
            1. 搜索时间复杂度 当输入平衡时为 O(logn)
                             最坏成为单链表 O(n)
时间	   	: 2020-09-06 21:17
***************************************************************/
#include <stdio.h>
#include <stdbool.h>
#include "../tools/tools.h"
#include "../tools/log.h"

enum TraversalType     
{   PRE_ORDER = 0,    
    IN_ORDER = 1,  
    POST_ORDER = 2,  
};

typedef struct Node {
    struct Node *left;
    struct Node *right;

    int key;
} Node;

/**
 * calloc_node - 分配节点空间, 插入键值
 * @key:	待插入键值
 * @return: 新分配的节点指针
 */
Node* calloc_node(int key)
{
    Node *node =  calloc_buf(1, Node);
    node->key = key;
    return node;
}

/**
 * insert - 向二叉搜索树插入键值
 * @tree:   树
 * @key:    待插入键值	
 * @return: 无
 */
void insert(Node **tree, int key)
{
    pr_debug("\n");
    /* 来到所需的叶节点, 插入 */
    if (*tree == NULL) {
        *tree = calloc_node(key);
        return;
    }

    /* 向左子树插 */
    if (key <= (*tree)->key)
        insert(&(*tree)->left, key);
    /* 向右子树插 */
    else
        insert(&(*tree)->right, key);
        
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
void traversal(Node *tree, enum TraversalType type, void (*op)(Node *))
{   
    pr_debug("\n");
    /* 1. 递归退出条件 */
    if (tree == NULL) {
        return;
    }

    /* 2. 输出前序遍历结果 */
    if (type == PRE_ORDER) 
        op(tree);
    
    /* 3. 遍历左右子树 */
    traversal(tree->left, type, op);
    if (type == IN_ORDER) 
        op(tree);
    traversal(tree->right, type, op);

    if (type == POST_ORDER) 
        op(tree);
}

/**
 * show - 显示节点键值
 * @node:   节点
 * @return: 无
 */
static inline void show(Node *node) { printf("%d ", node->key); }

/* 测试:
8
insert 30
insert 88
insert 12
insert 1
insert 20
insert 17
insert 25
print
 */
const int MAX = 100;
int main(int argc, char *argv[])
{
    SET_DEFAULT_LEVEL(CONSOLE_LOGLEVEL_INFO);
    int n = 0, i;
    int A[MAX];
    int key;
    char cmd[20];
    Node *tree = NULL;

    scanf("%d", &n);

    for (i = 0; i < n; ++i) {
        scanf("%s", cmd);
        if (cmd[0] == 'i') {
            scanf("%d", &key);
            insert(&tree, key);
        } else if (cmd[0] == 'p') {
            traversal(tree, IN_ORDER, show);
            printf("\n");
            traversal(tree, PRE_ORDER, show);
        }
    }
    printf("\n");    

    // double start = START();
    
    // FINISH(start);
    return 0;
}