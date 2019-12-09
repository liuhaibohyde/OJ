/*
给定两个单词（beginWord 和 endWord）和一个字典 wordList，找出所有从 beginWord 到 endWord 的最短转换序列。转换需遵循如下规则：
每次转换只能改变一个字母。
转换过程中的中间单词必须是字典中的单词。
说明:

如果不存在这样的转换序列，返回一个空列表。
所有单词具有相同的长度。
所有单词只由小写字母组成。
字典中不存在重复的单词。
你可以假设 beginWord 和 endWord 是非空的，且二者不相同。

示例 1:
输入:
beginWord = "hit",
endWord = "cog",
wordList = ["hot","dot","dog","lot","log","cog"]
输出:
[
  ["hit","hot","dot","dog","cog"],
  ["hit","hot","lot","log","cog"]
]

示例 2:
输入:
beginWord = "hit"
endWord = "cog"
wordList = ["hot","dot","dog","lot","log"]
输出: []
解释: endWord "cog" 不在字典中，所以不存在符合要求的转换序列。
*/

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <iostream>
#include <algorithm>

using namespace std;

// BFS + DFS
class Solution {
public:
    vector<vector<string>> res;
    unordered_map<string, vector<string>> trace;                    // 记录单词变化路径,逆向(key-变化后单词)

    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList)
    {
        unordered_set<string> dict(wordList.begin(), wordList.end());
        if (dict.find(endWord) == dict.end()) {                     // 字典中没有endqord，直接返回空
            return res;
        }

        unordered_set<string> q{beginWord};                         // q：当前需要遍历的集合
        while (q.size() && trace.find(endWord) == trace.end()) {    // 如果trace中有endWord,表示最短路径已经产生
            for (auto& word : q) {                                  // 已经在待访问集合q中的单词，从dict中删除
                dict.erase(word);
            }

            unordered_set<string> tmp;                              // 必须要用set，防止“菱形”变换导致重复单词
            for (auto& word : q) {                                  // 遍历q中待访问的单词
                for (int i = 0; i < word.length(); ++i) {           // 每个单词从a~z替换一遍，看是否存在字典中
                    string s = word;
                    for (char ch = 'a'; ch <= 'z'; ++ch) {
                        if (s[i] == ch) {
                            continue;
                        }

                        s[i] = ch;                                  // 替换一个字母
                        if (dict.find(s) == dict.end()) {           // 字典中没有这个单词，跳过
                            continue;
                        }

                        trace[s].emplace_back(word);                // 保存字典中这个单词的前驱（即当前遍历单词）
                        tmp.insert(s);                              // 作为下一轮BFS遍历的单词，同时下一轮从字典中删除
                        if (s == endWord) {
                            cout << word << endl;
                        }
                    }
                }
            }
            q = tmp;                                                // 下一轮待遍历的单词赋值给q
        }

        if (trace.find(endWord) == trace.end()) {                   // trace中没有endWord，返回
            return res;
        }

        vector<string> path;
        dfs(path, beginWord, endWord);
        cout << "trace: " << endl;
        return res;
    }

    // 这里没有像双向BFS那样传path引用，因为找到路径后还需要翻转，实测执行速度没有传值快
    void dfs(vector<string> path, const string& begin, const string& end)
    {
        path.emplace_back(end);                 // trace中的路径逆向
        if (end == begin) {
            reverse(path.begin(), path.end());  // 逆序
            res.emplace_back(path);             // 找到最短序列，存入结果中
            return;
        }

        for (auto word : trace[end]) {
            dfs(path, begin, word);
        }
    }
};

// 双向BFS
class Solution {
public:
    vector<vector<string>> res;
    unordered_map<string, vector<string>> trace;            // 记录单词变化路径,正向(key-变化前单词)

    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList)
    {
        unordered_set<string> dict(wordList.begin(), wordList.end());
        if (dict.find(endWord) == dict.end()) {
            return res;
        }

        unordered_set<string> beginq{beginWord};            // 双向BFS，保存下一轮待访问单词是集合
        unordered_set<string> endq{endWord};
        bool found = false, flip = false;                   // found-是否找到最短序列标志, flip-是否反转标志
        while (!beginq.empty()) {
            unordered_set<string> tmp;
            for (auto& word : beginq) {                     // 清空访问过的单词
                dict.erase(word);
            }

            for (auto& word : beginq) {
                for (int i = 0; i < word.size(); ++i) {
                    string s = word;
                    for (char ch = 'a'; ch <= 'z'; ++ch) {  // 每个单词的字母从a-z替换一遍
                        if (s[i] == ch) {
                            continue;
                        }

                        s[i] = ch;                          // 替换一个字母后，字典中不存在则跳过
                        if (dict.find(s) == dict.end()) {
                            continue;
                        }

                        if (endq.find(s) != endq.end()) {   // 总是遍历beginq，所以在endq中查找，找到表示最短序列产生
                            found = true;                   // 本层循环还要继续，防止多条最短路径
                        }
                        tmp.insert(s);
                        flip ? trace[s].emplace_back(word) : trace[word].emplace_back(s);
                    }
                }
            }
            if (found) {
                break;                                      // 已经找到最短序列，不需要再进行下一轮BFS
            }
            if (tmp.size() <= endq.size()) {                // 首尾均衡查找,每次都是遍历beginq中的单词
                beginq = tmp;
            } else {
                beginq = endq;
                endq = tmp;
                flip = !flip;                               // beginq与endq交换，flip需要使用！反转
            }
        }

        vector<string> path;
        dfs(path, beginWord, endWord);
        return res;
    }

    void dfs(vector<string>& path, const string& begin, const string& end)
    {
        path.emplace_back(begin);
        if (begin == end) {                                 // 找到最短序列，存入结果中
            res.emplace_back(path);
            return;
        }

        for (auto word : trace[begin]) {
            dfs(path, word, end);
            path.pop_back();                                // 传path引用，回溯
        }
    }
};

