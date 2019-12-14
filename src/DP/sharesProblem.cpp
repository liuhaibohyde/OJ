/*
给定一个数组，它的第 i 个元素是一支给定股票第 i 天的价格。
设计一个算法来计算你所能获取的最大利润。
注意：你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。

示例 1:
输入: [7,1,5,3,6,4]
输出: 7
解释: 在第 2 天（股票价格 = 1）的时候买入，在第 3 天（股票价格 = 5）的时候卖出, 这笔交易所能获得利润 = 5-1 = 4 。
     随后，在第 4 天（股票价格 = 3）的时候买入，在第 5 天（股票价格 = 6）的时候卖出, 这笔交易所能获得利润 = 6-3 = 3 。

示例 2:
输入: [1,2,3,4,5]
输出: 4
解释: 在第 1 天（股票价格 = 1）的时候买入，在第 5 天 （股票价格 = 5）的时候卖出, 这笔交易所能获得利润 = 5-1 = 4 。
     注意你不能在第 1 天和第 2 天接连购买股票，之后再将它们卖出。
     因为这样属于同时参与了多笔交易，你必须在再次购买前出售掉之前的股票。

示例 3:
输入: [7,6,4,3,1]
输出: 0
解释: 在这种情况下, 没有交易完成, 所以最大利润为 0。
*/
#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;

/*
一共有六道类似的题目，只是给出的限制交易条件不同而已：
1、只能交易一次
2、无数次
3、最多交易2次
4、最多交易k次
5、卖出后需要冻结一天
6、每次卖出需要支付手续费

所有六道题目都可以按照下面的公式解决：
状态转移方程：
n-天数，k-交易次数，最后0-没有股票，1-有股票
dp[i][k][0] = max(dp[i-1][k][0], dp[i-1][k][1] + prices[i]);
                        rest            卖出
今天没有股票，两种可能：
    昨天就没有股票，今天选择rest
    昨天有股票，今天选择sell，所以加上当天的价格

dp[i][k][1] = max(dp[i-1][k][1], dp[i-1][k-1][0] - prices[i]);
                        rest            买入
今天有股票，两种可能：
    昨天就有股票，今天选择rest
    昨天没有股票，今天选择buy，所以减去今天价格

通过观察上面的公式，可以发现其实交易天数i这个维度只和前一天有关，可以去掉
注意第3、4题，限定交易次数的，需要枚举交易次数K的状态
*/

/*
309. 最佳买卖股票时机含冷冻期 - 卖出股票后，你无法在第二天买入股票 (即冷冻期为 1 天)。
这里不限定交易次数，所以K这个维度也优化掉，最后只剩下两个维度买入、卖出，不需要数组了，直接定义变量解决
*/
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.empty()) {
            return 0;
        }
        int dpi0 = 0;
        int dpi1 = -prices[0];
        int dpPre0 = 0;
        for (int i = 0; i < prices.size(); i++) {
            int tmp = dpi0; 
            dpi0 = max(dpi0, dpi1 + prices[i]);
            dpi1 = max(dpi1, dpPre0 - prices[i]);
            dpPre0 = tmp;                           // 注意这里因为有冷冻期，需要保存前天的利润
        }
        return dpi0;
    }
};

/*
123. 买卖股票的最佳时机 III - 你最多可以完成 两笔 交易。
*/
class Solution {
public:
    int maxProfit(vector<int>& prices)
    {
        if (prices.empty()) {
            return 0;
        }

        // int dp[prices.size()][2 + 1][2] = {{{0}}};  // 2+1是为了转移方程时好写k-1
        int dp[2 + 1][2] = {{0}};  // 2+1是为了转移方程时好写k-1
        for (int i = 0; i < prices.size(); i++) {
            for (int k = 2; k >= 1; k--) {  // 特别注意这里，需要额外穷举交易次数的状态
                if (i == 0) {
                    // dp[i][k][0] = dp[i][0][0] = 0;
                    // dp[i][k][1] = dp[i][0][1] = -prices[0];  // 刚开始如有股票，利润为-prices[0]
                    dp[k][0] = dp[0][0] = 0;    // 没有股票，利润为0
                    dp[k][1] = dp[0][1] = -prices[0];  // 刚开始如有股票，利润为-prices[0]
                    continue;
                }

                // 买入时交易次数减1，也可以在卖出时减
                // dp[i][k][0] = max(dp[i - 1][k][0], dp[i - 1][k][1] + prices[i]);
                // dp[i][k][1] = max(dp[i - 1][k][1], dp[i - 1][k - 1][0] - prices[i]);
                // 可以看出i值依赖于i-1，可以优化掉
                dp[k][0] = max(dp[k][0], dp[k][1] + prices[i]);
                dp[k][1] = max(dp[k][1], dp[k - 1][0] - prices[i]);
            }
        }
        return dp[2][0];  // 最终手里没有股票的利润大
    }
};

/*
188. 买卖股票的最佳时机 IV - 你最多可以完成 k 笔交易。
最多K笔交易，因为买入卖出需要两天，所以如果k>n/2，相当于交易无数次。
同时限定了k的大小，可以避免dp数组太大暴栈
*/
class Solution {
public:
    int maxProfit(int maxk, vector<int>& prices) {
        if (prices.empty() || maxk == 0) {
            return 0;
        }
        
        if (maxk > prices.size() / 2) {
            int dpi0 = 0;   // 初始时手里没有股票，利润0
            int dpi1 = -prices[0];   // 初始时手里有股票，-prices[0]
            for (int i = 0; i < prices.size(); i++) {
                dpi0 = max(dpi0, dpi1 + prices[i]);
                dpi1 = max(dpi1, dpi0 - prices[i]);
            }
            return dpi0;
        } 
            
        int dp[maxk + 1][2] = {{0}};
        for (int i = 0; i < prices.size(); i++) {
            for (int k = maxk; k >= 1; k--) {
                if (i == 0) {                   // 初始状态设置
                    dp[k][0] = dp[0][0] = 0;    // 没有股票，利润为0
                    dp[k][1] = dp[0][1] = -prices[0];   // 有股票，利润为-prices[0]
                    continue;
                }
                
                // 买入的时候交易次数减1，也可以在卖出的时候减
                dp[k][0] = max(dp[k][0], dp[k][1] + prices[i]);
                dp[k][1] = max(dp[k][1], dp[k - 1][0] - prices[i]);
            }
        }
        return dp[maxk][0];    // 最终手里没有股票的利润高
    }
};