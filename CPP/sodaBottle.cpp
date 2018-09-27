#include <iostream>
#include <vector>
using namespace std;
int main(){
    vector<int> res;
    int n;
    while(cin>>n){
        if(n==0) break;
        int ans=0;
        while(n>2){
            ans+=n/3;
            n=n/3+n%3;
        }
        if(n==2)
            ans+=1;
        res.push_back(ans);
    }
    for(size_t i=0;i<res.size();i++)
        cout<<res[i]<<endl;
    return 0;
}
