#include <iostream>
#include <string>
using namespace std;
int main(){
    string s;
    //dBowNgxyPZXZXlBTMKFskExQEK
    while(cin>>s){
        int a[126]={0};
        string res("");
        for(int i=0;i<s.size();i++) {
            if(a[s[i]]>=1) continue;
            a[s[i]]++;
        }
        for(int i=0;i<s.size();i++){
            if(--a[s[i]]==0) res+=s[i];
        }
        cout<<res<<endl;
    }
}
////¹þÏ£±í
//#include<iostream>
//#include<string>
//#include<map>
//using namespace std;
//int main(){
//    string s;
//    while(cin>>s){
//        string res;
//        map<char,int> cnt;
//        for(int i=0;i<s.size();i++){
//            if(cnt[s[i]]==0){
//                cnt[s[i]]++;
//                res+=s[i];
//            }
//        }
//        cout<<res<<endl;
//    }
//}
