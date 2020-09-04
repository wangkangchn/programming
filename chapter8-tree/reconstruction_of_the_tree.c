/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: reconstruction_of_the_tree.c
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: 树的重建
时间	   	: 2020-09-04 10:18
***************************************************************/
#include <stdio.h>
#include "../tools/tools.h"
#include "../tools/log.h"

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
 * binary_search - 二分查找
 * @S:      待查找数列
 * @num:	S的大小
 * @key:    待查找的键
 * @return: 成功返回0, 失败返回-1
 */
int binary_search(int *S, int num, int key)
{   
    /* 递归结束条件 */
    if (num != 0) {
        int middle = num / 2;

        if (S[middle] == key) 
            return 1;     
        /* 右侧递归搜索 */
        else if (S[middle] < key) 
            return binary_search(S + middle + 1, num - middle, key);
        /* 左侧递归搜索 */
        else 
            return binary_search(S, middle, key);      
    } else 
        return 0;
}

/* binary_search(S, n, key);  */
/**
 * reconstruct - 依据前序和中序遍历结果重建树
 * @in:	
 * @left:   左闭
 * @right:  右开
 * @return: 成功返回0, 失败返回-1
 */
void reconstruct(Node *tree, int *pre, int id, int n, int *in, int left, int right)
{   
    int index;
    /* 递归结束条件 */
    if (left < right || id < n) {
        /* 根节点 */
        if (id == 0)
            (tree + id)->parent = -1;
        else {
            if (tree[tree[id].parent].left == 0)
                tree[tree[id].parent].left = id;
            else
                tree[tree[id].parent].right = id;
        }
        
        /* 在中序结果中搜索 id */
        index = binary_search(in + left, right - left, id);

        reconstruct(tree, pre, id + 1, n,  in, left, index);
        reconstruct(tree, pre, id + 1, n,  in, index + 1, right);
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
void traversal(Node *tree, int id, int father, enum TraversalType type, void (*op)(Node *, int, int))
{
    Node *node = tree + id;

    /* 1. 递归退出条件 */
    if (id == 0) 
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