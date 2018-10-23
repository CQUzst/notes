#include <iostream>
#include <algorithm>
using namespace std;
//有一个数组a[N]顺序存放0~N-1，要求每隔两个数删掉一个数，到末尾时循环至开头继续进行，
//求最后一个被删掉的数的原始下标位置。以8个数(N=7)为例:｛0，1，2，3，4，5，6，7｝，
//0->1->2(删除)->3->4->5(删除)->6->7->0(删除),如此循环直到最后一个数被删除。
//输出描述：每组数据为一行一个整数n(小于等于1000)，为数组成员数,如果大于1000，则对a[999]进行计算。
//输入描述：一行输出最后一个被删掉的数的原始下标位置
int main(){
    int n=0;
    while(cin>>n){
        if(n>1000)n=999;
        int a[n];
        for(size_t i=0;i<n;i++) a[i]=i;
        int deleteNumber=0;
        int res=0;
        int cnt=2;
        while (deleteNumber!=n){
            for(size_t j=0;j<n;j++){
                if(a[j]==-1)continue;
                if(cnt>0) {
                    cnt--;
                    continue;
                }
                if(cnt==0) {
                    a[j]=-1;
                    deleteNumber++;
                    res=j;
                    cnt=2;
                }
            }
        }
        cout<<res<<endl;
    }
    return 0;
}
