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
#include "../tools/bstree.h"

DEFINE_BSTREE_ELEMENT_TYPE(double, bstree_node, bstree);

// int compare(const void *arg1, const void *arg2)
// {
//     int ret = 0;
//     int __arg1 = *(int *)arg1;
//     int __arg2 = *(int *)arg2;

//     if (__arg1 < __arg2) ret = -1;
//     else if (__arg1 > __arg2) ret = 1;

//     return ret;
// }
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
    double _key;
    char cmd[20];
    
    bstree tree = {
        .root = NULL,
        .__compare = compare,
    };
    // bstree_node *tree = NULL;

    scanf("%d", &n);

    for (i = 0; i < n; ++i) {
        scanf("%s", cmd);
        switch (cmd[0])
        {
        case 'i':
            scanf("%d", &key);
            _key = (double)key;
            insert(&tree, &_key);
            break;
        
        case 'f':
            scanf("%d", &key);
            _key = (double)key;
            printf("%s\n", find(&tree, &_key) ? "yes" : "no");
            break;

        case 'd':
            scanf("%d", &key);
            _key = (double)key;
            delete(&tree, &_key);
            break;
        
        case 'p':
            traversal(tree.root, IN_ORDER, show);
            printf("\n");
            traversal(tree.root, PRE_ORDER, show);
            printf("\n");
            break;

        default:
            break;
        }
    }

    return 0;
}