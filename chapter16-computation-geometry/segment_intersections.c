/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: segment_intersections.c
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: 线段相交问题
时间	   	: 2020-10-26 20:34
***************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "../tools/tools.h"
#include "../tools/log.h"
#include "../tools/geometry.h"
#include "../tools/bstree.h"

DEFINE_BSTREE_ELEMENT_TYPE(double, bstree_node, bstree);

/* 线段端点 */
typedef struct {
    Point end;              /* 线段端点 */
    Point other_end;        /* 线段的另一个端点 */
} Segment_End;

typedef enum {
    HORIZONTAL_LEFT,
    HORIZONTAL_RIGHT,
    VERTICAL_TOP,
    VERTICAL_BOTTOM,
} End_t;

/**
 * get_end_type - 获取端点的类型
 * @end:	端点
 * @return: 类型
 */
static inline End_t get_end_type(Segment_End e)
{   
    End_t type;

    /* x 相同该线段为纵向 */
    if (equals(e.end.x, e.other_end.x)) {
        type = vless(e.end, e.other_end) ? VERTICAL_BOTTOM : VERTICAL_TOP;
    
    /* y 相同线段为横向 */
    } else if (equals(e.end.y, e.other_end.y)) {
        type = vless(e.end, e.other_end) ? HORIZONTAL_LEFT : HORIZONTAL_RIGHT;
    } else {
        pr_err("点 (%lf, %lf) 所在的线段与轴不平行\n", e.end.x, e.end.y);
        exit(0);
    }

    return type;
}


/* 函数指针, 用于比较优先级队列元素, 其返回值必须满足
    arg1 < arg2时， 返回值 < 0;
    arg1 == arg2时，返回值 = 0;
    arg1 > arg2时， 返回值 > 0. */
int compare(const void *arg1, const void *arg2)
{
    int ret = 0;
    Point __arg1 = *(Point *)arg1;
    Point __arg2 = *(Point *)arg2;

    if (!vequals(__arg1, __arg2)) {
        if (__arg1.y < __arg2.y)
            ret = -1;
        else if (__arg1.y > __arg2.y)   
            ret = 1;
        else {
            if (__arg1.x < __arg2.x)
                ret = -1;
            else if (__arg1.x > __arg2.x)   
                ret = 1;
        }
    }

    return ret;
}


/* 2. 定义树节点间的大小关系
    arg1 == arg2:   0
    arg1 < arg2:    -1
    arg1 > arg2:    1
    */
int compare_bstree(const void *arg1, const void *arg2)
{
    double __arg1 = *(double *)arg1;
    double __arg2 = *(double *)arg2;

    if (equals(__arg1, __arg2))   return 0;
    else if (__arg1 < __arg2)           return -1;
    else                                return 1;
}


#define free_node(node) ({  \
    if ((node)) {   \
        free_buf((node)->data); \
        free_buf((node));       \
    }   \
})

/**
 * clear_up_tree_node - 清空树节点
 * @tree:	待删除的树
 * @return: 无
 */
void clear_up_tree_node(bstree_node *tree)
{   
    if (tree) {
        /* 从左子树退出时清空左子树 */
        clear_up_tree_node(tree->left);
        free_node(tree->left);

        /* 从右子树退出时清空右子树和根 */
        clear_up_tree_node(tree->right);
        free_node(tree->right);
    }
}

/**
 * clear_up_tree - 清空树
 * @tree:	待删除的树
 * @return: 无
 */
void clear_up_tree(bstree *tree)
{   
    clear_up_tree_node(tree->root);
    free_buf(tree->root->data);
    free_buf(tree->root);
}

/**
 * search - 在二叉树中搜索是否存在指定范围内的值
 * @tree:   二叉树	
 * @lower:  下界	
 * @upper:  上界	
 * @buf:    保存搜索到的值	
 * @buf_size:    buf 大小	
 * @return:     指定范围内存在的点数
 */
int search(bstree_node *tree, double lower, double upper, double *buf, size_t buf_size)
{
    int num = 0;
    double *key = NULL;
    int res_lower = 0;
    int res_upper = 0;
    if (tree) {
        key = tree->data;

        res_lower = compare_bstree(key, &lower);
        res_upper = compare_bstree(key, &upper);
        
        /* 节点位于范围中间 */
        if (res_lower >= 0 && res_upper <= 0) {
            buf[num++] = *key;
            /* 先在左子树上搜, 后到右子树上搜 */
            num += search(tree->left, lower, upper, buf+num, buf_size-num);
            num += search(tree->right, lower, upper, buf+num, buf_size-num);
        
        /* 比上界还大, 在左子树搜 */
        } else if (res_upper > 0) {
            num += search(tree->left, lower, upper, buf+num, buf_size-num);
        
        /* 比下界还小, 在右子树上搜 */
        } else if (res_lower < 0) {
            num += search(tree->right, lower, upper, buf+num, buf_size-num);
        }
    }

    return num;
}

/**
 * segment_intersections - 线段交点
 * @ends:	线段的端点集
 * @count:	端点集的大小
 * @return: 交点的个数
 */
int segment_intersections(Segment_End *ends, size_t ends_size)
{   
    int i = 0, j = 0;
    /* 1. 将端点值按 y 升序排序 */
    Segment_End *_ends = calloc_buf(ends_size, Segment_End);
    memcpy(_ends, ends, ends_size * sizeof(Segment_End));
    qsort(_ends, ends_size, sizeof(Segment_End), compare);

    /* 2. 由下向上进行扫描 */
    Segment_End end;
    memset(&end, 0, sizeof(Segment_End));
    bstree tree = {
        .root = NULL,
        .__compare = compare_bstree,
    };

    int num = 0;
    int count = 0;
    int buf_size = 0x400;
    double *buf = NULL;
    buf = calloc_buf(buf_size, double);
    memset(buf, 0, buf_size * sizeof(typeof(*buf)));

    for (i; i < ends_size; ++i) {
        end = _ends[i];
        /*  若 end 为垂直线段的下端点, 则加入二叉树;
            若 end 为垂直线段的上端点(因为排序的时候是下端点在前, 所以遇到上端点就说明这条线段已经
        处理完毕了), 则从二叉树中删除另一个端点; 
            若 end 为水平线段的左端点(扫描线与线段平行), 则在该线段的范围内搜索二叉树, 若在该范围
        内搜到了端点, 就说明之前的垂线与该水平线相交了, 因为水平线还没有出垂直线的范围;
            若 end 为水平线的右端点, 水平线结束, 丢弃.            
        */

        switch (get_end_type(end))
        {
        case HORIZONTAL_LEFT:
            num = search(tree.root, end.end.x, end.other_end.x, buf, buf_size);
            if (num) {
                count += num;
                for (j = 0; j < num; ++j) {
                    printf("范围 (%lf %lf) 交点 x 坐标为: %lf\n", end.end.x, end.other_end.x, buf[j]); 
                }  
                num = 0;
                memset(buf, 0, num * sizeof(typeof(*buf)));
            }
            break;
        
        case VERTICAL_TOP:
            delete(&tree, &end.other_end.x);
            break;
        
        case VERTICAL_BOTTOM:
            insert(&tree, &end.end.x);
            break;
        
        default:
            break;
        }
    }

    /* 释放二叉树占用的空间 */
    clear_up_tree(&tree);

    return count;
}

/* 测试:
7
2 2 2 5
1 3 5 3
4 1 4 4
5 2 7 2
6 1 6 3
6 5 6 7
3 1 3 4

 */
const int MAX = 100;
int main(int argc, char *argv[])
{
    // SET_DEFAULT_LEVEL(CONSOLE_LOGLEVEL_INFO);
    int n = 0, i = 0;
    int count = 0;

    scanf("%d", &n);
    Segment *segs = calloc_buf(n, Segment);     /* 线段集 */
    Segment_End *ends = calloc_buf(n, Segment_End);         /* 端点集 */

    for (i = 0; i < n; ++i) {
        scanf("%lf %lf %lf %lf", &segs[i].p1.x, &segs[i].p1.y, &segs[i].p2.x, &segs[i].p2.y);
        ends[i].end = segs[i].p1;
        ends[i].other_end = segs[i].p2;
        ends[i + 1].end = segs[i].p2;
        ends[i + 1].other_end = segs[i].p1;
    }
    double start = START();
    
    count = segment_intersections(ends, n * 2);
    printf("%d\n", count);
    FINISH(start);
    return 0;
}