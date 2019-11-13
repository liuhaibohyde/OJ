# OJ

### 排序
|               排序算法               | 平均时间 |  空间   | 稳定度 |             备注              |
| :----------------------------------: | :------: | :-----: | :----: | :---------------------------: |
|   [快速排序](src/sort/quickSort.c)   | O(nlogn) | O(logn) | 不稳定 | n较大时较好（最坏蜕变为冒泡） |
|    [堆排序](src/sort/heapSort.c)     | O(nlogn) |  O(1)   | 不稳定 |          n较大时较好          |
|   [归并排序](src/sort/mergeSort.c)   | O(nlogn) |  O(n)   |  稳定  |          n较大时较好          |
|  [冒泡排序](src/sort/bubbleSort.c)   |  O(n2)   |  O(1)   |  稳定  |   n较小时较好（一般不推荐）   |
| [直接插入](src/sort/InsertionSort.c) |  O(n2)   |  O(1)   |  稳定  |      大部分已排序时较好       |
| [直接选择](src/sort/selectionSort.c) |  O(n2)   |  O(1)   | 不稳定 |          n较小时较好          |
|   [计数排序](src/sort/countSort.c)   |  O(n+k)  | O(n+k)  |  稳定  |  优于比较排序，0~k为数值范围  |

### DP
1. [每个金矿金子数不同，需要不同数量工人，给定工人挖出最多金子](src/DP/maxGold.c)
2. [给定总钱数、物品个数，每个物品有价格、重要度，求能达到的最大价值](src/DP/maxValue.cpp)

### 数位DP
1. [不包含指定的一位数字，一维DP数组记录状态](src/DigitDp/simple1D.c)
2. [不包含指定的两位数，二维DP数组记录状态](src/DigitDp/continuousNum2D.cpp)

### BFS
1. [基础BFS，地图上规定步数内能否走到某一点](src/BFS/simpleBFS.cpp)
2. [BFS+优先队列，地图上到达目标点所用最少步数](src/BFS/BFS_PriorityQueue.cpp)

### Stack
1. [简单四则运算的变形，运算符$，#，优先级$高于#](src/stack/simpleArithmetic.c)

### 算法应用
1. [拓扑排序，给出n个关系A<B,B<C,C<D……最快确定A-D的关系](src/Algorithm/topologySort.cpp)
2. [二进制枚举，10个数分两组，它们的和相差最小](src/Algorithm/binaryEnumeration.c)
3. [并查集（带权值）：给出n个区间的奇偶，求第几个区间开始与前面已知条件矛盾](src/Algorithm/unionFind.cpp)
