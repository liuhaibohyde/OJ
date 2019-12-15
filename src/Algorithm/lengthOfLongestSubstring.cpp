/*
给定一个字符串，请你找出其中不含有重复字符的 最长子串 的长度。

示例 1:
输入: "abcabcbb"
输出: 3 
解释: 因为无重复字符的最长子串是 "abc"，所以其长度为 3。

示例 2:
输入: "bbbbb"
输出: 1
解释: 因为无重复字符的最长子串是 "b"，所以其长度为 1。

示例 3:
输入: "pwwkew"
输出: 3
解释: 因为无重复字符的最长子串是 "wke"，所以其长度为 3。
     请注意，你的答案必须是 子串 的长度，"pwke" 是一个子序列，不是子串。
*/
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_map<char, int> window;
        int left = 0;
        int right = 0;
        int res = 0;
        while (right < s.size()) {
            char r = s[right];
            window[r]++;
            right++;

            while (window[r] > 1) {
                char l = s[left];
                window[l]--;
                left++;
            }
            res = max(res, right - left);   // 要求的是最长子串，每次移动right时候都需要update结果
        }
        return res;
    }
};