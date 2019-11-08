#include<stdio.h> 
#include<queue>
#include<vector>
#include<iostream>

using namespace std;

/*
Description
     规定天数内救出公主：
     每组测试数据以三个整数N,M,T(0<n, m≤20, t>0)开头，分别代表迷宫的长和高，以及公主能坚持的天数。
     紧接着有M行，N列字符，由"."，"*"，"P"，"S"组成。其中 "." 代表能够行走的空地。 "*" 代表墙壁，Jesse不能从此通过。
     "P" 是公主所在的位置。 "S" 是Jesse的起始位置。 每个时间段里Jesse只能选择“上、下、左、右”任意一方向走一步。
Prototype
     int SSaveP (int *visited, int M, int n, int t)
Input Param
     M               迷宫（数组）行数
     N               迷宫（数组）列数
     T               公主能坚持的天数
Output Param
                     无
Return Value
     0         可以救出公主
     -1        不可以救出公主
*/

typedef struct {
    int x;
    int y;
}Location;

// 上、下、左、右
int stepX[4] = { 0, 0, 1, -1 };
int stepY[4] = { 1, -1, 0, 0 };

int bfs(char* visited, int t, int n, int m, queue<Location> path, vector<vector<int>> dis)
{
    while (!path.empty()) {
        Location curr = path.front();
        path.pop();

        for (int i = 0; i < 4; i++) {
            Location next;
            next.x = curr.x + stepX[i];
            next.y = curr.y + stepY[i];

            if (next.x < 0 || next.x >= m || next.y < 0 || next.y >= n || dis[curr.x][curr.y] > t) {
                continue;
            }

            if (*(visited + next.x * n + next.y) == '*' || *(visited + next.x * n + next.y) == 'S') {
                continue;
            }

            if (dis[next.x][next.y] == -1) {
                dis[next.x][next.y] = dis[curr.x][curr.y] + 1;
                path.push(next);
                if (*(visited + next.x * n + next.y) == 'P') {
                    if (dis[next.x][next.y] <= t) {
                        return 0;
                    } else {
                        return -1;
                    }
                }
            }
        }
    }

    return -1;
}

int SSavep(char* visited, int t, int n, int m)
{
    Location p = { -1, -1 };
    Location s = { -1, -1 };
    queue<Location> path;
    vector<vector<int>> dis(m, vector<int>(n, -1));

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (*(visited + i * n + j) == 'P') {
                p.x = i;
                p.y = j;
            } else if (*(visited + i * n + j) == 'S') {
                s.x = i;
                s.y = j;
                dis[i][j] = 0;
                path.push(s);       // 起点push到队列中，作为访问开始节点
            }
        }
        cout << endl;
    }

    if (p.x == -1 || p.y == -1 || s.x == -1 || s.y == -1) {
        return -1;
    }
    
    return bfs(visited, t, n, m, path, dis);
}

int main()
{
	int N = 4;
	int M = 4; 
	int T = 10;
	char a[4][4] = {'.', '.', '.','.', 
                    '.', '.', '.', '.', 
                    '.', '.', '.', '.',
                    'S', '*', '*','P'};
    char *p = &a[0][0];
	int  Ret;

	Ret = SSavep(p, T, N, M);

    return 0;
}
