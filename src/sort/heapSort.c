/*
1、初始化堆（大根堆）：根节点最大，左右子树均小于根节点
2、排序：
        a. 将堆顶的节点a[0]（当前最大值）与 最后一个节点a[n-1] 交换，保证了a[n-1]的值为最大值
        b. 对剩下的a[0]-a[n-2]重新构造大根堆，再交换a[0] 和 a[n-2]，a[n-2]为次大值
        c. 重复a，b步骤，直到最后一个元素
*/

#include <stdio.h>

void Swap(int *a, int *b) 
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

/*************************** 堆排序一 ****************************/
// 大根堆调整
void MaxHeapify(int *a, int n, int i)       // n：堆的节点个数
{
    int l = 2 * i + 1;      // 左子节点
    int r = 2 * i + 2;      // 右子节点
    int max = i;

    if (l < n && a[l] > a[i]) {             // 左右子节点中，找到较大的值，记录下标max
        max = l; 
    }
    if (r < n && a[r] > a[max]) {   
        max = r;
    }

    if (max != i) {                     
        Swap(&a[max], &a[i]);               // 交换 自己 和 儿子节点中值较大的那个
        MaxHeapify(a, n, max);              // 交换后，需要对被交换的子节点重新调整大根堆
    }
}

// 创建大根堆
void CreateMaxHeap(int *a, int n)           // n：数组元素个数
{
    for (int i = n/2 - 1; i >= 0; i--) {    // 从倒数第二层开始，即从有子节点的那一层开始 
        MaxHeapify(a, n, i);
    }
}

// 排序
void HeapSort(int *a, int n)
{
    CreateMaxHeap(a, n);

    for (int i = n - 1; i > 0; i--){        // 从最后一个节点开始对堆进行调整
        Swap(&a[i], &a[0]);                 // 与根节点交换，保证当前数组最后一个a[n-1]的值最大
        MaxHeapify(a, i, 0);                // 生成一个新的包含前 n-1 个节点的大根堆，最后一个节点已经确认是最大值（排好序了）
    }    
}

int main(char args, char* argv[])
{
    int a[10] = {12,85,25,16,34,23,49,95,17,61};
    HeapSort(a, 10);

    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    
    return 0;
}
