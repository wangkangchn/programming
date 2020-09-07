/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: binary_search_tree.c
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: 二叉搜索树(插入, 查找, 删除)
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
    /* 来到所需的叶节点, 插入 */
    if (*tree == NULL) {
        *tree = calloc_node(key);
        // (*tree)->parent = parent;
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
            insert(&tree, key);
            break;
        
        case 'f':
            scanf("%d", &key);
            printf("%s\n", find(tree, key) ? "yes" : "no");
            break;

        case 'd':
            scanf("%d", &key);
            delete(&tree, key);
            break;
        
        case 'p':
            traversal(tree, IN_ORDER, show);
            printf("\n");
            traversal(tree, PRE_ORDER, show);
            printf("\n");
            break;

        default:
            break;
        }
    }

    // double start = START();
    
    // FINISH(start);
    return 0;
}