/*
交换任意两个元素，使得序列有序，求最少交换次数

答案：元素总数n - 循环节个数
循环节的求法是，先将数组排序，然后根据之前的坐标和排序之后的坐标，构建成一个有向图，然后在这个图上找到环

循环节解释：
有序列：5   4   3   2   1，排序后1   2   3   4   5
发现5、1虽然不在自己应该在的位置上，但是如果把1和5当做整体来看，那么对于最终排序好的序列来说，它们刚好占据了正确的位置。
所以对整个序列来说，只要1和5内部有序，那么整体也就有序了。1、5形成一个循环，称作循环节。
注意：如果一个元素排序前后位置没变，自己本身就可以看做是一个循环节。
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

using namespace std;


/*
 *  交换任意两数的本质是改变了元素位置，
 *  故建立元素与其目标状态应放置位置的映射关系
 */
int getMinSwaps(vector<int> &nums)
{
    vector<int> tmp(nums);
    sort(tmp.begin(), tmp.end());

    map<int, int> pos;                  // 排序后元素与所在位置的映射关系
    int len = (int)nums.size();
    for (int i = 0; i < len; i++) {
        pos[tmp[i]] = i;                // 建立每个元素与其应放位置的映射关系
    }

    int loops = 0;                      // 循环节个数
    vector<bool> visited(len, false);   // 记录位置是否访问过
    for (int i = 0; i < len; i++) {     // 找出循环节的个数
        if (!visited[i]) {              // 已经访问过的位置不再访问,退出循环时就访问了组成循环节的所有元素
            int j = i;
            while (!visited[j]) {
                visited[j] = true;
                j = pos[nums[j]];       // 原序列中j位置的元素在有序序列中的位置
            }
            loops++;
        }
    }
    return len - loops;
}

