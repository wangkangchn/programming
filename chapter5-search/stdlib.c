/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: stdlib.c
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: 标准库中的工具函数
时间	   	: 2020-08-30 10:45
***************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <assert.h>

#include "../tools/tools.h"
/* 打印结果 */
void print_result(FILE *fp)
{
    char buf[100];

    if (fp) {
        
        printf("\n>>>\n");
        while(memset(buf, 0, sizeof(buf)), fgets(buf, sizeof(buf) - 1, fp) != 0 ) {
                printf("%s", buf);
        }
        printf("\n<<<\n");
    }
}

int compare(const void *, const void *);

int main(int argc, char *argv[])
{
    /* strtod: 将字符串转换为 double 浮点类型 */
    char *start = "1.123151d ha ha w";
    char *end;
    printf("%s: %f\n", start, strtod(start, &end));
    printf("剩余字符串为: %s\n", end);
    printf("%zd\n", sizeof(long double));
    printf("%zd\n", sizeof(long long int));
    
    int dec, sign;
    printf("浮点转字符串: %s\n", fcvt(123.41531, 6, &dec, &sign));
    printf("小数点位置: %d, 符号为: %d\n", dec, sign);
    printf("浮点转字符串: %s\n", ecvt(123.41531, 6, &dec, &sign));
    printf("小数点位置: %d, 符号为: %d\n", dec, sign);

    char str[20];
    printf("gcvt: %s\n", gcvt(123.456, 5,str));

    printf("执行命令行: %d\n", system("sudo touch 123.txt & echo 1 > 123.txt"));
    
    FILE *fp = NULL;
    fp = popen("rm 123.txt & touch wkangk.txt & echo I like qiqi. > wkangk.txt", "r");
    assert(fp);
    // fp = popen("./wkangk.sh", "r");
    if (fp) {
        print_result(fp);
        printf("命令返回值: %d\n", pclose(fp));
    } else {
        perror("popen");
        exit(EXIT_FAILURE);
    }
    
    int arr[] = {1,2,311,24,53, 0,12,32, 3};
    int key = 2;
    qsort(arr, ARRAY_SIZE(arr), sizeof(int), compare);
    for (size_t i = 0; i < ARRAY_SIZE(arr); ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    int *index = bsearch(&key, arr, ARRAY_SIZE(arr), sizeof(int), compare);
    printf("2: %p, index: %p\n", arr+1, index);
    
    div_t my_div = div(5, 2);
    printf("5 / 2 quot: %d rem: %d\n", my_div.quot, my_div.rem);
    return 0;
}

int compare(const void *arg1, const void *arg2)
{
    int key = *(int *)(arg1);
    int item = *(int *)(arg2);
    if (key < item)
        return -1;
    else if (key == item)
        return 0;
    else
        return 1;
}