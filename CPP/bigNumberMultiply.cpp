#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

//整数大数相乘
class intMultiply {
public:
    string multiply(string num1, string num2) {
        if(num1.empty() || num2.empty()) return "";
        int n1 = num1.size(),n2 = num2.size();
        reverse(num1.begin(),num1.end());//逆转字符串，从低位到高位开始算
        reverse(num2.begin(),num2.end());
        string res(n1+n2,'0');

        for(int i=0;i<n1;i++){//num1的每一位与num2的所有数相乘
            int carry=0;
            for(int j=0;j<n2;j++){
                carry+=(num1[i]-'0')*(num2[j]-'0')+res[i+j]-'0';//位相乘后加上位原本的值大小
                res[i+j]=carry%10+'0';//大于9要取余
                carry/=10;///10往下一位进位
            }
            if(carry) res[i+n2]=carry+'0';//num1的第i位和num2的所有位乘完如果有进位，则进位
        }
        reverse(res.begin(),res.end());

        size_t count=0;
        while( count< res.size()-1 && res[count] == '0') count++;//反转后清0
        res.erase(0,count);
        return res;
    }
}intmul;

//浮点大数乘法
class floatMultiply {
public:
    string multiply(string num1, string num2) {
        if(num1.empty() || num2.empty()) return "";
        int flag1=0;//num1小数的位数
        int flag2=0;//num2小数的位数
        reverse(num1.begin(),num1.end());//逆转字符串，从低位到高位
        reverse(num2.begin(),num2.end());
        for(size_t i=0;i<num1.size();i++){
            if(num1[i]=='.') {
                num1.erase(i,1);
                break;
            }
            flag1++;
        }
        for(size_t j=0;j<num2.size();j++){
            if(num2[j]=='.') {
                num2.erase(j,1);
                break;
            }
            flag2++;
        }
        int decimal=flag1+flag2;
        string res(num1.size()+num2.size(),'0');
        for(size_t i=0;i<num1.size();i++){
            int carry=0;
            for(size_t j=0;j<num2.size();j++){
                carry+=(num1[i]-'0')*(num2[j]-'0')+res[i+j]-'0';
                res[i+j]=carry%10+'0';
                carry/=10;
            }
            if(carry)
                res[i+num2.size()]=carry+'0';
        }
        string ss(".");
        res.insert(decimal,ss);
        size_t count = 0;
        while(count < res.size()-1 && res[count] == '0') count++;//清后面的0
        res.erase(0,count);

        reverse(res.begin(),res.end());

        count=0;
        while(count < res.size()-1 && res[count] == '0') count++;//清前面的0
        res.erase(0,count);

        if(res[0]=='.'){
            string zeroStart("0");
            res.insert(0,zeroStart);
        }
        return res;
    }
}floatmul;

int main(){
    string s1;
    int n;
    vector<string> res;
    while(cin>>s1>>n){
        string ans;
        ans=s1;
        n--;
        for(int i=0;i<n;i++){
            ans=floatmul.multiply(ans,s1);
        }
        res.push_back(ans);
    }
    for(size_t i=0;i<res.size();i++){
        cout<<res[i]<<endl;
    }
    return 0;
}
