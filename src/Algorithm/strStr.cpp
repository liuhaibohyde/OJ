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
        int n = needle.size();
        vector<vector<int>> dp(n + 1, vector<int>(128));
        dp[0][needle[0]] = 1;
        int x = 0;
        for (int i = 1; i < n; ++i) {
            for (int j = 0; j < 128; ++j)  {
                dp[i][j] = dp[x][j];
            }
            dp[i][needle[i]] = i + 1;
            x = dp[x][needle[i]];
        }

        x = 0;
        for (int i = 0; i < haystack.size(); ++i) {
            x = dp[x][haystack[i]];
            if (x == n) {
                return i - n + 1;
            }
        }
        return -1;
    }
};