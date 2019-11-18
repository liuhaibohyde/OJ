/*
线段树问题：只要能转化成对一些“连续点”的修改和统计问题，基本都可以用线段树来解决

翻硬币 ———— 每次翻转指定区间的硬币，随时查询某个区间内有多少正面朝上的硬币：
有N个硬币存放在桌面上，编号从0到N - 1，最初，每个硬币是反面朝上的。
你必须执行两种类型的操作：
1）翻转编号A和B（含）之间的所有硬币。这是通过命令“0 A B”实现。
2）回答在A和B（含）之间有多少硬币是正面朝上的。这是由命令“1 A B”表示。
 */
#include <stdio.h>
#include <memory.h>

#define MAX 100000
int num[MAX*4] = {0};
int lazy[MAX*4] = {0};

void PushUp(int root)
{
    num[root] = num[root << 1] + num[root << 1|1];
}

void build(int l, int r, int root)
{
    if (l == r) {
        num[root] = 1;
        return;
    }

    int mid = (l + r) / 2;
    build(l, mid, root*2);        // [l, mid]:左子树  [mid+1, r]:右子树
    build(mid + 1, r, root*2 + 1); 

    // 对于这个根节点root，先把左右子树都算出来了，再来更新它的值。
    // 沿路回溯：回溯到的点root，都是被 [la , rb] 或其子区间影响到的点，边回溯边更新
    PushUp(root);
} 

void PushDown(int root, int l, int r)
{
    if (lazy[root] == 0) {
        return;
    }

    lazy[root << 1] ^= lazy[root];      // 左右子树的lazy标记与父亲节点异或，因为连续翻两次相当于没翻
    lazy[root << 1|1] ^=  lazy[root];   // 其它情况根据问题的具体情况修改这里

    int mid = (l + r) / 2;
    num[root << 1] = mid - l + 1 - num[root << 1];
    num[root << 1|1] = r - mid - num[root << 1|1];

    lazy[root] = 0;
}

/* L,R为需要更新区间的左、右端点（递归时不会改变）
   l, r为当前区间的左、右端点（随递归改变）
   root为当前[l, r]的根存储位置（随递归改变） */
void Update(int L, int R, int l, int r, int root)
{
    if (L <= l && r <= R) {                     // 当前区间已经完全被包含在内，直接更新，并返回
        num[root] = (r - l + 1) - num[root];    // 翻面
        lazy[root] = 1 - lazy[root];            // lazy标记
        return;
    }

    PushDown(root, l, r);

    int mid = (l + r) / 2;
    if (L <= mid) {
        Update(L, R, l, mid, root << 1);
    }
    if (R > mid) {
        Update(L, R, mid + 1, r, root << 1|1);
    }

    PushUp(root);
}

int Query(int L, int R, int l, int r, int root)
{
    if (L <= l && r <= R) {
        return num[root];
    }

    PushDown(root, l, r);

    int mid = (l + r) / 2;
    int ans = 0;
    if (L <= mid) {
        ans += Query(L, R, l, mid, root << 1);
    }
    if (R > mid) {
        ans += Query(L, R, mid + 1, r, root << 1|1);
    }

    return ans;
}

int main()
{
    int t, n, q;
    scanf("%d", &t);      
    while (t--) {
        memset(num, 0, sizeof(num));
        memset(lazy, 0, sizeof(lazy));

        scanf("%d", &n);      // 翻硬币这里不需要build树，因为开始默认全部0
        scanf("%d", &q);
        for (int i = 0; i < q; i++) {
            int opr, l, r;
            scanf("%d", &opr);
            scanf("%d", &l);
            scanf("%d", &r);

            l += 1;             // 默认根节点是1，所以把题目的区间0~N-1 -> 1~N
            r += 1;

            if (opr) {
                printf("%d\n", Query(l, r, 1, n, 1));
            } else {
                Update(l, r, 1, n, 1);
            }
        }
    }

    return 0;
}
