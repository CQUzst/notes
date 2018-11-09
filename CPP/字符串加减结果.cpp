#include <iostream>
#include <string>
using namespace std;
int main(){
    string s;
    while(cin>>s){
        int num=0,res=0;
        int flag=1;
        for(size_t i=0;i<s.size();i++){
            if(s[i]=='+')
                flag=1;
            else if(s[i]=='-')
                flag=-1;
            else{
                while (isdigit(s[i])) {
                   num=num*10+s[i]-'0';
                   i++;
                }
                i--;
            }
            res+=flag*num;
            num=0;
        }
        cout<<res<<endl;
    }
    return 0;
}
