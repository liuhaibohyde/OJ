/*
快速排序 - 分治思想
1、先从数列中取出一个数作为轴值（基准数）pivot
2、根据基准数将数列进行分区，小于基准数的放左边，大于基准数的放右边
3、重复第二步的分区操作（递归），直到每个区间只有一个数为止
*/

#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) 
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void quickSort(int *a, int low, int high)
{
    int i = low;
    int j = high;
    int tmp = a[i];

    if (low > high) {
        return;
    }

    while (i < j) {
        while (a[j] >= tmp && i < j) {      // 从右向左找第一个小于tmp的数
            j--;
        }
        a[i] = a[j];
        while (a[i] < tmp && i < j) {       // 从左向右找第一个大于tmp的数
            i++;
        }
        a[j] = a[i];
    }
    a[i] = tmp;
    quickSort(a, low, i-1);
    quickSort(a, j+1, high);
}

int main(char args, char* argv[])
{
    int a[10] = {12,85,25,16,34,23,49,95,17,61};
    quickSort(a, 0, 9);

    for (int i = 0; i < 10; i++) {
        printf("%d, ", a[i]);
    }
    printf("\n");
    
    return 0;
}
