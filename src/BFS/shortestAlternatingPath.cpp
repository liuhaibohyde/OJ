/*
两个二维数组有向图red_edges，blue_edges， 它们中的每一个 [i, j] 对表示从节点 i 到节点 j 的有向边（带颜色）。
求从0开始，到节点n-1的最短路径(返回数组，每个点的最短路径都要计算，没有路径赋值-1)

输入：n = 3, red_edges = [[0,1]], blue_edges = [[1,2]]
输出：[0,1,2]

输入：n = 3, red_edges = [[0,1],[0,2]], blue_edges = [[1,0]]
输出：[0,1,1]

下面是BFS解法
*/
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>    // 无序map，底层hash实现，这里其实用不到
#include <map>
#include <set>
#include <queue>

using namespace std;

class Solution {
public:

    vector<int> shortestAlternatingPaths(int n, vector<vector<int>>& red_edges, vector<vector<int>>& blue_edges) {
        vector<vector<int>> red(n);
        vector<vector<int>> blue(n);
        for (auto& iter : red_edges) {
            red[iter[0]].emplace_back(iter[1]);
        }
        for (auto& iter : blue_edges) {
            blue[iter[0]].emplace_back(iter[1]);
        }

        vector<int> res(n, INT32_MAX);
        vector<vector<vector<int>>> visit(n, vector<vector<int>>(n, vector<int>(2, 0)));
        queue<pair<int, int>> pos;              // 每一轮BFS的 起点 - 颜色
        pos.emplace(make_pair(0, 0));           // 0 红色
        pos.emplace(make_pair(0, 1));           // 1 蓝色

        int step = 0;
        while (!pos.empty()) {
            int size = pos.size();
            step++;                             // BFS，每次step+1

            for (int i = 0; i < size; i++) {    // 需要分别遍历当前step+1，红、蓝两色能达到的所有的点
                int curr = pos.front().first;
                int color = pos.front().second;
                pos.pop();                      // 出队

                if (color) {                    // 蓝色
                    for (auto& iter : blue[curr]) {                 // iter 即下一个可到达的点
                        if (!visit[curr][iter][!color]) {
                            res[iter] = min(res[iter], step);       // 取步数小的
                            visit[curr][iter][!color] = 1;
                            pos.emplace(make_pair(iter, !color));   // 下一轮遍历的起点入队
                        }
                    }
                } else {                        // 红色
                    for (auto& iter : red[curr]) {
                        if (!visit[curr][iter][!color]) {
                            res[iter] = min(res[iter], step);       // 取步数小的
                            visit[curr][iter][!color] = 1;
                            pos.emplace(make_pair(iter, !color));   // 下一轮遍历的起点入队
                        }
                    }
                }
            }
        }

        res[0] = 0;
        for (auto& iter : res) {
            if(iter == INT32_MAX){
                iter = -1;
            }
        }

        return res;
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