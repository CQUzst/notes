#include <iostream>
#include <string>

using namespace std;
class Solution {
public:
    string countAndSay(int n) {
        if(n == 1) return "1";
        else if(n == 2) return "11";
        string next(""), prev = countAndSay(n - 1);
        int num=1;
        for(int i=0;i<prev.size();i++){
            if(prev[i]==prev[i+1]) num++;
            else {
                next+=to_string(num)+prev[i];
                num=1;
            }
        }
        return next;
//        for(size_t i=0; i < prev.length(); ++i) {
//            int num = 1;
//            if(prev[i]==prev[i+1]) ++num;
//            else next+=to_string(num) + prev[i];
//        }
//        return next;
    }
};
int main(){
    Solution s;
    int n=8;
    s.countAndSay(n);
    return 0;
}
