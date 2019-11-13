/*
给定区间[a,b]，求区间内不包含84、5的个数。
例如845，184，15都不满足要求，而3834可以，因为84不连续且不包含5。
*/

#include <iostream>
#include <memory.h>

using namespace std;

typedef long long ll;

ll dp[20][2];
int upNum[20];

ll dfs(int pos, int pre, int status, bool lead, bool limit) // pre：传入上一位数字判断84，status：当前位是否是8，分两种记录dp
{
    if (pos == -1) {
        return 1;
    }

    if (!limit && !lead && dp[pos][status] != -1) {     // dp过，直接返回
        return dp[pos][status];
    }

    ll count = 0;
    int up = limit ? upNum[pos] : 9;
    for (int i = 0; i <= up; i++) {
        if ((pre == 8 && i == 4) || (i == 5)) {         // 84、5不满足条件
            continue;
        }
        
        count += dfs(pos - 1, i, i == 8, lead && i == 0, limit && i == upNum[pos]); // 当前位值为8、不为8分别记到状态1、0中
    }
    
    if (!limit && !lead) {
        dp[pos][status] = count;
    }
    
    return count;
}

ll solve(ll n)
{
    int pos = 0;
    while (n) {
        upNum[pos++] = n % 10;
        n /= 10;
    }

    memset(dp, -1, sizeof(dp));
    return dfs(pos - 1, -1, 0, true, true);
}

int main()
{
    ll a, b;
    cin >> a >> b;

    cout << solve(b) - solve(a - 1) << endl;

    return 0;
}
