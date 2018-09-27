#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main(){
    int n,x;
    while(cin>>n){
        vector<int> vec;
        while(n--){
            cin>>x;
            vec.push_back(x);
        }
        //unique()函数将重复的元素放到vector的尾部
        //然后返回指向第一个重复元素的迭代器 再用erase函数擦除从这个元素到最后元素的所有的元素
        sort(vec.begin(),vec.end());
        vec.erase(unique(vec.begin(), vec.end()), vec.end());
        for(size_t i=0;i<vec.size();i++)
            cout<<vec[i]<<endl;
    }
    return 0;
}
