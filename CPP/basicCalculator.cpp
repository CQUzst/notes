#include <iostream>
#include <string>
#include <stack>
using namespace std;
class Solution {
public:
    int calculate(string s) {
        int res = 0, sign = 1, n = s.size();
        stack<int> st;
        for (int i = 0; i < n; ++i) {//如果是空格，不处理，会自动进入下一个位置
            char c = s[i];
            if (c >= '0'&&c<='9') {
                int num = 0;
                while (i < n && s[i] >= '0') {
                    num = 10 * num + s[i++] - '0';//读入连续数字
                }
                res += sign * num;//加减算法
                --i;//while循环里多加的一次
            } else if (c == '+') {
                sign = 1;
            } else if (c == '-') {
                sign = -1;
                //如果遇到了左括号，则把当前结果res和符号sign压入栈，res重置为0，sign重置为1
            } else if (c == '(') {
                st.push(res);
                st.push(sign);
                res = 0;
                sign = 1;
                //如果遇到了右括号，结果res乘以栈顶的符号，就是括号左边的符号，出栈，前面的结果res加上栈顶的数字，出栈
            } else if (c == ')') {
                res *= st.top();
                st.pop();
                res += st.top();
                st.pop();
            }
        }
        return res;
    }
};
int main(){
    Solution s;
    int res;
    res=s.calculate("33-14");
    cout<<res<<endl;
    return 0;
}
