/*
大数沉底，没啥好说的
*/

#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) 
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void BubbleSort(int *arr, int size)  
{  
    int i, j, tmp;  
    for (i = 0; i < size - 1; i++) {  
        for (j = 0; j < size - i - 1; j++) {  
            if (arr[j] > arr[j+1]) {  
                tmp = arr[j];  
                arr[j] = arr[j+1];  
                arr[j+1] = tmp;  
            }  
        }  
    }  
}  

//鸡尾酒排序
/*
冒泡排序的改进 - 鸡尾酒排序，排序时以首尾双向在序列中进行排序
1、先对数组从左到右进行升序的冒泡排序；
2、再对数组进行从右到左的降序的冒泡排序；
3、以此类推，持续的、依次的改变冒泡的方向，并不断缩小没有排序的数组范围；
*/
void CocktailSort(int a[], int n){
    int left = 0, right=n-1;
    while(left<right){
        for(int i=left;i<right-1;i++){       //从前往后排
            if(a[i]>a[i+1]){
                Swap(a[i],a[i+1]);
            }           
            right-=1;
            for(int j=right;j>left;j--){     //从后往前排
                if(a[j]<a[j-1]){
                    Swap(a[j],a[j-1]);
                }
            }
            left+=1;
        }
    }    
}

int main(){
    int a[] = {3,5,7,2,1,0,4,65,7,89,5,3,2,5,45,3,2,54,4,543,3,33,2,34,45,5};
    int length = sizeof(a)/sizeof(int);   

    BubbleSort(a, length);
    
    for (int i = 0; i < length; i++) {
        printf("%d ", a[i]);
    }

    return 0;
}
