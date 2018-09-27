#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
int main(){
    string s;
    vector<int> res;
    while(cin>>s){
        if(s[0]=='0'&&s[1]=='x'){
            string ans=s.substr(2,s.size());
            reverse(ans.begin(),ans.end());
            int k=1;
            int sum=0;
            for(size_t i=0;i<ans.size();i++){
                int number=0;
                if(ans[i]<='9'&&ans[i]>='1'){
                    number=ans[i]-'0';
                }
                if(ans[i]<='F'&&ans[i]>='A'){
                    number=10+ans[i]-'A';
                }
                number*=k;
                sum+=number;
                 k*=16;
            }
            res.push_back(sum);
        }
    }
    for(size_t i=0;i<res.size();i++){
        cout<<res[i]<<endl;
    }
    return 0;
}
