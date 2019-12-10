/*
有 N 个网络节点，标记为 1 到 N。
给定一个列表 times，表示信号经过有向边的传递时间。 times[i] = (u, v, w)，其中 u 是源节点，v 是目标节点， w 是一个信号从源节点传递到目标节点的时间。
现在，我们向当前的节点 K 发送了一个信号。需要多久才能使所有节点都收到信号？如果不能使所有节点收到信号，返回 -1。

注意:
N 的范围在 [1, 100] 之间。
K 的范围在 [1, N] 之间。
times 的长度在 [1, 6000] 之间。
所有的边 times[i] = (u, v, w) 都有 1 <= u, v <= N 且 0 <= w <= 100。
*/

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <queue>
#include <iostream>
#include <algorithm>

using namespace std;

/*
Floyd
从K点开始，覆盖全部有向图节点需要的时间(额外记录了最短路径)。
此题没有负边，如果有负数的话，定义的dist、path初始化为INT_MAX
*/
class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int N, int K)
    {
        vector<vector<int>> path(N + 1, vector<int>(N + 1, -1));

        // times转为邻接矩阵
        vector<vector<int>> dist(path);
        for (int i = 0; i < dist.size(); ++i) {
            dist[i][i] = 0;
        }
        for (int i = 0; i < times.size(); ++i) {
            dist[times[i][0]][times[i][1]] = times[i][2];
        }

        for (int k = 1; k < N + 1; ++k) {
            for (int i = 1; i < N + 1; ++i) {
                for (int j = 1; j < N + 1; ++j) {
                    if (dist[i][k] != -1 && dist[k][j] != -1 &&
                        (dist[i][k] + dist[k][j] < dist[i][j] || dist[i][j] == -1)) {
                        path[i][j] = k;  // path[i][i]如果不为-1，则记录的是i->j经过的中转点
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }

        int res = -1;
        for (int i = 1; i < N + 1; ++i) {
            if (dist[K][i] == -1) {
                return -1;
            }
            res = max(res, dist[K][i]);
        }
        return res;
    }
};

/*
Dijkstra
只能处理不包含负边的有向图
*/
class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int N, int K)
    {
        vector<vector<int>> dist(N + 1, vector<int>(N + 1, INT32_MAX));
        for (auto& iter : times) {
            dist[iter[0]][iter[1]] = iter[2];
        }
        for (int i = 0; i < dist.size(); i++) {
            dist[i][i] = 0;
        }

        vector<bool> visited(N + 1, false);
        for (int loop = 0; loop < N; loop++) {  // 循环n轮
            int minValue = INT32_MAX;
            int minIdx = 0;
            for (int i = 1; i < dist.size(); i++) {
                if (!visited[i] && dist[K][i] < minValue) {  // 未访问过的点中查找K能到达的点的最小值
                    minValue = dist[K][i];
                    minIdx = i;
                }
            }
            if (minValue == INT32_MAX) {
                return -1;
            }
            visited[minIdx] = true;
            for (int i = 1; i < dist.size(); i++) {  // 以minIdx为起点，松弛
                if (dist[minIdx][i] != INT32_MAX && (minValue + dist[minIdx][i] < dist[K][i])) {
                    dist[K][i] = minValue + dist[minIdx][i];
                }
            }
        }

        int ans = -1;
        for (int i = 1; i < dist.size(); i++) {
            if (dist[K][i] == INT32_MAX) {
                return -1;
            }
            ans = max(ans, dist[K][i]);
        }
        return ans;
    }
};

/*
Bellman-ford - 不推荐使用，性能比较低
遍历每条边进行松弛，最多需要遍历n-1编（n为顶点数）
*/
class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int N, int K)
    {
        vector<int> dist(N + 1, -1);
        dist[K] = 0;

        for (int loop = 0; loop < N - 1; loop++) {
            bool flag = false;
            for (int i = 0; i < times.size(); i++) {
                int src = times[i][0];
                int des = times[i][1];
                int dis = times[i][2];

                if (dist[src] != -1 && (dist[src] + dis < dist[des] || dist[des] == -1)) {
                    dist[des] = dist[src] + dis;
                    flag = true;
                }
            }

            if (!flag) {        // flag=false,本轮循环没有任何节点可以松弛，已经找到最短路径，退出循环
                break;
            }
        }

        int res = -1;
        for (int i = 1; i < dist.size(); i++) {
            if (dist[i] == -1) {
                return -1;
            }
            // if (dist[times[i][1]] > dist[times[i][0]] + times[i][2]) {  // 最多n-1轮循环，如果还能松弛，则存在负权回路
            //     return -1;
            // }
            res = max(res, dist[i]);
        }
        return res;
    }
};

/*
SPFA
优化版Bellman-ford
*/
class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int N, int K)
    {
        vector<vector<int>> dist(N + 1, vector<int>(N + 1, INT32_MAX));
        for (auto& iter : times) {
            dist[iter[0]][iter[1]] = iter[2];
        }
        for (int i = 0; i < dist.size(); i++) {
            dist[i][i] = 0;
        }

        vector<int> res(N + 1, INT32_MAX);  // 松弛成功的顶点需要入列，这里需要额外的一个数组
        res[K] = 0;
        queue<int> q;
        q.emplace(K);  // 从起点K开始入列
        while (!q.empty()) {
            auto cur = q.front();
            q.pop();
            for (int i = 1; i < dist.size(); i++) { // 以当前点为起点，松弛
                if (dist[cur][i] != INT32_MAX && (res[cur] + dist[cur][i] < res[i])) {
                    res[i] = res[cur] + dist[cur][i];
                    q.emplace(i);  // 松弛成功的顶点入列,判断存在负环，可以记录每个点的入列次数，大于总顶点数即存在
                }
            }
        }

        int ans = -1;
        for (int i = 1; i < N + 1; i++) {
            if (res[i] == INT32_MAX) {
                return -1;
            }
            ans = max(ans, res[i]);
        }
        return ans;
    }
};

