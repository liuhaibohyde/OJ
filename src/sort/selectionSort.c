/*
选出最小（或者最大）的一个数与第1个位置交换。然后在剩下的数中再找到最小（或者最大）的数与第2个位置交换……
*/

#include <stdio.h>

void Swap(int *a, int *b) 
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void SelectSort(int a[],int n){
    int i , j, min;
    for (i = 0; i < n - 1; i++){
        min = i;
        for (j = i + 1; j < n; j++) {   // 从i+1开始，选出最小的数
            if (a[j] < a[min]) {
                min = j;                // 记录下标
            }  
        }
        if (min != i) {
            Swap(&a[i], &a[min]);       // 最小的数与当前循环的第i个数交换
        }
    }
}

int main(char args, char* argv[])
{
    int a[10] = {12,85,25,16,34,23,49,95,25,12};
    SelectSort(a, 10);

    for (int i = 0; i < 10; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
    
    return 0;
}
