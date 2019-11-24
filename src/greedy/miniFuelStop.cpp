/*
到达终点需要的最少加油次数

贪心+优先队列，没油时，从路过的加油站队列中，取出油最多的加。
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

using namespace std;

class Solution {
public:
    int minRefuelStops(int target, int startFuel, vector<vector<int>>& stations) {
        priority_queue<int> fuels;

        int ans = 0;
        while (startFuel) {
            if (startFuel >= target) {
                return ans;
            }
            
            ++ans;                                  // 油不够到终点，肯定需要加油
            for (auto iter = stations.begin(); iter != stations.end();) {
                if (iter[0][1] > startFuel) {
                    break;
                }
                fuels.push(iter[0][1]);             // 路过的加油站保存进优先队列
                iter = stations.erase(iter);
            }
            
            if (fuels.empty()) {
                break;                              // 无油可加，退出
            } else {
                startFuel += fuels.top();           // 取路过的加油站中油最多的
                fuels.pop();                        // 在队列中删除该加油站
            }

        }
        
        return -1;
    }
};

int main()
{
    Solution* so = new Solution();
    
    vector<vector<int>> stations = {{10,60}, {20,30}, {30,30}, {60,40}};
    int ans = so->minRefuelStops(100, 10, stations);

    delete so;
    return 0;
}
