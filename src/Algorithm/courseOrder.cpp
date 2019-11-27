/*
课程选修顺序

现在你总共有 n 门课需要选，记为 0 到 n-1。
在选修某些课程之前需要一些先修课程。 例如，想要学习课程 0 ，你需要先完成课程 1 ，我们用一个匹配来表示他们: [0,1]
返回正确的顺序（有多个的话，返回任意一个），不可能全部选修（有环）返回空数组

输入: 2, [[1,0]] 
输出: [0,1]

输入: 4, [[1,0],[2,0],[3,1],[3,2]]
输出: [0,1,2,3] or [0,2,1,3]
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
#include <queue>
#include <stack>

using namespace std;

class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        vector<int> indegree(numCourses, 0);
        for (auto& iter : prerequisites) {          // 统计每门课的入度
            indegree[iter[0]]++;
        }

        stack<int> s;
        for (int i = 0; i < numCourses; i++) {
            if (indegree[i] == 0) {
                s.emplace(i);                       // 入度为0的入栈
            }
        }

        vector<int> ans;
        while (!s.empty()) {
            int n = s.top();                       // 入度为0的直接存入结果中
            ans.emplace_back(n);
            s.pop();

            for (auto& iter : prerequisites) {
                if (iter[1] == n) {
                    if (--indegree[iter[0]] == 0) {
                        s.emplace(iter[0]);
                    }
                }
            }
        }

        if (ans.size() < numCourses) {              // 存在环
            ans.clear();
        }

        return ans;
    }
};


int main()
{
    Solution* so = new Solution();

    vector<vector<int>> pre = {{0,1}};
    so->findOrder(2, pre);

    delete so;
    return 0;
}
