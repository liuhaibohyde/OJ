/*
给定一个数组 nums ，如果 i < j 且 nums[i] > 2*nums[j] 我们就将 (i, j) 称作一个重要翻转对。
你需要返回给定数组中的重要翻转对的数量。

示例 1:
输入: [1,3,2,3,1]
输出: 2

示例 2:
输入: [2,4,3,5,1]
输出: 3
*/
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <vector>
#include <unordered_map>

using namespace std;

// 归并排序
class Solution1 {
public:
    int reversePairs(vector<int>& nums) {
        vector<int> temp(nums.size(), 0);
        return mergeSort(nums, temp, 0, nums.size() - 1);
    }

    int mergeSort(vector<int>& nums, vector<int>& temp, int l, int r) {
        if (l >= r) {
            return 0;
        }

        int mid = l + (r - l) / 2;
        int res = mergeSort(nums, temp, l, mid) + mergeSort(nums, temp, mid + 1, r);

        // 计算出当前左右子区间的结果
        int templ = l;
        int tempr = mid + 1;
        while (templ <= mid && tempr <= r) {
            if ((long)nums[templ] > 2 * (long)nums[tempr]) {
                res += mid - templ + 1;
                tempr++;
            } else {
                templ++;
            }
        }

        // 归并
        int idx = 0;
        templ = l;
        tempr = mid + 1;
        while (templ <= mid && tempr <= r) {
            if (nums[templ] <= nums[tempr]) {
                temp[idx++] = nums[templ++];
            } else {
                temp[idx++] = nums[tempr++];
            }
        }
        while (templ <= mid) {
            temp[idx++] = nums[templ++];
        }
        while (tempr <= r) {
            temp[idx++] = nums[tempr++];
        }
        for (int i = l; i <= r; i++) {
            nums[i] = temp[i - l];
        }
        return res;
    }
};

// BIT 树状数组
class Solution2 {
public:
    void update(vector<int>&bits, int idx, int val) {
        while (idx < bits.size()) {
            bits[idx] += val;
            idx += (idx & (-idx));  
        }
    }

    int query(vector<int>& bits, int idx) {
        int res = 0;
        while (idx > 0) {
            res += bits[idx];
            idx -= (idx & (-idx));
        }
        return res;
    }

    int reversePairs(vector<int>& nums) {
        int n = nums.size();
        vector<int> v = nums;

        sort(v.begin(), v.end());
        unordered_map<int, int> m;
        for (int i = 0; i < n; i++) {
            m[v[i]] = i + 1;            // 树状数组从1开始
        }

        vector<int> bits(n + 1);
        int res = 0;
        for (int i = n - 1; i >= 0; i--) {
            // 在排序后的数组v中，查找比当前nums[i]的一半还要小的值的位置；然后再在BIT中query
            res += query(bits, lower_bound(v.begin(), v.end(), nums[i] / 2.0) - v.begin());
            update(bits, m[nums[i]], 1);    // bits中存的是对应位置数字出现的次数，这样相加后才得到题目要的个数
        }
        return res;
    }
};
