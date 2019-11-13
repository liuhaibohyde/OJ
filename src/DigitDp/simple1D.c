/*
给定一个范围［l，r］，求出这个范围内的满足要求的数字的个数。要求是：
这些数字不能包含某个数字n。例如，不能包含数字”1”时，那么数字22、32、4都符合要求，数字2314，1233不符合要求。
*/

#include <stdio.h>
#include <memory.h>

int up[10+1];
int dp[10+1];

int dfs(int pos, int ne, int limit, int lead)
{
    if (pos == -1) {  
        if (lead) {
            return 0;
        }   
        return 1;
    }

    if (!limit && !lead && dp[pos] != -1) { // 当前位的值 非最大值 & 非前导0 & 已dp记录过，直接返回值
        return dp[pos];
    }
    
    int cnt = 0;
    int u = limit ? up[pos] : 9;
    
    for (int i = 0; i <= u; i++) {
        if (ne == 0 && i == ne && !lead) {  // 注意，如果不包含的数为0，还需要判断非前导0
            continue;
        } else if (i == ne) {
            continue;
        }
        
        cnt += dfs(pos - 1, ne, limit && i == up[pos], lead && i == 0);
    }
    
    if (!limit && !lead) {              // 只记录当前位 非最大值 & 非前导0 的个数 
        dp[pos] = cnt;          
    }
    return cnt;
}

int solve(int num, int ne)
{
    int pos = 0;
    while(num) {
        up[pos++] = num % 10;
        num /= 10;
    }

    return dfs(pos-1, ne, 1, 1);
}

int main()
{
    int l, r, n;
    scanf_s("%d %d %d", &l, &r, &n);

    memset(dp, sizeof(dp), -1, sizeof(dp));
    printf("%d\n", solve(r, n) - solve(l - 1, n));

    return 0;
}
