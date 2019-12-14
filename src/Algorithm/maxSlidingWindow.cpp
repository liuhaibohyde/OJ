/*
给定一个数组 nums，有一个大小为 k 的滑动窗口从数组的最左侧移动到数组的最右侧。
你只可以看到在滑动窗口内的 k 个数字。滑动窗口每次只向右移动一位。
返回滑动窗口中的最大值。

示例:
输入: nums = [1,3,-1,-3,5,3,6,7], 和 k = 3
输出: [3,3,5,5,6,7] 
解释: 
  滑动窗口的位置                最大值
---------------               -----
[1  3  -1] -3  5  3  6  7       3
 1 [3  -1  -3] 5  3  6  7       3
 1  3 [-1  -3  5] 3  6  7       5
 1  3  -1 [-3  5  3] 6  7       5
 1  3  -1  -3 [5  3  6] 7       6
 1  3  -1  -3  5 [3  6  7]      7

提示：
你可以假设 k 总是有效的，在输入数组不为空的情况下，1 ≤ k ≤ 输入数组的大小。
*/

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <deque>

using namespace std;

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> res;
        deque<int> deq; // 保存数组中窗口范围内元素的下标

        for (int i = 0; i < nums.size(); i++) {
            if (!deq.empty() && deq.front() == i - k) { // 队首元素已经超出窗口范围了，删除
                deq.pop_front();
            }

            while (!deq.empty() && nums[deq.back()] < nums[i]) {   // 循环队列，如果队尾元素没有后面的大，删除
                deq.pop_back();
            }

            deq.emplace_back(i);
            if (i >= k - 1) {   // 输出窗口内的最大值
                res.emplace_back(nums[deq.front()]);
            }
        }
        return res;
    }
};