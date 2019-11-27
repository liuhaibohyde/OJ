/*
两个二维数组有向图red_edges，blue_edges， 它们中的每一个 [i, j] 对表示从节点 i 到节点 j 的有向边（带颜色）。
求从0开始，到节点n-1的最短路径(返回数组，每个点的最短路径都要计算，没有路径赋值-1)

输入：n = 3, red_edges = [[0,1]], blue_edges = [[1,2]]
输出：[0,1,2]

输入：n = 3, red_edges = [[0,1],[0,2]], blue_edges = [[1,0]]
输出：[0,1,1]

下面是DFS解法
*/
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>    // 无序map，底层hash实现，这里其实用不到
#include <map>
#include <set>

using namespace std;

class Solution {
public:
    void dfs(vector<vector<int>>& red, vector<vector<int>>& blue, int color, int i, vector<vector<int>>& res) {

        if (color) {
            for (auto& iter : blue[i]) {
                if (res[i][color] + 1 < res[iter][!color]) {
                    res[iter][!color] = res[i][color] + 1;
                    dfs(red, blue, !color, iter, res);
                }
            }
        } else {
            for (auto& iter : red[i]) {
                if (res[i][color] + 1 < res[iter][!color]) {
                    res[iter][!color] = res[i][color] + 1;
                    dfs(red, blue, !color, iter, res);
                }
            }
        }
    }

    vector<int> shortestAlternatingPaths(int n, vector<vector<int>>& red_edges, vector<vector<int>>& blue_edges) {
        vector<vector<int>> red(n);
        vector<vector<int>> blue(n);
        for (auto& iter : red_edges) {
            red[iter[0]].emplace_back(iter[1]);
        }
        for (auto& iter : blue_edges) {
            blue[iter[0]].emplace_back(iter[1]);
        }

        vector<vector<int> > res(n, vector<int>(2, INT32_MAX));
        res[0] = {0, 0};

        dfs(red, blue, 0, 0, res);
        dfs(red, blue, 1, 0, res);

        vector<int> ans(n);
        for (int i = 0; i < n; ++i) {
            ans[i] = min(res[i][0], res[i][1]);
            if (ans[i] == INT32_MAX) {
                ans[i] = -1;
            }
        }
        return ans;
    }
};

int main()
{
    Solution* so = new Solution();
    
    vector<vector<int>> red = {{0,1}};
    vector<vector<int>> blue = {{1,2}};

    vector<int> ans = so->shortestAlternatingPaths(3, red, blue);

    delete so;
    return 0;
}