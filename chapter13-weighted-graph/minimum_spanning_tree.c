/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: minimum_spanning_tree.c
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: 最小生成树
时间	   	: 2020-09-18 21:43
***************************************************************/
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include "../tools/tools.h"
#include "../tools/log.h"
#include "../tools/queue.h"

DEFINE_QUEUE_ELEMENT_TYPE(int, queue);

const int DELETED = -1;     /* V 中的顶点添加到 MST 中时, 该顶点标记为 DELETED */

/**
 * prim - 普利姆算法实现最小生成树, 每次从 V 的 T 边中选一条权值最小的, 因为每次选择的都是距 MST
 *      最小权重的边, 所以最后 MST 中包含的就是所有权最小的边  
 * @G:          图(邻接矩阵表示)	
 * @vertex_num: 顶点个数
 * @return:     最小生成树各边权值的总和
 */
int prim(int **G, int vertex_num)
{
    int i, j, k, vertex;
    int temp; 
    int weight = 0, min_weight;
    int MST[vertex_num];    /* 最小生成树顶点集合 */
    int V[vertex_num];      /* 未添加到 MST 中的顶点的集合 */

    /* 未开始时, 没有顶点添加到 MST 中 */
    for(i = 0; i < vertex_num; ++i) {
        V[i] = i;
        MST[i] = 0;
    }

    V[0] = DELETED; /* 选择顶点 0 为起点*/
    /* 每次选取一个顶点到 MST */
    for(j = 1; j < vertex_num; ++j) {
        pr_debug("第 %d 次遍历\n", j);
        min_weight = INT_MAX;

        /* 确定 MST 中的顶点与 V 中顶点的最小权 */
        for(k = 0; k < j; ++k) {
            /* 从 V 中找出邻接到当前 MST 权最小的边 */
            for(i = 0; i < vertex_num; ++i) {
                if (V[i] != DELETED) {
               
                    temp = *( ((int *)G + MST[k] * vertex_num) + V[i] );
                    pr_info("(MST)%d -> (T)%d : %d\n", MST[k], V[i], temp);
                    
                    if (temp == -1)
                        continue;

                    if (min_weight > temp) {
                        min_weight = temp;
                        vertex = i;
                    }
                }
            }
        }
        pr_warning("选择顶点: %d, 最小权: %d\n", V[vertex], min_weight);
        MST[j] = V[vertex];
        weight += min_weight;
        V[vertex] = DELETED;
    }
    return weight;
}

/* 测试:
5
-1 2 3 1 -1
2 -1 -1 4 -1
3 -1 -1 1 1
1 4 1 -1 3
-1 -1 1 3 -1

*/
const int MAX = 100;
int main(int argc, char *argv[])
{
    SET_DEFAULT_LEVEL(CONSOLE_LOGLEVEL_ERR);
    int n = 0, i, j;
    

    scanf("%d", &n);
    int G[n][n];
    memset(G, 0xff, n * n * sizeof(int));

    for (i = 0; i < n; ++i) 
        for (j = 0; j < n; ++j)  
            scanf("%d", &G[i][j]);

    // printf("获得输入: \n");
    // for (int i = 0; i < n; ++i) {
    //     for (int j = 0; j < n; ++j)
    //         printf("%d ", *(((int *)G + i * n) + j));   /* ooo 我明白了, 要先把 G 转为 int *, 不然G+1加的是整个数组的大小  */
    //     printf("\n");
    // }
    double start = START();
    
    printf("%d\n", prim((int **)G, n));

    FINISH(start);
    return 0;
}

// #include <stdio.h>
// void func(int n, char  str[ ][5] )
// void func(int n, char  （*str）[5] )
// void func(int n, char **str)
// {
//  int i;
//  for(i = 0; i < n; i++)
//   printf("/nstr[%d] = %s/n", i, str[i]);
// }
// 附加，第三种传参方式说明：在函数中使用传参过来的二维数组（指针）进行数组取值的时候不能使用（array[i][j]）这种形式来取值。应该将二维数组看成一个一维数组，使用array[i * j + j]这种形式来进行取值。

// 个人理解：这是因为在传参的时候，我们将array[][]数组当成二级指针来进行传递，所以我认为他是将数组的属性退化成了二级指针的属性，因此这里并不能使用array[i][j]这种方式来进行数组取值。输出格式如下

// int tag = 0;//tag标记，在方法中输出二维数组时所需要的标记
// printf("使用传递过来的二维数组参数输出二维数组\n");
// for(i = 0; i < rows*columns; i++) 
// {	
// 　　printf("%d,", array[i]);
// 　　if(tag == columns-1) 
// 　　{
// 　　　　tag = 0;
// 　　　　printf("\n");
// 　　} 
// 　　else 
// 　　{
// 　　　　tag++;
// 　　}
// }