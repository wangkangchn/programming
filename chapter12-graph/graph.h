/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: graph.h
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: 图
时间	   	: 2020-09-16 08:39
***************************************************************/
#ifndef __GRAPH_h__ 
#define __GRAPH_h__ 

#include "../tools/list.h"

typedef struct Vertex {
    int id;
    int d;  /* 该顶点的发现时刻 */
    int f;  /* 该顶点的结束时刻*/
    struct list_head list;
} Vertex;

/* 邻接表顶点 */
typedef struct adj_node {
    int id;
    struct list_head list;
} adj_node;


#endif	// __GRAPH_h__