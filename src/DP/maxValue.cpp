/*
给定总钱数，物品个数，每个物品有价格、重要度，求能达到的最大价值
*/
#include <stdio.h>
#include <memory>

#define RETURN_IF(expr, errorno) do {     \
        if (expr) {              \
            return errorno;              \
        }                        \
    } while (0)

# define MAX(a,b) (((a) > (b)) ? (a) : (b))

int getMaxValue(int *p, int maxMoney, int maxNum)
{
    int* result = (int*)malloc(30000 * sizeof(int));
    RETURN_IF(result == NULL, -1);
    memset(result, 0, sizeof(int) * 30000);

    for (int i = 1; i <= maxNum; i++) {             // 从0开始遍历物品，物品要么买，要么不买
        int currMoney = *(p + 2 * i);       
        int currWeight = *(p + 2 * i + 1);  
        int currValue = currMoney * currWeight; 

        for (int j = maxMoney; j >= currMoney; j--) {   // 从最大的钱数开始反向遍历，只需要遍历到与当前物品钱相等即可
            int value = result[j - currMoney] + currValue;  // 这件物品买下的价值 = 剩下的钱所能达到的最大价值 + 当前物品价值
            result[j] = MAX(value, result[j]);  // 这件物品买下的价值，没买下的价值，取大的即可
        }
    }

    int maxValue = result[maxMoney];            // 返回结果
    free(result);
    result = NULL;

    return maxValue;
}

void GetResult(int*p, int& Get_Result)
{	 
    int maxMoney = *(p);
    int maxNum = *(p + 1);

    Get_Result = getMaxValue(p, maxMoney, maxNum);

    return;
} 

int main()
{
    int a[6][2] = {{1000,5},{800,2},{400,5},{300,5},{400,3},{200,2}} ;
	int *p = &a[0][0];
	int GetNumber = 0;
	GetResult(p,GetNumber);

    return 0;
}
