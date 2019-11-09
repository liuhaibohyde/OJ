/*
将待排序数列看成是一个仅含有一个元素的有序数列和一个无序数列，将无序数列中的元素逐次插入到有序数列中，从而获得最终的有序数列。
*/

void swap(int *a, int *b) 
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

// 直接插入法一
void InsertSort1(int a[], int n)
{
    int j;
    for (int i = 1; i < n; i++) {                               // 从第二个数开始
        if (a[i] < a[i - 1]) {
            int temp = a[i];                                    // 保存要比较的值
            for(j = i - 1; j >= 0 && a[j] > temp; j--) {        // 从后向前查找待插入位置
                a[j + 1] = a[j];                                // 挪位
            }  
            a[j + 1] = temp;                                    // 复制到插入位置
        }
    }
}

// 直接插入法二：用数据交换代替法一的数据后移(比较对象只考虑两个元素)
void InsertSort2(int a[], int n)
{
    for (int i = 1; i < n; i++) {                               // 从第二个数开始
        for(int j = i - 1; j >= 0 && a[j] > a[j + 1]; j--) {    // 从i-1开始往前，不停的交换数据，直到找到小于这个数的插入位置
            swap(&a[j], &a[j + 1]);
        }
    }
}

int main(char args, char* argv[])
{
    int a[10] = {12,85,25,16,34,23,49,95,25,12};
    InsertSort2(a, 10);

    for (int i = 0; i < 10; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
    
    return 0;
}
