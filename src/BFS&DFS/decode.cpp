/*
字符串编码：
    1、源字符与目标字符之间是多对多的关系
    2、将源字符串拆解，根据转换规则找出所有的目标字符串（目标字符串相同的记做一个）
    3、将所有目标字符串按照字典序排序，输出给定目标字符串的位置index

输入样例：
123 bccd
12 a
1 b
1 ab
2 c
1 bc
3 d
23 e
4 a
输出：
4

解析：
将123通过映射表可转换为ad bcd be abcd abe bccd bce共7个目标字符串，按字典排序后为abcd abe ad bccd bcd bce be，
待查目标字符串bccd是其中的第4个，输出为4
*/

#include <stdio.h>
#include <iostream>
#include <map>
#include <set>
#include <string>

using namespace std;

void Decode(multimap<string, string>& rules, set<string>& out, string dest, string src, int idx)
{
    if (idx > src.length()) {
        return;
    }
    if (idx == src.length()) {                          // 源字符串已遍历完，dest存入结果中，退出
        out.insert(dest);
        return;
    }
    
    for (int i = 1; i <= (src.length() - idx); i++) {   // idx初始为0，
        string str = src.substr(idx, i);                // 遍历源字符串的所有组合
        auto begin = rules.lower_bound(str);            // 查找转换规则中匹配的所有源字符串
        auto end = rules.upper_bound(str);
        for (auto it = begin; it != end; it++) {
            Decode(rules, out, dest + it->second, src, idx + i);    // 递归，dest不断累加
        }
    }
}

int main()
{
    string src, dest;
    cin >> src >> dest;
    
    string subSrc, subDest;
    multimap<string, string> rules;         // 转换规则，多对多
    while (cin >> subSrc >> subDest) {
        rules.insert(pair<string, string>(subSrc, subDest));
    }

    set<string> out;
    Decode(rules, out, "", src, 0);

    int ans = 1;
    bool flag = false;
    for (auto iter : out) {
        if (iter == dest) {
            flag = true;
            break;
        }
        ++ans;
    }

    cout << (flag ? ans : -1) << endl;
    return 0;
}
