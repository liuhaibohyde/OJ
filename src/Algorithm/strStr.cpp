#include <vector>	
#include <string>	

using namespace std;

class Solution {
public:
    int strStr(string haystack, string needle) {
        if (needle.empty()) {
            return 0;
        }
        if (haystack.empty()) {
            return -1;
        }

        // 构造KMP数组
        int len = needle.size();
        vector<vector<int>> dp(len + 1, vector<int>(256, 0));   // dp[当前状态(字符下标index)][下一个字符] = 下一个状态(字符下标index)
        dp[0][needle[0]] = 1;                                   // 初始状态，只有匹配到needle中的第一个字符才会“状态前进”
        int x = 0;
        for (int i = 1; i < len; i++) {
            for (int j = 0; j < 256; j++) {
                dp[i][j] = dp[x][j];    // 遍历ASCII表赋初值为上一个状态，即X的状态；后续实际匹配中，如果当前字符匹配不到，则回去找X的状态
            }
            dp[i][needle[i]] = i + 1;   // 匹配到needle中的字符，状态前进
            x = dp[x][needle[i]];       // x表示的是与当前i具有相同前缀的上一个状态
        }
        
        x = 0;
        for (int i = 0; i < haystack.size(); i++) {
            x = dp[x][haystack[i]];
            if (x == len) {
                return i - len + 1;
            }
        }
        return -1;
    }
};
