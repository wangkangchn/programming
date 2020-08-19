/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: max_profit.cpp
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: 求最大利益
时间	   	: 2020-08-19 09:59
***************************************************************/
#include <iostream>
#include <algorithm>

#include "types.h"
using namespace std;

static const __u32 MAX = 1000000;

int main(int argc, char *argv[])
{
    __u32 n = 0;
    __s32 R[MAX] = {0,};

    cout << "请输入n: ";
    cin >> n;
    
    for (size_t i = 0; i < n; ++i) {
        cout << "请输入R[" << i << "]: ";
        cin >> R[i];
    }
    
    __s32 minv = R[0];
    __s32 maxv = 0;
    for (__u32 i = 1; i < n; ++i) {
        maxv = max(maxv, (R[i] - minv));
        minv = min(minv, R[i]);
    }

    cout << "max: " << maxv << endl;
    return 0;
}