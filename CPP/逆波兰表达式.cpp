#include <iostream>
#include <string>
#include <vector>
#include <stack>
using namespace std;

class Solution {
private:
    stack <string> st;
    void calc(stack <string> &st,string token){
        string num1=st.top();st.pop();
        string num2=st.top();st.pop();

        string temp;
        //std::stoi(tokens[i], nullptr, 10);
        int b = atoi(num1.c_str());
        int a = atoi(num2.c_str());
        if(token=="+")
            temp=to_string(a+b);
        else if(token=="-")
            temp=to_string(a-b);
        else if(token=="*")
            temp=to_string(a*b);
        else if(token=="/")
            temp=to_string(a/b);
        st.push(temp);
    }
public:
    int evalRPN(vector<string>& tokens) {
        int res=0;
        for(size_t i=0;i<tokens.size();i++){
            if(tokens[i]=="+"||tokens[i]=="-"||tokens[i]=="*"||tokens[i]=="/"){
                calc(st,tokens[i]);
            }
            else
                st.push(tokens[i]);
        }
        cout<<st.top()<<endl;
        res=atoi(st.top().c_str());
        return res;
    }
};
int main(){
    vector<string> vec;
    vec.push_back("4");
    vec.push_back("3");
    vec.push_back("1");
    vec.push_back("-");
    vec.push_back("+");
    Solution s;
    s.evalRPN(vec);
    return 0;
}
