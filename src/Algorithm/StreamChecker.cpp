/*
按下述要求实现 StreamChecker 类：
	StreamChecker(words)：构造函数，用给定的字词初始化数据结构。
	query(letter)：如果存在某些 k >= 1，可以用查询的最后 k个字符（按从旧到新顺序，包括刚刚查询的字母）
        拼写出给定字词表中的某一字词时，返回 true。否则，返回 false。
示例：
StreamChecker streamChecker = new StreamChecker(["cd","f","kl"]); // 初始化字典
streamChecker.query('a');          // 返回 false
streamChecker.query('b');          // 返回 false
streamChecker.query('c');          // 返回 false
streamChecker.query('d');          // 返回 true，因为 'cd' 在字词表中
streamChecker.query('e');          // 返回 false
streamChecker.query('f');          // 返回 true，因为 'f' 在字词表中
streamChecker.query('g');          // 返回 false
streamChecker.query('h');          // 返回 false
streamChecker.query('i');          // 返回 false
streamChecker.query('j');          // 返回 false
streamChecker.query('k');          // 返回 false
streamChecker.query('l');          // 返回 true，因为 'kl' 在字词表中。
提示：
	1 <= words.length <= 2000
	1 <= words[i].length <= 2000
	字词只包含小写英文字母。
	待查项只包含小写英文字母。
	待查项最多 40000 个。
*/

#include <stdio.h>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

class StreamChecker {
    struct TrieNode {
        bool flag;
        unordered_map<char, TrieNode*> next;
        TrieNode() : flag(false) {}
    };

public:
    TrieNode* root = new TrieNode();
    string s;

    StreamChecker(vector<string>& words) {
        for (auto& word : words) {              // 创建字典树
            auto node = root;                   // 每个单词都从根节点开始
            for (int i = word.size() - 1; i >= 0; i--) {
                if (node->next.find(word[i]) == node->next.end()) {
                    node->next[word[i]] = new TrieNode();
                }
                node = node->next[word[i]];
            }
            node->flag = true;                  // flag为true，完整的一个单词
        }
    }
    
    bool query(char letter) {
        s += letter;
        auto node = root;
        for (int i = s.size() - 1; i >= 0; i--) {
            if (node->flag) {
                return true;
            }
            if (node->next.find(s[i]) == node->next.end()) {
                return false;
            }
            node = node->next[s[i]];
        }
        return node->flag;
    }
};

/**
 * Your StreamChecker object will be instantiated and called as such:
 * StreamChecker* obj = new StreamChecker(words);
 * bool param_1 = obj->query(letter);
 */