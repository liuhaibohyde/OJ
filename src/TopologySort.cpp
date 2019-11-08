/*
给出n表示有多少个大写字母A-Z，例如： n = 4时有A,B,C,D
m行关系，每行两个字母之间用<连接，如：A<B, B<C, C<D
1、矛盾关系：A<B, B<A
2、m行过后还是无法确定关系
3、第i行（i<m）就可以确定所有n个字母关系时，直接输出
*/

#include <iostream>
#include <vector>
#include <stack>
#include <string>

using namespace std;

int TopologySort(vector<vector<int>> &G, vector<int> &d, int n, vector<int> &v)
{
    vector<int> degree(d);
    stack<int> s;
    for (int i = 0; i < n; i++) {
        if (degree[i] == 0) {   // 入度为0的节点入栈
            s.push(i);
        }
    }

    int flag = 0;
    v.clear();
    while (!s.empty()) {
        if (s.size() > 1) {     // 栈中不止一个元素入度为0，说明这几个元素之间互相无法确定大小关系
            flag = 1;
        }

        int cur = s.top();
        v.push_back(cur);
        s.pop();

        for (int i = 0; i < n; i++) {   // 遍历矩阵中剩下的节点关系
            if (G[cur][i] == 1) {       // 当前节点已被计算，因此被当前节点指向的节点入度需要减1
                degree[i]--;
                if (degree[i] == 0) {   // 如果入度为0了，那么入栈
                    s.push(i);
                }
            }
        }
    }
    if (v.size() < n) {              // 此有向图有回路，两个节点互为儿子、父亲节点，导致没有入度为0的节点可取，因为个数不足
        return -1;
    } else {                         // 为一个拓扑序列
        if (flag == 1) {
            return -2;               // 元素之间有无法确定的大小关系
        } else {
            return 0;                // 有一个唯一的大小关系的拓扑序列
        }
    }
}

int main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> G(n, vector<int>(n, 0));
    vector<int> degree(n, 0);
    vector<int> out;
    
    for (int i = 0; i < m; i++) {
        string s;
        cin >> s;
        int v = s[0] - 'A';
        int w = s[2] - 'A';
        if (G[v][w] == 0) {     // 同一关系，应该只计算一次
            G[v][w] = 1;        
            degree[w] += 1;     // 统计节点的入度数
        }

        int ret = TopologySort(G, degree, n, out);

        if (ret == 0) {
            cout << "Sorted sequence determined after " << i + 1 << " relations: ";
            for (auto it : out) {
                char c = 'A' + it;
                cout << c;
            }
            cout << ".";
            return 0;
        } else if (ret == -1) {
            cout << "Inconsistency found after " << i + 1 << " relations.";
            return 0;
        }
    }

    cout << "Sorted sequence cannot be determined.";
    return 0;
}
