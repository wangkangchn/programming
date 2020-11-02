/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: binary_search_tree.c
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: 二叉搜索树(插入, 查找, 删除)
            1. 搜索时间复杂度 当输入平衡时为 O(logn)
                             最坏成为单链表 O(n)
            2. 查找, 删除 O(logn)
时间	   	: 2020-09-06 21:17
***************************************************************/
#include <stdio.h>
#include <stdlib.h>
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

    int lh, rh;
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
 * find - 在二叉搜索树中搜索指定的键值
 * @tree:   树
 * @key:	待搜索的键值
 * @return: 找到成功返回true, 失败返回false
 */
bool find(Node *tree, int key)
{
    /* 没有找到 */
    if (tree == NULL) 
        return false;

    /* 在左子树上搜索 */
    if (key < tree->key)
        find(tree->left, key);
    /* 在右子树上搜索 */
    else if (key > tree->key)
        find(tree->right, key);
    else
        return true;
}

/**
 * find_rightmost_key - 查找最右子树键值, 返回其上的键值, 而后删除该节点
 * @tree:   待搜索的子树	
 * @return: 最右子树的键值
 */
int find_rightmost_key(Node **tree)
{   
    int key;
    Node *temp;
    /* 右子树存在继续遍历 */
    if ((*tree)->right) 
        return find_rightmost_key(&(*tree)->right);    
    
    else {
        temp = *tree;
        key = temp->key;
        /* 该节点有一个左子树, 将左子树上提*/
        if (temp->left)  
            *tree = temp->left;
        /* 叶结点直接删除 */
        else 
            *tree = NULL;

        free_buf(temp);
        return key;
    }
}

/**
 * delete - 在二叉搜索树中删除指定节点
 * @tree:   树的地址
 * @key:	待删除的键值
 * @return: 无
 */
void delete(Node **tree, int key)
{   
    Node *temp;
    /* 没有找到 */
    if (*tree == NULL) 
        return;

    /* 在左子树上删除 */
    if (key < (*tree)->key) {
        delete(&(*tree)->left, key);
    }

    /* 在右子树上删除 */
    else if (key > (*tree)->key) {
        delete(&(*tree)->right, key);
    }

    /* 找到删除的节点 */
    else {
        /* 两个子节点都存在, 将左子树的最右子树的值上移, 后删除左子树最右节点 */
        if ((*tree)->left && (*tree)->right) {
            
            (*tree)->key = find_rightmost_key(&(*tree)->left);

        /* 两个子节点都不存在, 直接删除 */    
        } else if (!((*tree)->left || (*tree)->right)) {
            free_buf(*tree);
        /* 两个子节点存在其中之一, 将子节点上移 */
        } else {
            temp = *tree;
            /* 使用一级指针, 在在这里并不会修改原来的树, 因为 形参tree使用另外的空间保存实参传入的指针,
            这里修改的只是形参的指针, 不会影响实参的指针 */  
            if ((*tree)->left) {
                (*tree) = (*tree)->left;     
            } else {
                (*tree) = (*tree)->right;
            }
            free_buf(temp);

        }
    }
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
    /* 1. 递归退出条件 */
    if (tree) {
        pr_debug("处理 %d\n", tree->key);
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
}

/**
 * show - 显示节点键值
 * @node:   节点
 * @return: 无
 */
static inline void show(Node *node) { printf("key: %d left: %d(%d) right: %d(%d)\n", 
        node->key, node->left ? node->left->key : -1, node->lh, node->right ? node->right->key : -1, node->rh); }



/* LL型 右旋 
    /1 {parent}             2(parent)
   /2 (node)        (node)3  1
  /3
*/
void LL(Node **node)  
{   
    Node *__temp = (*node)->left;
    int _h = __temp->rh; 

    (*node)->left = __temp->right; 
    (*node)->lh = _h; 
    __temp->right = (*node); 
    __temp->rh = max((*node)->lh, (*node)->rh) + 1;  
    (*node) = __temp;
}

/* RR型 左旋
    \1 (parent)         2(parent)
     \2 (node)   (node)1  3    
      \3
 */
void RR(Node **node)
{
    Node *__temp = (*node)->right;
    int _h = __temp->lh; 

    (*node)->right = __temp->left; 
    (*node)->rh = _h; 
    __temp->left = (*node); 
    __temp->lh = max((*node)->lh, (*node)->rh) + 1;  
    (*node) = __temp;
}

/* LR型 先左旋后右旋 
        1 (parent)       1
       /                /
      2 (node)  =>     3 (node)  =>     3
       \              /                / \
        3            2                2   1
*/
void LR(Node **node)
{
    RR( &((*node)->left) );   
    LL( node );     
}  

/* RL型 先右旋后左旋 
    1 (parent)      1
     \               \
      2 (node)  =>    3(node)   =>     3
     /                 \              /  \
    3                   2            1    2
*/
void RL(Node **node)
{   
    LL( &((*node)->right) );  
    RR( node );     
} 
 

/**
 * unbalanced_direction - 获取节点的不平衡方向
 * @node:	不平衡节点
 * @return: 1 左子树高
 *          0 右子树高
 */
#define unbalanced_direction(node, left) ({    \
    bool res;   \
    if (left)   res = ((node)->lh > (node)->rh);   \
    else        res = ((node)->lh >= (node)->rh);   \
    res;\
})

/**
 * compute_height - 计算各节点的高度
 * @param:	
 * @return: 成功返回0, 失败返回-1
 */
int compute_height(Node **tree)
{
    int lh = 0;
    int rh = 0;
    int diff = 0;
    Node *_temp = NULL;
    if (*tree) {
        
        if ((*tree)->left) { 
            lh = compute_height(&((*tree)->left)) + 1;
        } 
        if ((*tree)->right) {
            rh = compute_height(&((*tree)->right)) + 1;
        }
        (*tree)->lh = lh;
        (*tree)->rh = rh;

        /* 计算左右子树高度差, 对于左右子树高度差绝对值大于 1 的节点进行平衡操作 */
        diff = lh - rh;
        pr_debug("处理: %d\n", (*tree)->key);
        pr_debug("lh: %d, rh: %d, diff: %d\n", lh, rh, diff);
        if ((diff > 0 ? diff : -1 * diff) > 1) {
            
            /* 左子树高 */
            if (diff > 0) {
                /* LL 型 */
                if (unbalanced_direction((*tree)->left, 1)) {
                    pr_debug("LL型 \n");
                    LL(tree);
                /* LR 型 */
                } else {
                    pr_debug("LR型 \n");
                    LR(tree);
                }

            /* 右子树高 */    
            } else if (diff < 0) {
                /* RL 型 */
                if (unbalanced_direction((*tree)->right, 0)) {
                    pr_debug("RL型  %d \n", (*tree)->key);
                    pr_info("调整前(tree: %p, tree->right: %p, tree->right->left: %p):", 
                        *tree, (*tree)->right, (*tree)->right->left);
                    pr_info("tree->key: %d, tree->right->key: %d, tree->right->left->key: %d\n", 
                        (*tree)->key, (*tree)->right->key, (*tree)->right->left->key);

                    RL(tree);

                    pr_info("调整后(tree: %p, tree->left: %p, tree->right: %p):", 
                        *tree, (*tree)->left, (*tree)->right);
                    pr_info("tree->key: %d, tree->left->key: %d, tree->right->key: %d\n", 
                        (*tree)->key, (*tree)->left->key, (*tree)->right->key);

                    pr_err("调整后(%d): tree->lh: %d, tree->rh: %d\n", (*tree)->key, (*tree)->lh, (*tree)->rh);
                /* RR 型 */
                } else {
                    pr_debug("RR型 \n");
                    _temp = *tree;
                    pr_info("调整前: \n");
                    pr_info("tree->key: %d, tree->left: %p, tree->right->key: %d, \ntree->right->left: %p, tree->right->right->key: %d \n", (*tree)->key, (*tree)->left, (*tree)->right->key, (*tree)->right->left, (*tree)->right->right->key);

                    RR(tree);
                    // RR(&((*tree)->right), tree);

                    pr_info("调整后: \n");
                    pr_info("tree->key: %d, tree->left->key: %d, tree->left->left: %p, tree->left->right: %p, tree->right->key: %d \n", (*tree)->key, (*tree)->left->key, (*tree)->left->left, (*tree)->left->right, (*tree)->right->key );

                }    
                // getchar();
            }

            lh = (*tree)->lh;
            rh = (*tree)->rh;
        }
    }
    return max(lh, rh);
}


const int upper = 1e5;
int main(int argc, char *argv[])
{
    SET_DEFAULT_LEVEL(CONSOLE_LOGLEVEL_FATAL);
    int i;
    Node *bs_tree = NULL;
    Node *asl_tree = NULL;


    /* 3. 插入 */
    printf("升序插入: %d\n", upper);
    for (i = 0; i < upper; ++i) {
        insert(&bs_tree, i);
        insert(&asl_tree, i);
        compute_height(&asl_tree);
        printf("%d/%d\r", i, upper);
    }
    printf("\n");

    double start = START();
    int val = upper - 1;
    printf("普通 bs_tree 搜索: %d, 结果: %s, 耗时: ", val, find(bs_tree, val) ? "yes" : "no");
    FINISH(start);
    
    start = START();
    printf("平衡 bs_tree 搜索: %d, 结果: %s, 耗时: ", val, find(asl_tree, val) ? "yes" : "no");
    FINISH(start);

    return 0;
}