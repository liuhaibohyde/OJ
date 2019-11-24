# Sort库函数

### C++中的sort
```c++
#include <algorithm>

/*
参数1：第一个参数是数组的首地址，一般写上数组名就可以，因为数组名是一个指针常量。
参数2：第二个参数相对较好理解，即首地址加上数组的长度n（代表尾地址的下一地址）。
参数3：默认可以不填，如果不填sort会默认按数组升序排序。也可以自定义一个排序函数。
*/
sort(first_pointer,first_pointer+n,cmp)

// 使用标准库函数（不适用于结构体排序）
sort(begin, end, less<data-type>())     // 升序
sort(begin, end, greater<data-type>())  // 降序

// 自定义排序函数
bool compare(const int a, const int b) 
{
    return a < b;               // 升序
    return b < a;               // 降序
}

bool cmp2(const Student a, const Student b)
{
    return a.id < b.id;         // 升序
    return a.id > b.id;         // 降序
}

```

### C++优先级队列比较函数
```c++
#include <queue>

// 默认按照元素从大到小排列。即默认的int型队列中值大的优先级高，先出队
priority_queue<int> q;  

// 1、使用标准库函数（不适用于结构体）
priority_queue<int> q;                                  // 元素从大到小的顺序出队
priority_queue<int,vector<int>, greater<int> > q;       // 元素从小到大的顺序出队

// 2、自定义排序比较方法
struct cmp {     
　　operator bool ()(int x, int y)     
　　{        
　　　　 return　x > y;　　 // x小的优先级高，也可以写成其他方式，如： return p[x] > p[y]; 表示p[i]小的优先级高
　　}
};
priority_queue<int, vector<int>, cmp> q;    // 定义方法

struct node {     
　　int x, y;     
　　friend bool operator < (node a, node b)     
　　{         
　　　　return a.x > b.x;                   // 结构体中，x小的优先级高     
　　}
};
```

### C中的qsort
```c
#include <stdlib.h>

/*
base -- 指向要排序的数组的第一个元素的指针。
nitems -- 由 base 指向的数组中元素的个数。
size -- 数组中每个元素的大小，以字节为单位。
compar -- 用来比较两个元素的函数。
*/
void qsort(void *base, size_t nitems, size_t size, int (*compar)(const void *, const void*));

int compar(const void *p1, const void *p2)
{
    return ( *(int*)p1 - *(int*)p2 );      // 升序, 小于0升序，大于0降序
}

int values[] = { 88, 56, 100, 2, 25 };
qsort(values, 5, sizeof(int), compar);
```