/*
计数排序：输入序列中只有7个元素的值小于x的值，则x可以直接存放在输出序列的第8个位置上
*/

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

void CountSort(int *a, int length)
{
    int min = a[0];
    int max = a[0];
    
    for (int i = 0; i < length; i++) {              // 得到序列的最大、最小值
        max = a[i] > max ? a[i] : max;
        min = a[i] < min ? a[i] : min;
    }

    int range = max - min + 1;
    int *count = (int*)malloc(sizeof(int)*range);   // 辅助排序，存放计数结果
    if (count == NULL) {
        return;
    }
    memset(count, 0, sizeof(int)*range);

    for (int i = 0; i < length; i++) {              // 统计序列中每个元素出现的次数,count[i]表示第i个数有多少个
        count[a[i]-min]++;
    }

    int idx = 0;
    for (int i = 0; i < range; i++) {               // 挨个放回原数组中
        while (count[i] > 0) {                      // 同一位置有多个，一直顺序放回去
            a[idx++] = i + min;                     // i+min即原数组中本来的值
            count[i]--;
        }
    }

    free(count);
}

int main(){
    int a[] = {3,5,7,2,1,0,4,65,7,89,5,3,2,5,45,3,2,54,4,543,3,33,2,34,45,5};
    int length = sizeof(a)/sizeof(int);   

    CountSort(a, length);
    
    for (int i = 0; i < length; i++) {
        printf("%d ", a[i]);
    }

    return 0;
}
