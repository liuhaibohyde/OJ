/*
归并排序：将两个有序数列合并成一个有序数列，分治策略
*/

#include<stdio.h>
#include<stdlib.h>

void MergeArray(int *a, int* tmp, int l, int r, int end)    // l:左序列起点下标，r:右序列起点下标，end:右序列终点下标
{
    int lEnd = r - 1;                       // 左序列终点下标
    int num = end -l + 1;

    int p = l;
    while (l <= lEnd && r <= end) {         // 先合并两个子区间都包含的最短区间长度元素，存入tmp中
        if (a[l] <= a[r]) {
            tmp[p++] = a[l++];
        } else {
            tmp[p++] = a[r++];
        }
    }

    while (l <= lEnd) {                     // 左区间剩余元素
        tmp[p++] = a[l++];
    }
    while (r <= end) {                      // 右区间剩余元素
        tmp[p++] = a[r++];
    }

    for (int i = 0; i < num; i++, end--) {  // 不一定是从0开始，注意
        a[end] = tmp[end];
    }
}

void MergeSort(int *a, int *tmp, int l, int r)
{
    if (l >= r) {
        return;
    }

    int mid = l + (r - l)/2;
    MergeSort(a, tmp, l, mid);          // 递归排序左、右两个子区间
    MergeSort(a, tmp, mid+1, r);
    MergeArray(a, tmp, l, mid+1, r);    // 合并两个有序子区间
}

int main(){
    int a[10] = {3,5,2,10,8,9,6,4,7,1};
    int length = sizeof(a) / sizeof(a[0]);

    int *tmp = (int*)malloc(length * sizeof(int));    // 需要申请另外一个相同大小的空间
    if (tmp == NULL) {
        return -1;
    }
    
    MergeSort(a, tmp, 0, length-1);
    
    for (int i = 0; i < length; i++) {
        printf("%d ", a[i]);
    }

    free(tmp);
    tmp = NULL;
    return 0;
}
