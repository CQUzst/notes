#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    int a,b;
    char sep;
    vector<pair<int,int>>couple;
    vector<pair<int,int>>res;
    while(cin>>a>>sep>>b){
        couple.push_back({a,b});
    }
    if(couple.size()==0)
        return 0;
    sort(couple.begin(),couple.end());
    int left=couple.begin()->first,right=couple.begin()->second;
    for(int i=1;i<couple.size();i++){
        if(couple[i].first>right){
            res.push_back({left,right});
            left=couple[i].first;
            right=couple[i].second;
        }
        else
            right=max(right,couple[i].second);
    }
    res.push_back({left,right});
    for(int i=0;i<res.size()-1;i++)
        cout<<res[i].first<<","<<res[i].second<<" ";
    cout<<res[res.size()-1].first<<","<<res[res.size()-1].second;
    return 0;
}
