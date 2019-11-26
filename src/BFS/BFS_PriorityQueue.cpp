/*
坦克从其实位置走到目标位置，要求所有步数最少，求所用的步数
地图上有河流（不可走），墙壁、铁块需要额外消耗步数
*/

#include <iostream>
#include <vector>
#include <queue>
#include <string>
using namespace std;

#define CONTINUE_IF(expr)   \
{                           \
    if (expr) {             \
        continue;           \
    }                       \
}

typedef struct {
    int x;
    int y;
}Location;

struct tank{
    int x, y, stp;
    friend bool operator < (const tank &a, const tank &b) { 
        return a.stp > b.stp;                                  // 小顶堆，值小的优先出队
    }
};

int moveX[] = {0, 0, -1, 1};
int moveY[] = {1, -1, 0, 0};

int bfs(int R, int C, vector<vector<char>> a, Location start)
{
    vector<vector<char>> visited(R, vector<char>(C, 0));
    visited[start.x][start.y] = 1;      // 已访问过
    
    priority_queue<tank> path;
    tank move = {start.x, start.y, 0};  // 初始状态
    path.push(move);

    while (!path.empty()) {
        move = path.top();              // 访问优先级最高的元素，即步数最少的
        path.pop();

        if (a[move.x][move.y] == '1') {
            return move.stp;
        }

        tank next;
        for (int i = 0; i < 4; i++) {
            next.x = move.x + moveX[i];
            next.y = move.y + moveY[i];

            CONTINUE_IF(next.x < 0 || next.y < 0 || next.x >= R || next.y >= C);
            CONTINUE_IF(a[next.x][next.y] == 'r' || visited[next.x][next.y]);
            
            if (a[next.x][next.y] == 'b') {
                next.stp = move.stp + 2;
            } else if (a[next.x][next.y] == 's') {
                next.stp = move.stp + 3;
            } else {
                next.stp = move.stp + 1;
            }
            
            visited[next.x][next.y] = 1;      // 已访问过
            path.push(next);
        }
    }

    return -1;
}

int main()
{   
    int N;
    while (cin >> N) {
        int R, C;
        cin >> R >> C;

        Location start;
        vector<vector<char>> a(R, vector<char>(C, 0));
        for (int i = 0; i < R; i++) {
            string tmp;
            cin >> tmp;
            for (int j = 0; j < C; j++) {
                a[i][j] = tmp[j];
                if (tmp[j] == '0') {
                    start.x = i;
                    start.y = j;
                } 
            }
        }

        cout << bfs(R, C, a, start) << endl; 
        
    }

    return 0;
}
