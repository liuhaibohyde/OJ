/*
给定一个字符串 s 和一个非空字符串 p，找到 s 中所有是 p 的字母异位词的子串，返回这些子串的起始索引。
字符串只包含小写英文字母，并且字符串 s 和 p 的长度都不超过 20100。

说明：
字母异位词指字母相同，但排列不同的字符串。
不考虑答案输出的顺序。

示例 1:
输入:
s: "cbaebabacd" p: "abc"
输出:
[0, 6]

解释:
起始索引等于 0 的子串是 "cba", 它是 "abc" 的字母异位词。
起始索引等于 6 的子串是 "bac", 它是 "abc" 的字母异位词。

示例 2:
输入:
s: "abab" p: "ab"
输出:
[0, 1, 2]

解释:
起始索引等于 0 的子串是 "ab", 它是 "ab" 的字母异位词。
起始索引等于 1 的子串是 "ba", 它是 "ab" 的字母异位词。
起始索引等于 2 的子串是 "ab", 它是 "ab" 的字母异位词。
*/
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <unordered_map>    

using namespace std;

class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        if (s.empty() || p.empty() || s.size() < p.size()) {
            return {};
        }

        unordered_map<char, int> needs;
        for (auto& ch : p) {
            needs[ch]++;
        }
        unordered_map<char, int> window;
        int left = 0;
        int right = 0;
        int match = 0;
        vector<int> res;
        while (right < s.size()) {
            char r = s[right];
            if (needs.find(r) != needs.end()) {
                window[r]++;
                if (window[r] == needs[r]) {
                    match++;
                }
            }
            right++;

            while (match == needs.size()) {         // 长度匹配，把left加入到结果中
                if (right - left == p.size()) {
                    res.emplace_back(left);
                }
                char l = s[left];
                if (needs.find(l) != needs.end()) {
                    window[l]--;
                    if (window[l] < needs[l]) {
                        match--;
                    }
                }
                left++;
            }
        }
        return res;
    }
};