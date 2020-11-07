/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: largest_square.c
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: 最大正方形
时间	   	: 2020-11-07 08:43
***************************************************************/
#include <stdio.h>
#include <string.h>
#include "../tools/tools.h"
#include "../tools/log.h"

#define index(G, i, j, w)  ({ *( ((int *)(G) + (i) * (w))  + (j)); })

// /**
//  * largest_square - 求没有被污染的最大正方形面积
//  * @G:      待搜索图	
//  * @H:      图高
//  * @W:      图宽	
//  * @return: 最大正方形面积
//  */
// int largest_square(int **G, size_t H, size_t W)
// {
//     int area = 0, max_area = 0;
//     int i = 0, j = 0, k = 0;
//     int min_row = 0, min_col = 0;
//     int row_upper = 0, col_upper = 0;
//     int row = 0, col = 0;
    
//     for (i = 0; i < H; ++i) {
//         for (j = 0; j < W;) {
//             if (index(G, i, j, W)) {      
//                 ++j;
//                 continue;
//             }
//             k = 1;  /* 对角线 */
//             while (1) {
//                 row_upper = i + k;  /* 最下界(闭) */
//                 col_upper = j + k;  /* 最右界(闭) */
//                 /* (i, j) 的对顶点为 (row_upper, col_upper) */
//                 if (index(G, row_upper, col_upper, W) == 0) {
//                     /* 判断对顶点所在的行列是否均为干净瓷砖, 先行后列 */
//                     for (col = j; col < col_upper; ++col) {
//                         if (index(G, row_upper, col, W) == 1) {
//                             min_col = col;
//                             break;                            
//                         }         
//                     }
//                     for (row = i; row < row_upper; ++row) {
//                         if (index(G, row, col_upper, W) == 1) {
//                             min_row = row;
//                             break;                            
//                         }       
//                     }

//                     if (min_col == 0 && min_row == 0) {
//                         area = (k - i + 1) * (k - i + 1);
//                         max_area = max_area < area ? area : max_area;
//                     } else {
//                         j = min_col + 1;
//                         break;
//                     }

//                 } else {
//                     ++j;    /* 对顶点是障碍, 从障碍后一个继续检测 */
//                     break;
//                 }
//             } 
//         }
//     }
//     return max_area;
// }

/**
 * get_largest_square - 
 * @G:      待搜索图	
 * @H:      图高
 * @W:      图宽	
 * @return: 最大正方形面积
 */
int get_largest_square(int **G, size_t H, size_t W)
{
    int dp[H][W];
    int i = 0, j = 0;
    int max_w = 0;

    for (i = 0; i < H; ++i) {
        for (j = 0; j < W; ++j) {
            dp[i][j] = (*( ((int *)(G) + (i) * (W))  + (j)) + 1) % 2;
            max_w |= dp[i][j];
        }
    }

    for (i = 0; i < H; ++i) {
        for (j = 0; j < W; ++j) {
            if (*( ((int *)(G) + (i) * (W))  + (j))) {
                dp[i][j] = 0;
            } else {
                dp[i][j] = min(dp[i - 1][j - 1], min(dp[i - 1][j], dp[i][j - 1])) + 1;
                max_w = max(max_w, dp[i][j]);
            }
        }
    }
    
    return max_w * max_w;
}

/* 测试:
4 5
0 0 1 0 0
1 0 0 0 0 
0 0 0 1 0
0 0 0 1 0 

*/
const int MAX = 100;
int main(int argc, char *argv[])
{
    // SET_DEFAULT_LEVEL(CONSOLE_LOGLEVEL_INFO);
    int H, W;
    int A[MAX];
    int i = 0, j = 0;

    scanf("%d %d", &W, &H);
    int G[W][H];

    for (i = 0; i < H; ++i) 
        for (j = 0; j < W; ++j) 
            scanf("%d", &G[i][j]); 

    double start = START();
    printf("%d\n", get_largest_square((int **)G, H, W));
    FINISH(start);
    return 0;
}