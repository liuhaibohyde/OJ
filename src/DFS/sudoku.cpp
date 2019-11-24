/*
DFS基本应用————数独游戏：
在一个9*9的方阵上划分出9个更小的3*3的子方阵。每个格子上填1到9这9个数字中的一个。有些格子上的数字确定了，不能再改动。
要求把剩余尚未确定的地方填上适当的数字并且保证：
    1.任意一行的9个数字均不相同
    2.任意一列的9个数字均不相同
    3.任意子方阵中的9个数字均不相同
 */
#include <stdio.h>
#include <iostream>

int dfs(int map[9][9], int minMap[9][10], int row[9][10], int col[9][10])
{
    for (int i = 0; i < 9; i++) {                                           // 行列挨个扫描
        for (int j = 0; j < 9; j++) {
            if (map[i][j] != 0) {                                           // 已经填有值，跳过
                continue;
            }

            int k = (i / 3) * 3 + (j / 3);                                  // k-第几个子方阵
            for (int num = 1; num <= 9; num++) {                            // 1-9每个数字dfs
                if (!minMap[k][num] && !row[i][num] && !col[j][num]) {
                    map[i][j] = num;
                    minMap[k][num] = row[i][num] = col[j][num] = 1;         // 保存被占用的数字
                    if (dfs(map, minMap, row, col)) {
                        return 1;
                    }
                    minMap[k][num] = row[i][num] = col[j][num] = 0;         // 回溯
                    map[i][j] = 0;
                }
            }
            return 0;   // 9个数字均无解，返回失败
        }
    }

    return 1;
}

int main()
{
    int map[9][9] = {0};                    // 保存最终结果
    int row[9][10] = {0};                   // 保存每一行被占用的数字
    int col[9][10] = {0};                   // 保存每一列被占用的数字
    int minMap[9][10] = {0};                // 保存每个子方阵被占用的数字
    char tmp[10] = {0};

    for (int i = 0; i < 9; i++) {
        scanf("%s", tmp);
        for (int j = 0; j < 9; j++) {
            map[i][j] = tmp[j] - '0';
            if (map[i][j]) {
                int k = (i / 3) * 3 + (j / 3);
                int value = map[i][j];
                row[i][value] = 1;
                col[j][value] = 1;
                minMap[k][value] = 1;
            }
        }
    }

    (void)dfs(map, minMap, row, col);   // 用例保证有唯一解

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            printf("%d", map[i][j]);
        }
        printf("\n");
    }    

    return 0;
}

