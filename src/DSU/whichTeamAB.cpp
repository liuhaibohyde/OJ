/*
并查集:
n个人分成两个队伍，给出m个关系（每个关系两个人），判断是否是一个team、是否矛盾
*/
#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

vector<int> f;
vector<int> v;

int Find(int x)
{
    if (f[x] == x) {
        return x;
    }

    int r = f[x];
    f[x] = Find(f[x]);      // 路径压缩，将节点直接指向最终根节点

    v[x] = v[x] ^ v[r];     // 压缩后，更新每个节点与最终根节点之间的关系
    return f[x];
}

int check(int a, int b, int c)
{
    int af = Find(a);
    int bf = Find(b);

    if (af == bf) {         // 同一个根节点
        if (c == 2) {
            cout << ((v[a]^v[b]) ? "we are not a team" : "we are a team") << endl;
        } else {
            if ((v[a]^v[b]) != c) {
                cout << "da pian zi" << endl;
            }
        }
    } else {                            // 根节点不同
        if (c < 2) {
            f[bf] = af;                 // union, 任选一个父节点
            v[bf] = c ^ v[a] ^ v[b];    // 只有两个队伍，互相异或后既是结果
        } else {
            cout << "not sure yet" << endl;
        }
    }
}

int main()
{
    int n, m;
    cin >> n >> m;
    f.push_back(0);
    v.push_back(0);
    for (int i = 1; i <= n; i++) {
        f.push_back(i);
        v.push_back(0);
    }

    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;

        int ret = check(a, b, c);
    }

    return 0;
}
