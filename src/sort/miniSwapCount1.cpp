/*
只交换相邻两数，使序列升序排列，求出最少交换次数。

即求序列的逆序数(升序为例，前面的数比后面的大，那就是一个逆序，所有逆序和就是序列的逆序数)：
证明：
1、假设序列个数为n，把最大的数交换到最后，交换次数为：最大数后面的数字个数
2、最大数交换完成后，从序列中去除不再关心，序列变成n-1，再重复第一步
3、发现：每个数都需要交换其逆序数次操作
*/
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <map>
#include <unordered_map>
#include <set>
#include <string>
#include <vector>
#include <memory.h>

using namespace std;

class Solution {
public:
    int miniSwap(vector<int>& nums)
    {
        if (nums.empty() || nums.size() == 1) {
            return 0;
        }

        int ans = 0;
        for (int i = 0; i < nums.size() - 1; i++) {
            for (int j = i + 1; j < nums.size(); j++) {
                if (nums[i] > nums[j]) {
                    ans++;
                }
            }
        }

        return ans;
    }
}

