/*
给你一个字符串 S、一个字符串 T，请在字符串 S 里面找出：包含 T 所有字母的最小子串。

示例：
输入: S = "ADOBECODEBANC", T = "ABC"
输出: "BANC"
说明：
如果 S 中不存这样的子串，则返回空字符串 ""。
如果 S 中存在这样的子串，我们保证它是唯一的答案。
*/
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <map>
#include <unordered_map>

using namespace std;

class Solution {
public:
    string minWindow(string s, string t) {
        if (s.empty() || t.empty() || s.size() < t.size()) {
            return "";
        }

        unordered_map<char, int> needs;
        for (auto& ch : t) {
            needs[ch]++;        // 子串每个字符的个数
        }
        
        int left = 0;
        int right = 0;
        int match = 0;
        int start = 0;
        int range = INT32_MAX;
        unordered_map<char, int> window;        // 窗口中包含的字符个数
        while (right < s.size()) {
            char r = s[right];                  // 先移动右指针   
            if (needs.find(r) != needs.end()) {
                window[r]++;
                if (window[r] == needs[r]) {    // 窗口中包含的字符和子串的字符匹配到，则match计数+1
                    match++;
                }
            }
            right++;                        

            while (needs.size() == match) {     // 窗口中包含全部子串字符了
                if ((right - left) < range) {   // 记录匹配到的窗口开始位置和长度
                    start = left;
                    range = right - left;
                }
                char l = s[left];

                if (needs.find(l) != needs.end()) {
                    window[l]--;
                    if (window[l] < needs[l]) {
                        match--;
                    }
                }
                left++;                         // 移动左指针
            }
        }
        return range == INT32_MAX ? "" : s.substr(start, range);
    }
};