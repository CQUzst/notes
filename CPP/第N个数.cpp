#include <iostream>
#include <string>
using namespace std;
//个位数：1-9，一共9个,共计9个数字
//2位数：10-99,一共90个，共计180个数字
//3位数：100-999，一共900个，共计2700个数字
//4位数，1000-9999，一共9000个，共计36000个数字
//以此类推,这样我们就可以首先定位到是哪个数，再找到其对应的数字

class Solution {
public:
    int findNthDigit(int n) {
        long digitType = 1;
        long base = 9;
        long ith =1;
        //定位到是几位数
        while (n> base*digitType ) {
            n-=base *digitType ;
            digitType +=1;
            ith += base;
            base = base*10;
        }
        //定位到是这些几位数里面的第indexInSubRange个的第index位
        int indexRange=(n-1)/digitType;
        int index = (n -1) % digitType;
        string s=to_string(ith+indexRange);
        return s[index]-'0';
    }
};
int main(){
    Solution s;
    cout<<s.findNthDigit(1111);
    return 0;
}
