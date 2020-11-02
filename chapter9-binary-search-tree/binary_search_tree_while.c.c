/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: binary_search_tree_while.c.c
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: 二叉搜索树 循环实现
时间	   	: 2020-09-22 11:03
***************************************************************/
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "../tools/tools.h"
#include "../tools/log.h"
#include "../tools/list.h"
#include "../tools/abs_tree.h"

DEFINE_BSTREE_ELEMENT_TYPE(double, bstree_node, bstree);


int compare(const void *arg1, const void *arg2)
{
    int ret = 0;
    double __arg1 = *(double *)arg1;
    double __arg2 = *(double *)arg2;

    if (fabs(__arg1 - __arg2) < 1e-8) ret = 0;
    else if (__arg1 < __arg2)   ret = -1;
    else                        ret = 1;

    return ret;
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
void traversal(bstree_node *tree, enum TraversalType type, void (*op)(bstree_node *))
{   
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
static inline void show(bstree_node *node) { printf("%lf ", *node->data); }

int balance(bstree_node **tree)
{   
    int rh = (*tree)->rh;
    int lh = (*tree)->lh;
    int diff = lh - rh;
    if ((diff > 0 ? diff : -1 * diff) > 1) {
        
        /* 左子树高 */
        if (diff > 0) {
            /* LL 型 */
            if (unbalanced_direction((*tree)->left, 1)) {
                pr_debug("LL\n");
                LL(tree);
            /* LR 型 */
            } else {
                pr_debug("LR\n");
                LR(tree);
            }

        /* 右子树高 */    
        } else if (diff < 0) {
            /* RL 型 */
            if (unbalanced_direction((*tree)->right, 0)) {
                pr_debug("RL\n");
                RL(tree);
            /* RR 型 */
            } else {
                pr_debug("RR\n");
                RR(tree);
            }    
        }
        lh = (*tree)->lh;
        rh = (*tree)->rh;
    }
    return max(lh, rh);
}

/**
 * insert - 向二叉搜索树插入键值
 * @tree:   树(二级指针, 数指针的地址)
 * @key:    待插入键值	
 */
void insert(bstree *tree, double *val)   
{   
    pr_debug("插入: %lf\n", *val);
    bstree_node **node = &( (tree)->root ); 
    bstree_node *__temp = calloc_node( (val), typeof( *((tree)->root) ) );  
    bstree_node *__parent = NULL;   /* 保存父节点 */
    int h = 0;
    while (*node != NULL) {
        __parent = *node;
        if ( (tree)->__compare( __temp->data, (*node)->data ) <= 0 ) 
            node = &(*node)->left; 
        else 
            node = &(*node)->right;                    
    }
    __temp->parent = __parent;  /* 根节点的父为 NULL */
    (*node) = __temp;           /* 将新节点添加到二叉树 */

    /* 插入根节点时, 不调整 */
    if (__parent) {
         /* 由插入的位置不断向上计算树高, 对不满足条件的分支进行调整 */
        while (true) {
            __temp = *node;
            node = &((*node)->parent);  /* 找到父节点 */

            if (is_left(__temp)) {
                pr_debug("左子树\n");
                (*node)->lh = balance(node) + 1;
            } else {
                pr_debug("右子树\n");
                (*node)->rh = balance(node) + 1;
            }

            if ((*node)->parent == NULL)
                break;
        }
    }
}

/* 测试:

 */
const int MAX = 100;
int main(int argc, char *argv[])
{
    // SET_DEFAULT_LEVEL(CONSOLE_LOGLEVEL_ERR);
    int n = 0, i;
    double _key;
    
    bstree tree = {
        .root = NULL,
        .__compare = compare,
    };
    // bstree_node *tree = NULL;

    n = 5;

    for (i = 0; i < n; ++i) {
        _key = (double)i;
        insert(&tree, &_key);
    }
    printf("中序遍历\n");
    traversal(tree.root, IN_ORDER, show);
    return 0;
}