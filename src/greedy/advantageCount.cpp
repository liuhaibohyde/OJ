/*
给定两个大小相等的数组 A 和 B，返回 A 的任意排列，使 A[i] > B[i] 的索引 i 的数目最多。

贪心：
对于位置索引i，取A中能大于B[i]的最小的数，如果A中没有大于的，则拿整个A中最小的数填入结果
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
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> advantageCount(vector<int>& A, vector<int>& B) {
        multiset<int> s(A.begin(), A.end());    // set自动排好序了

        for (int i = 0; i < A.size(); i++) {
            auto it = s.upper_bound(B[i]);      // 找到第一个大于B[i]的

            if (it == s.end()) {
                A[i] = *s.begin();
                it = s.begin();                 // 后面需要删除该元素
            } else {
                A[i] = *it;
            }
            
            s.erase(it);
        }
        return A;
    }
};

// 把B也排序，并记录位置映射关系，双指针速度更快
class Solution {
public:
    vector<int> advantageCount(vector<int>& A, vector<int>& B) {
        sort(A.begin(), A.end());

        vector<pair<int,int>> bp;
        for(int i = 0; i < B.size(); i++){         
            bp.push_back(make_pair(B[i], i));
        }
        sort(bp.begin(), bp.end());                 // 对B排序，并记录排序后的位置映射关系

        int i = 0;
        int j = bp.size() - 1;                      // j初始指向B中最大值
        int cur = 0;
        vector<int> res(A.size(), 0);
        while (i <= j) {
            if(A[cur] > bp[i].first) {              // bp[i].first 即B排序后第i个位置的元素的值
                res[bp[i].second] = A[cur];         // 直接给结果数组中的对应位置赋值, A[cur]即为当前A中最小值
                i++;
            } else{
                res[bp[j].second] = A[cur];         // 对应位置的值不大于B，则把A[cur]赋给B中最大值所在的位置
                j--;
            }
            cur++;
        }
        return res;
    }
};
