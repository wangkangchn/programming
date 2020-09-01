/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: koch_curve.c
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: 科赫曲线
时间	   	: 2020-09-01 08:49
***************************************************************/
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>
#include "../tools/tools.h"
#include "../tools/queue.h"

typedef struct {
    double x;
    double y;
} point;


/* 点集操作 */
#undef add
#define add(p1, p2) ({  \
    point __p1 = (p1);   \
    point __p2 = (p2);   \
    point __p;           \
    __p.x = p1.x + p2.x;        \
    __p.y = p1.y + p2.y;        \
    __p; })

#undef neg
#define neg(p) ({ p.x = -p.x; p.y = -p.y })

#undef sub  /* p1 - p2 = p1 + (-p2) */
#define sub(p1, p2) ({ add(p1, neg(p2)); })

#undef div
#define div(p, val) ({  \
    point __p = (p);   \
    double __val = (double)val;   \
    __p.x /= __val;        \
    __p.y /= __val;        \
    __p; })

#undef mul
#define mul(p, val) ({  \
    point __p = (p);   \
    double __val = (double)val;   \
    __p.x *= __val;        \
    __p.y *= __val;        \
    __p; })

/* 队列保存结果 */
DEFINE_ELEMENT_TYPE(point, queue);
queue *Q;

const double PI = 3.1415926535898;

/**
 * compute_third_pt - 已知正三角形的两点求第三点(极坐标与直角坐标进行转换)
 * @p1:     左端点
 * @p2:     右端点	
 * @return: 第三点
 */
point compute_third_pt(point p1, point p2)
{
    /* p1 - p2 线段相对于 x 轴的倾角(弧度) 以及 长度 */
    double alpha = atan((p2.y - p1.y) / (p2.x - p1.x));
    double l = sqrt((p2.y - p1.y) * (p2.y - p1.y) + (p2.x - p1.x) * (p2.x - p1.x));
    point p = {
        .x = p1.x + l * cos(alpha + PI / 3),
        .y = p1.y + l * sin(alpha + PI / 3),
    };
    return p;
}

/**
 * compute_third_pt_rotation_matrix - 利用旋转矩阵求解第三个点, 第三个点的方式是一定的, 即将p1 - p2线段
 * 逆时针选择60° 使用的是坐标形式 p = p1坐标 - p2坐标
 *                      [cosθ -sinθ]
 *     旋转结果 = p  @  [           ] 
 *                      [sinθ cosθ ]
 * 
 * @p1:     左端点
 * @p2:     右端点	
 * @return: 第三点
 */
point compute_third_pt_rotation_matrix(point p1, point p2)
{
    /* p1 - p2 线段相对于 x 轴的倾角(弧度) 以及 长度 */
    double x = p2.x - p1.x;
    double y = p2.y - p1.y;
    point p = {
        .x = x * cos(PI / 3) - y * sin(PI / 3) + p1.x,
        .y = x * sin(PI / 3) - y * cos(PI / 3) + p1.y,
    };
    return p;
}

/**
 * koch_curve - 由左到右按顺序输出科赫曲线的各顶点(深度为n) 
 * @p1:     左端点
 * @p2:     右端点	
 * @n:      递归深度
 * @return: 成功返回0, 失败返回-1
 */
void koch_curve(point p1, point p2, int n)
{   
    static unsigned int count = 0;
    if (count++ >= n) return;

    /* 三等分点 */
    point temp = div(add(p2, p1), 3);
    
    point s = add(p1, temp);
    point t = add(s, temp);
 
    /* 计算第三点  */
    point u = compute_third_pt(s, t);
    
    printf("%.10f %.10f\n", p1.x, p1.y);   
    printf("%.10f %.10f\n", s.x, s.y);   
    printf("%.10f %.10f\n", u.x, u.y);   
    printf("%.10f %.10f\n", t.x, t.y);  
    printf("%.10f %.10f\n", p2.x, p2.y);  

    /* 保存顶点 */
    push(Q, s); push(Q, u); push(Q, t);

    koch_curve(p1, s, n);
    koch_curve(s, u, n);
    koch_curve(u, t, n);
    koch_curve(t, p2, n);
}

int compare(const void *arg1, const void *arg2)
{
    point p1 = *(point *)(arg1);
    point p2 = *(point *)(arg2);
    if (p1.x < p2.x)
        return -1;
    else if (p1.x == p2.x)
        return 0;
    else
        return 1;
}

const int MAX = 100;

int main(int argc, char *argv[])
{
    int n = 0, i, count = 0;
    Q = calloc(1, sizeof(queue));
	assert(init(Q, MAX));

    scanf("%d", &n);
    point p1 = { .0, .0 };
    point p2 = { 100.0, 0.0 };
    
    push(Q, p1); push(Q, p2);
    
    koch_curve(p1, p2, n);

    qsort(Q->data, size(Q), sizeof(point), compare);

    // for (size_t i = 0; i < size(Q); ++i) 
    //     printf("%f %f\n", Q->data[i].x, Q->data[i].y);         
    clear(Q);
    return 0;
}
