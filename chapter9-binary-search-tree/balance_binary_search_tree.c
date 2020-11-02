/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: balance_binary_search_tree.c
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: 平衡二叉搜索树
时间	   	: 2020-09-07 13:50
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
    struct Node *parent;
    struct Node *left;
    struct Node *right;

    int lh, rh;         /* 左右子树的高度 */
    
    int key;
} Node;

/* 右旋 */
#define ROTATE_R(node)  ({  \
    typeof( (node) ) __parent = (node)->parent; \
    typeof( (node) ) __child = (node)->left;    \
    (node)->left = __child->right;              \
    (node)->lh = __child->rh;                   \
    __child->right = (node);                    \
    __child->rh += 1;                           \
    if (__parent.left == (node)) __parent.left = __child;   \
    else __parent.right = __child;    })

/* 左旋 */
#define ROTATE_L(node)  ({  \
    typeof( (node) ) __parent = (node)->parent; \
    typeof( (node) ) __child = (node)->right;   \
    (node)->right = __child->left;              \
    (node)->rh = __child->lh;                   \
    __child->left = (node);                     \
    __child->lh += 1;                           \
    if (__parent.left == (node)) __parent.left = __child;   \
    else __parent.right = __child;       })

/* 先左旋后右旋 */
#define ROTATE_LR(node) ({  \
    ROTATE_L( (node)->left );         \
    ROTATE_R( (node) );     })  

/* 先右旋后左旋 */
#define ROTATE_RL(node) ({  \
    ROTATE_R( (node)->right );       \
    ROTATE_L( (node) );     }) 
 
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
 * @parent: 当前子树的父节点(特别的根节点的父节点为NULL)
 * @key:    待插入键值	
 * @return: 无
 */
void insert(Node **tree, Node *parent, int key)
{
    /* 来到所需的叶节点, 插入 */
    if (*tree == NULL) {
        *tree = calloc_node(key);
        (*tree)->parent = parent;   
        return;
    }

    /* 向左子树插 */
    if (key <= (*tree)->key)
        insert(&(*tree)->left, *tree, key);
    /* 向右子树插 */
    else
        insert(&(*tree)->right, *tree, key);
}


/* 测试:
18
insert 8
insert 2
insert 3
insert 7
insert 22
insert 1
find 1
find 2
find 3
find 4
find 5
find 6
find 7
find 8
print
delete 3
delete 8
print

 */
const int MAX = 100;
int main(int argc, char *argv[])
{
    // SET_DEFAULT_LEVEL(CONSOLE_LOGLEVEL_ERR);
    int n = 0, i;

    int A[MAX];
    int key;
    char cmd[20];
    Node *tree = NULL;

    scanf("%d", &n);

    for (i = 0; i < n; ++i) {
        scanf("%s", cmd);
        switch (cmd[0])
        {
        case 'i':
            scanf("%d", &key);
            insert(&tree, -1, key);
            break;
        
        // case 'f':
        //     scanf("%d", &key);
        //     printf("%s\n", find(tree, key) ? "yes" : "no");
        //     break;

        // case 'd':
        //     scanf("%d", &key);
        //     delete(&tree, key);
        //     break;
        
        // case 'p':
        //     traversal(tree, IN_ORDER, show);
        //     printf("\n");
        //     traversal(tree, PRE_ORDER, show);
        //     printf("\n");
        //     break;

        default:
            break;
        }
    }

    // double start = START();
    
    // FINISH(start);
    return 0;
}
