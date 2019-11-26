# OJ

### 排序

1. [C/C++中排序相关库函数](src/sort/sort.md)
2. [只交换相邻两数，使序列升序排列，求出最少交换次数](src/sort/miniSwapCount1.cpp)
3. [交换任意两个位置元素，是序列升序，求最少交换次数](src/sort/miniSwapCount2.cpp)

|               排序算法               | 平均时间 | 最好时间 | 最坏时间 |  空间   | 稳定度 |             备注              |
| :----------------------------------: | :------: | :------: | :------: | :-----: | :----: | :---------------------------: |
|   [快速排序](src/sort/quickSort.c)   | O(nlogn) | O(nlogn) |  O(n2)   | O(logn) | 不稳定 | n较大时较好（最坏蜕变为冒泡） |
|    [堆排序](src/sort/heapSort.c)     | O(nlogn) | O(nlogn) | O(nlogn) |  O(1)   | 不稳定 |          n较大时较好          |
|   [归并排序](src/sort/mergeSort.c)   | O(nlogn) | O(nlogn) | O(nlogn) |  O(n)   |  稳定  |          n较大时较好          |
|  [冒泡排序](src/sort/bubbleSort.c)   |  O(n2)   |  O(n2)   |   O(n)   |  O(1)   |  稳定  |   n较小时较好（一般不推荐）   |
| [直接插入](src/sort/InsertionSort.c) |  O(n2)   |  O(n2)   |   O(n)   |  O(1)   |  稳定  |      大部分已排序时较好       |
| [直接选择](src/sort/selectionSort.c) |  O(n2)   |  O(n2)   |  O(n2)   |  O(1)   | 不稳定 |          n较小时较好          |

### DP
1. [挖金矿：每个金矿金子数不同，需要不同数量工人，给定工人挖出最多金子](src/DP/maxGold.c)
2. [01背包：给定总钱数、物品个数，每个物品有价格、重要度，求能达到的最大价值](src/DP/maxValue.cpp)

### 数位DP
1. [不包含指定的一位数字，一维DP数组记录状态](src/DigitDp/simple1D.c)
2. [不包含指定的两位数，二维DP数组记录状态](src/DigitDp/continuousNum2D.cpp)

### BFS
1. [基础BFS，地图上规定步数内能否走到某一点](src/BFS/simpleBFS.cpp)
2. [BFS+优先队列，地图上到达目标点所用最少步数](src/BFS/BFS_PriorityQueue.cpp)

### DFS
1. [数独游戏](src/DFS/sudoku.cpp)
2. [最短路径，红蓝颜色交替有向图](src/DFS/shortestAlternatingPaths.cpp)

### 并查集
1. [带权值，判断区间权值：给出n个区间奇偶，求第几个区间开始与前面已知条件矛盾](src/DSU/rangeOddOrEven.cpp)
2. [带权值，是否同组：n个人分两组，每个条件给出两个人是一组或不是一组](src/DSU/whichTeamAB.cpp)
3. [图的连通性，二维网络上01相间(也可以DFS,BFS)](src/DSU/islandsNum.cpp)

### 贪心
1. [优势洗牌，两个等长度数组，使A[i]>B[i]的数量最多](src/greedy/advantageCount.cpp)
2. [贪心+优先队列，到达终点需要最少加油次数](src/greedy/miniFuelStop.cpp)

### 算法应用
1. [stack堆栈，简单四则运算的变形，运算符$，#，优先级$高于#](src/Algorithm/simpleArithmetic.c)
2. [拓扑排序，给出n个关系A<B,B<C,C<D……最快确定A-D的关系](src/Algorithm/topologySort.cpp)
3. [二进制枚举，10个数分两组，它们的和相差最小](src/Algorithm/binaryEnumeration.c)
4. [multimap应用，多对多字符串编码问题](src/Algorithm/decode.cpp)
5. [线段树，对区间内的硬币反面，查询不同区间内硬币正面朝上](src/Algorithm/segementTree.cpp)
6. [多少个连续子区间的和大于给定的数](src/Algorithm/continuousSumNum.cpp)