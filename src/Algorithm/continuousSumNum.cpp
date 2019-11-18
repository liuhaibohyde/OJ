/*
多少个 连续子区间 的和大于给定的数

给一串含有c个正整数的数组, 求出有多少个下标的连续区间, 它们的和大于等于x。

输入：
3 6
2 4 7
输出：
4

2+4 2+4+7 4+7 7 四个子区间的和大于6
 */
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

typedef unsigned int uint;
typedef unsigned long long ulonglong;

int main()
{
    uint c, x;
    uint *array = NULL;
    if (scanf("%u%u", &c, &x) == -1) {
        return -1;
    }
    array = (uint *)malloc(c * sizeof(uint));
    if (array == NULL) {
        return -1;
    }
    
    for (uint i = 0; i < c; i++) {
        if (scanf("%u", &array[i]) == -1) {
            free(array);
            return -1;
        }
    }
    
    ulonglong ans = 0;
    uint sum = array[0];
    uint pLeft = 0;
    uint pRight = 0;
    while (pLeft < c && pRight < c) {
        if (sum >= x) {
            sum -= array[pLeft++];  // 减去left位置的值，并将left向右移动一位
            ans += c - pRight;      // 从pRight这个位置开始，所有的序列和都大于C
        } else {
            pRight++;               // 先移动right，因为都是正整数，向右移动，和越大
            if (pRight >= c) {
                continue;
            }
            sum += array[pRight];
        }
    }

    printf("%llu", ans);
    free(array);
    return 0;
}
