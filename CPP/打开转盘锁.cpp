#include<iostream>
#include<algorithm>
#include <string>
#include <vector>
#include <unordered_set>
#include <queue>
using namespace std;
class Solution {
public:
    int openLock(vector<string>& deadends, string target) {
        //本质就是个迷宫遍历的问题，只不过相邻位置不再是上下左右四个位置，
        //而是四位数字每个都加一减一，总共有八个相邻的位置，用广度优先遍历BFS
        int res = 0;
        unordered_set<string> deadlock(deadends.begin(), deadends.end());
        if (deadlock.count("0000")) return -1;//deadlock里面有0000，直接返回-1
        unordered_set<string> visited{{"0000"}};
        queue<string> q{{"0000"}};
        while (!q.empty()) {
            ++res;//用res来记录BFS遍历的层数
            //遍历上一次q栈中的值，依次取出，求周围八个位置
            for (int k = q.size(); k > 0; --k) {
                auto t = q.front(); q.pop();
                //遍历四位数字的每一位，然后分别加1减1，我们用j从-1遍历到1，遇到0跳过，也就是实现了加1减1的过程
                for (int i = 0; i < 4; ++i) {
                    for (int j = -1; j <= 1; ++j) {
                        if (j == 0) continue;
                        string str = t;
                        //为了处理9加1变0，和0减1变9的情况
                        //我们统一给该位数字加上个10，然后再加或减1，最后再对10取余即可
                        str[i] = ((t[i] - '0') + 10 + j) % 10 + '0';
                        //如果此时新生成的字符串等于target了，直接返回结果res
                        if (str == target) return res;
                        //如果该字符串不在死锁集合里，且之前没有遍历过（避免重复遍历），加入队列queue中，进入下一层搜索
                        if (!visited.count(str) && !deadlock.count(str))
                            q.push(str);
                        //再将该字符串加入visited集合中
                        visited.insert(str);
                    }
                }
            }
        }
        return -1;
    }
}s;
int main()
{
    string str[]={"0201","0101","0102","1212","2002"};

    vector<string>deadends(str,str+5);
    string target("0202");
    s.openLock(deadends,target);
    return 0;
}
