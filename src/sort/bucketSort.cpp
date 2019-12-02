/* 桶排序 - 分而治之： 
将一个数据表分割成许多buckets，然后每个bucket各自排序，或用不同的排序算法，或者递归的使用bucket sort算法。 
也是典型的divide-and-conquer分而治之的策略。它是一个分布式的排序，当要被排序的数组内的数值是均匀分配的时候， 
桶排序时间复杂度是O(n)，桶排序并不是比较排序，他不受到 O(n log n) 下限的影响，稳定。

算法流程： 
1、建立一定数量的数组当作空桶； 
2、遍历原始数组，并将数据放入到对应的桶中； 
3、对非空的桶进行排序； 
4、按照顺序遍历这些非空的桶并放回到原始数组中即可构成排序后的数组。 
*/

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

using namespace std;

void bucketSort(int *arr, int length)
{
    if (arr == NULL || length <= 1) {
        return;
    }

    int max = arr[0];
    for (int i = 0; i < length; i++) {              // 找出数组中的最大值
        if (arr[i] > max)
        {
            max = arr[i];
        }
    }
    max++;                                          // max需要额外加1，作为存放最大值的那个桶

    int *bucket = (int *)malloc(sizeof(int) * max); // 申请桶空间
    if (bucket == NULL) {
        return;
    }
    memset(bucket, 0, sizeof(int) * max);

    for (int i = 0; i < length; i++) {              // 遍历数组，存入桶中并计数
        bucket[arr[i]] += 1;
    }

    for (int i = 0, j = 0; i < max; i++) {          // 对非空的桶按顺序输出
        while (bucket[i]-- > 0) {
            arr[j++] = i;
        }
    }

    free(bucket);
    return;
}

void printArr(int *arr, int length)
{
    for (int i = 0; i < length; i++) {
        printf("%d ", arr[i]);
    }
}

int main()
{
    int arr[] = {3, 5, 7, 2, 1, 0, 4, 65, 7, 89, 5, 3, 2, 5, 45, 3, 2, 54, 4, 543, 3, 33, 2, 34, 45, 5};
    int length = sizeof(arr) / sizeof(int);
    bucketSort(arr, length);
    printArr(arr, length);
    return 0;
}