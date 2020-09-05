/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: reconstruction_of_the_tree.c
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: 树的重建
时间	   	: 2020-09-04 10:18
***************************************************************/
#include <stdio.h>
#include <assert.h>
#include "../tools/tools.h"
#include "../tools/log.h"
#include "../tools/queue.h"

DEFINE_ELEMENT_TYPE(int, queue);

typedef struct 
{
    int parent;
    int left;
    int right;
} Node;

enum TraversalType     
{   PRE_ORDER = 0,    
    IN_ORDER = 1,  
    POST_ORDER = 2,  
};


/**
 * search - 线性搜索(带标记)
 * @A:	    待搜索数组
 * @num:    A的个数
 * @key:    欲搜索的键值
 * @return: 搜索到key返回索引, 否则返回-1
 */
int search(int A[], int left, int right, int key)
{   
    int i, num = right - left;
    A += left;
    for (i = 0; i < num; ++i) {
        if (A[i] != key)
            continue;
        break;
    }
    return i != num ? i : -1;
}

/**
 * reconstruct - 依据前序和中序遍历结果重建树
 * @tree:	    树
 * @Q:          当前前序遍历队列
 * @in_order:   中序遍历序列
 * @left:       中序遍历序列左边界(闭)
 * @right:      中序遍历序列右边界(开)
 * @return:     欲建立子树的根节点与当前中序遍历序列匹配, 当前欲建立子树的根节点的索引
 *              否则返回-1
 */
int reconstruct(Node *tree, queue *Q, int *in_order, int left, int right)
{   
    /* 递归退出条件 */
    if (is_empty(Q) || (left >= right))
        return -1;
    pr_debug("Q: %d 搜索范围 left: %d right: %d\n", front(Q), left, right);
    /* 先搜索在当前 中序遍历序列 中有没有当前 前序遍历队列 的第一个节点, 
如果有, 说明当前 前序遍历队列的第一个节点为当前 中序遍历序列 的根节点, 则从index处划分in_order,
    确定该根节点的左右子节点(这里就是递归调用了). 返回当前前序遍历队列的头结点
如果没有, 则说明当前 前序遍历队列的第一个节点不是当前 中序遍历序列 的根节点则 返回-1.*/    
    int root;
    int index = search(in_order, left, right, front(Q));
    pr_debug("index: %d\n", index);
    if (index >= 0) {
        index += left;

        root = pop(Q);
        /* 递归搜索左右子树 */
        pr_debug("搜搜 %d 左子树: left: %d right: %d\n", root, left, index);
        (tree + root)->left = reconstruct(tree, Q, in_order, left, index);
        pr_debug("搜搜 %d 右子树: left: %d right: %d\n", root, index, right);
        (tree + root)->right = reconstruct(tree, Q, in_order, index + 1, right);
        pr_info("root: %d left: %d right: %d\n", root, (tree + root)->left, (tree + root)->right);

        printf("%d ", root);    /* 左 右 根 在这里输出的就是后续, 因为建立树是要先递归到树底, 所以递归返回的顺序就是
                                使用遍历算法遍历的顺序!!! */
        return root;
    } else
        return -1;
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
    if (id == -1) 
        return;

    if (type == PRE_ORDER) 
        op(tree, id, father);
    
    traversal(tree, node->left, id, type, op);
    if (type == IN_ORDER) 
        op(tree, id, father);
    traversal(tree, node->right, id, type, op);

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

/* 测试:
5
1 2 3 4 5
3 2 4 1 5 

9
1 2 3 4 5 6 7 8 9
3 2 5 4 6 1 8 7 9*/
const int MAX = 100;
int main(int argc, char *argv[])
{
    SET_DEFAULT_LEVEL(CONSOLE_LOGLEVEL_ERR);
    int n, i;

    scanf("%d", &n);
    /* 保存前序遍历序列 */
    queue *Q = calloc_buf(1, queue);
    assert(init(Q, n));

    Node *tree = calloc_buf(n + 1, Node);
    int in_order[n];
    int pre;        /* 前序序列元素 */
    
    for (i = 0; i < n; i++) {
        scanf("%d", &pre);
        push(Q, pre);
    }

    for (i = 0; i < n; i++) 
        scanf("%d", in_order + i);

    double start = START();
    printf("后续遍历\n");
    reconstruct(tree, Q, in_order, 0, n);
    
    // traversal(tree, 0+1, -1, POST_ORDER, show);

    printf("\n");

    free_buf(tree);
    clear(Q);
    free_buf(Q);
    FINISH(start);
    return 0;
}