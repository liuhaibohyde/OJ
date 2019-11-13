/*
并查集：处理一些不交集（Disjoint Sets）的合并及查询问题
*/

/*
n组区间，给定每个区间的奇偶（权值），求出第几组区间和前面已知条件矛盾
本题带权值，没办法路径压缩
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

int FindFather(map<int, int>& fMap, map<int, int>& disMap, int x, int& dis)   // 查找父节点，并计算距离（奇偶）
{
    int r = x;
    while (fMap[r] != r) {
        dis += disMap[r];
        r = fMap[r];
    }

    return r;
}

int solution(vector<vector<int>>& query, int m)
{
    map<int, int> fMap;     // 父节点表，节点i的父节点为fMap[i]
    map<int ,int> disMap;   // 到父节点的距离表，节点i到父节点fMap[i]的距离（奇偶）为disMap[i]
    fMap.clear();
    disMap.clear();

    int ans = 0;
    for (auto& input : query) {
        int l = input[0];
        int r = input[1];
        int dis = input[2];

        if (fMap[r] != 0 && fMap[l] != 0) {                 // 左右节点都曾出现过
             int ld = 0;
             int rd = 0;
             int lf = FindFather(fMap, disMap, l, ld);      // 找到父节点
             int rf = FindFather(fMap, disMap, r, rd);

            if (lf == rf) {                                 // 父节点相同，判断奇偶是否合法
                int disDiff = abs(ld - rd) % 2;
                if (disDiff != dis) {                       // 距离（奇偶）不同，矛盾
                    return ans; 
                }
            } else {                                        // 不是同一个父节点，union合并
                if (rf < lf) {
                    fMap[lf] = rf;                          // 取值小的做父节点，并计算被合并的那个父节点的距离（奇偶）
                    disMap[lf] = abs(rd - ld - dis) % 2;
                } else {
                    fMap[rf] = lf;
                    disMap[rf] = abs(dis + ld - rd) % 2;
                }
            }
        } else if (fMap[r] != 0 && fMap[r] != r && fMap[r] > l) {  // 仅右节点出现，找到最大父节点，避免出现多个父节点
            fMap[l] = fMap[r];
            disMap[l] = abs(disMap[r] - dis) % 2;
        } else {                                            // 第一次出现的节点，其父节点就是自己,更新父节点表、距离表
            fMap[r] = l;                                    // 值小的左节点做父节点
            disMap[r] = dis;
            fMap[l] = fMap[l] == 0 ? l : fMap[l];           // 左节点的父亲是自己
        }
        ans++;                                              // 目前还没有矛盾，结果累加
    }

    return ans;
}

int main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> query(m, vector<int>(3, 0));
    for (int i = 0; i < m; i++) {
        cin >> query[i][0] >> query[i][1] >> query[i][2];
    }
    
    cout << solution(query, m) << endl;

    return 0;
}

