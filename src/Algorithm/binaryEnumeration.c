/*
二进制枚举：枚举所有状态，bit位为1表示选中，0不选中
常用于求某一集合的子集个数
*/

/*
本题是10个人队伍，分两队，要求分完两队的和相差最小
*/
#include <stdio.h>
#include <math.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))

int chooseNumOf(int n)
{
    int len = 0;
    while (n) {
        n &= n - 1;
        ++len;
    }
    
    return len;
}

int main()
{   
    int i;
    int a[10];
    for (i = 0; i < 10; i++) {
        scanf_s("%d", &a[i]);
    }
    
    int minRet = 0x7FFFFFFF;
    for (i = 0x1f; i < (1 << 10); i++) {   // 2^10种组合
        if (chooseNumOf(i) != 5) {         // 刚好选中的是5个才计算
            continue;
        }

        int sum1 = 0;
        int sum2 = 0;
        for (int j = 0; j < 10; j++) {
            if (i & (1 << j)) {
                sum1 += a[j];
            } else {
                sum2 += a[j];
            }
        }
        minRet = MIN(minRet, abs(sum1 - sum2));
    }
    
    printf("%d\n", minRet);
    system("pause");
    return 0;
}
