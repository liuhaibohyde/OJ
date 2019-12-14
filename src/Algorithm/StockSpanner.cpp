/*
今天股票价格的跨度被定义为股票价格小于或等于今天价格的最大连续日数（从今天开始往回数，包括今天）。
例如，如果未来7天股票的价格是 [100, 80, 60, 70, 60, 75, 85]，那么股票跨度将是 [1, 1, 1, 2, 1, 4, 6]。

示例：
输入：["StockSpanner","next","next","next","next","next","next","next"], [[],[100],[80],[60],[70],[60],[75],[85]]
输出：[null,1,1,1,2,1,4,6]
解释：
首先，初始化 S = StockSpanner()，然后：
S.next(100) 被调用并返回 1，
S.next(80) 被调用并返回 1，
S.next(60) 被调用并返回 1，
S.next(70) 被调用并返回 2，
S.next(60) 被调用并返回 1，
S.next(75) 被调用并返回 4，
S.next(85) 被调用并返回 6。

注意 (例如) S.next(75) 返回 4，因为截至今天的最后 4 个价格
(包括今天的价格 75) 小于或等于今天的价格。

提示：
调用 StockSpanner.next(int price) 时，将有 1 <= price <= 10^5。
每个测试用例最多可以调用  10000 次 StockSpanner.next。
在所有测试用例中，
*/
#include <stdio.h>
#include <stdlib.h>
#include <stack>

using namespace std;

class StockSpanner {
public:
    stack<pair<int, int>> st;
    StockSpanner()
    {
    }

    // stack中保存单调递减的数字，后面出现大的数字就将队列中所有比它小的数字出栈
    int next(int price)
    {
        int count = 1;
        while (!st.empty() && st.top().first <= price) {
            count += st.top().second;
            st.pop();
        }
        st.push({price, count});
        return count;
    }
};
/**
 * Your StockSpanner object will be instantiated and caleld as such:
 * StockSpanner* obj = new StockSpanner();
 * int param_1 = obj->next(price);
 */
