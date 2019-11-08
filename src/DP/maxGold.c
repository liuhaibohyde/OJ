#include <stdio.h>

const int max_mine = 100;           //程序最多的金矿数
const int max_people = 10000;       //程序最多的人数

int n;                              //金矿数
int peopleTotal;                    //总人数
int peopleNeed[max_mine];           //每座金矿需要的人数
int gold[max_mine];                 //每座金矿能够挖出的金子数
int maxGold[max_people][max_mine];  //保存前i个人挖前j个金矿能够得到的最大金子数，等于-1时表示未知

int max(int a, int b)
{
   return a > b ? a : b;
}

unsigned int init(const char* filePath)
{
   FILE* fp;
   int ret = fopen_s(&fp, filePath, "r");
   if (ret != 0 || fp == NULL) {
       printf("文件打开失败！\n");
       return -1;
   }

   fscanf_s(fp, "%d", &peopleTotal);           //第一行的总人数
   fscanf_s(fp, "%d", &n);                     //第一行的总金矿数

   for (int i = 0; i < n; ++i) {               //从第二行开始获取每一行中的金矿所需人数、金子数
       fscanf_s(fp, "%d", &peopleNeed[i]);
       fscanf_s(fp, "%d", &gold[i]);
   }

   for (int i = 0; i <= peopleTotal; i++) {    //注意这里人数<=
       for (int j = 0; j < n; j++) {
           maxGold[i][j] = -1;                 //初始化赋值-1，【动态规划中的备忘录】
       }
   }

   return 0;
}

int getMaxGold(int people, int mineNum)
{
   int retMaxGold;

   if (maxGold[people][mineNum] != -1) {       //直接用备忘录中的值
       retMaxGold = maxGold[people][mineNum];
   } else if (mineNum == 0) {                  //金矿数为0（只有一个金矿），边界
       if (people >= peopleNeed[mineNum]) {     //人数够，挖出这个金矿所有的金子
           retMaxGold = gold[mineNum];         
       } else {                                //人数不够，挖出0
           retMaxGold = 0;
       }
   } else if (people >= peopleNeed[mineNum]) { //人数足够开采这座金矿
       /* 考虑开采与不开采两种情况，取大的 */
       retMaxGold = max(getMaxGold(people - peopleNeed[mineNum], mineNum - 1) + gold[mineNum], getMaxGold(people, mineNum - 1));
   } else {                                    //仅考虑不开采
       retMaxGold = getMaxGold(people, mineNum - 1);
   }

   maxGold[people][mineNum] = retMaxGold;
   return retMaxGold;
}

int main(int argc, char* argv[])
{
   if (init("C:/Users/l00446406/Downloads/测试数据/beibao1.in")) {
       return -1;
   }

   int maxGoldNum = getMaxGold(peopleTotal, n - 1);    //注意编号从0开始，所以最后一个金矿的编号为n-1,人数不要-1，因为这里的人是数量，不是编号
   printf("总共可以挖到的最多金子数： %d", maxGoldNum); 

   int result[max_mine] = {0};
   for (int i = n-1; i >= 0; i--) {
       if (maxGold[peopleTotal][i] > maxGold[peopleTotal][i-1]) {  //注意金矿编号从0开始
           result[i] = 1;
           peopleTotal -= peopleNeed[i];
       }
   }

   for (int i = 0; i < n; i++) {
       if (result[i] == 1) {
           printf("\n金矿：%d", i);
       }
   }

   return 0;
}
