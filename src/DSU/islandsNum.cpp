/*
给定一个由 '1'（陆地）和 '0'（水）组成的的二维网格，计算岛屿的数量(1的联通个数)。
一个岛被水包围，并且它是通过水平方向或垂直方向上相邻的陆地连接而成的。你可以假设网格的四个边均被水包围。

示例 1:
输入:
11110
11010
11000
00000
输出: 1

示例 2:
输入:
11000
11000
00100
00011
输出: 3

一、并查集解法：注意根节点的先后顺序
二、也可以用DFS、BFS解决(感染方式，访问过的节点修改值为‘0’,避免下次再访问到)
*/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <map>
#include <unordered_map>
#include <set>
#include <string>
#include <vector>
#include <memory.h>
#include <algorithm>

class Solution {
public:
    vector<int> f;

    int findRoot(int x) {
        if (f[x] == x) {
            return x;
        }

        f[x] = findRoot(f[x]);
        return f[x];
    }

    void Join(int x, int y) {
        int fx = findRoot(x);
        int fy = findRoot(y);
        
        if (fx > fy) {              // 注意“工”字形网络，如果不考虑大小的话，由于按照顺序访问每个点的右、下两点，会导致左上角的根节点挂到左下角上，多循环一些次数
            f[fx] = fy; 
        } else {
            f[fy] = fx;
        }
    }

    int numIslands(vector<vector<char>>& grid) {
        int row = grid.size();
        if (row == 0) {
            return 0;
        }
        int col = grid[0].size();

        for (int i = 0; i < row * col; i++) {
            f.emplace_back(i);
        }

        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                if (grid[i][j] == '0') {
                    continue;
                }

                int pos = i * col + j;
                if (i + 1 < row && grid[i + 1][j] == '1') {
                    Join(pos, pos + col);
                } 
                if (j + 1 < col && grid[i][j + 1] == '1') {
                    Join(pos, pos + 1);
                }
            }
        }

        int ans = 0;
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                int pos = i * col + j;
                if (findRoot(pos) == pos && grid[i][j] == '1') {
                    ans++;
                }
            }
        }

        return ans;
    }
};

