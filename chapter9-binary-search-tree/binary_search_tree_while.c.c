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
#include "../tools/tools.h"
#include "../tools/log.h"
#include "../tools/list.h"

typedef int (*__compare_fn)(const void *, const void *);

int compare(const void *arg1, const void *arg2)
{
    int ret = 0;
    int __arg1 = *(int *)arg1;
    int __arg2 = *(int *)arg2;

    if (__arg1 < __arg2) ret = -1;
    else if (__arg1 > __arg2) ret = 1;

    return ret;
}

enum TraversalType     
{   PRE_ORDER = 0,    
    IN_ORDER = 1,  
    POST_ORDER = 2,  
};

typedef struct Node {
    struct Node *left;
    struct Node *right;

    int *data;
} bstree_node;

typedef struct bstree {
    bstree_node *root;
    __compare_fn __compare;
} bstree;

/**
 * calloc_node - 分配节点空间, 插入键值
 * @val:	待插入键值
 * @return: 新分配的节点指针
 */
#define calloc_node(val)    ({              \
    bstree_node *__node =  calloc_buf(1, bstree_node);    \
    __node->data = calloc_buf(1, typeof( *__node->data ) ); \
    *__node->data = *(val);                      \
    __node;                                 \
})

/**
 * insert - 向二叉搜索树插入键值
 * @tree:   树(二级指针, 数指针的地址)
 * @key:    待插入键值	
 */
#define insert(tree, val)   ({  \
    typeof( (tree)->root ) *node = &( (tree)->root ); \
    typeof( (tree)->root ) __temp = calloc_node( (val) );   \
    while (*node != NULL)           \
        if ( (tree)->__compare( __temp->data, (*node)->data ) <= 0 ) node = &(*node)->left; \
        else node = &(*node)->right;                    \
    (*node) = __temp;                         \
})

/**
 * find - 在二叉搜索树中搜索指定的键值
 * @tree:   树
 * @key:	待搜索的键值
 * @return: 找到成功返回true, 失败返回false
 */
#define find(tree, val)     ({          \
    bool __result = false;              \
    typeof( (tree)->root ) __node = (tree)->root; \
    while (true)    {                   \
        if (__node == NULL)     break;  \
        if      ( (tree)->__compare( (val), __node->data ) < 0 )     __node = __node->left;  \
        else if ( (tree)->__compare( (val), __node->data ) > 0 )     __node = __node->right; \
        else {  __result = true;    break;  }               \
    }           \
    __result;   \
})


/**
 * find_rightmost_key - 查找最右子树键值, 返回其上的键值, 而后删除该节点
 * @tree:   待搜索的子树	
 * @return: 最右子树的键值
 */
#define find_rightmost_key(tree)    ({  \
    int *__key;  \
    typeof( (tree) ) __node_ = tree; \
    typeof( *(tree) ) __temp;       \
\
    while (true)    {   \
        if ((*__node_)->right) __node_ = &(*__node_)->right;   \
        else {  \
            __temp = *__node_;   \
            __key = __temp->data;\
            if (__temp->left)   *__node_ = __temp->left;  \
            else                *__node_ = NULL;         \
            free_buf(__temp);   \
            break;              \
        }   \
    }   \
    *__key;  \
})


/**
 * delete - 在二叉搜索树中删除指定节点
 * @tree:   树的地址
 * @key:	待删除的键值
 * @return: 无
 */
#define delete(tree, val)   ({  \
    typeof( (tree)->root ) *__node = &( (tree)->root ); \
    typeof( *__node )   __temp;         \
\
    while ((*__node) != NULL)  {           \
        if      ( (tree)->__compare( (val), (*__node)->data ) < 0 )     (__node) = &(*__node)->left;  \
        else if ( (tree)->__compare( (val), (*__node)->data ) > 0 )     (__node) = &(*__node)->right; \
        else {  \
\
            if ((*__node)->left && (*__node)->right)            *(*__node)->data = find_rightmost_key(&(*__node)->left);  \
            else if (!((*__node)->left || (*__node)->right))    free_buf(*__node);                                      \
            else {  \
                __temp = *__node;   \
                if ((*__node)->left)    (*__node) = (*__node)->left;        \
                else                    (*__node) = (*__node)->right;       \
                free_buf(__temp);   \
            }   \
        }   \
    }   \
})

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
static inline void show(bstree_node *node) { printf("%d ", *node->data); }

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
            insert(&tree, &key);
            break;
        
        case 'f':
            scanf("%d", &key);
            printf("%s\n", find(&tree, &key) ? "yes" : "no");
            break;

        case 'd':
            scanf("%d", &key);
            delete(&tree, &key);
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

    // double start = START();
    
    // FINISH(start);
    return 0;
}