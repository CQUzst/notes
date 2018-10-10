#include <iostream>
#include <string>
using namespace std;

string longest(string &a,string &b)
{
    int max=0;
    int start;
    for(size_t i = 0; i < a.size(); i++){
        for(size_t j = 0; j < b.size(); j++){
            int num=0;
            int start1=i;
            int start2=j;
            while((start1 <a.size()) && (start2 <b.size()) &&(a[start1++]==b[start2++]))
                num++;
            if(num > max){
                max=num;
                start=i;
            }
        }
    }
    return a.substr(start,max);
}

int main()
{
    string a("abcdeeedde");
    string b("gfacceeedd");
    string res;
    res = longest(a,b);
    cout<<res;
    return 0;
}
