#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    int N = 12;//2的N次方是超过基本数据类型所能表达的范围

    vector<int> result;//使用vector来保存结果，这里可以使用char来保存
    result.push_back(1);//首先起始为1
    vector<int>::iterator it;//定义迭代器

    for (int i = 1; i <= N; i++)
    {
        for (it = result.begin(); it != result.end(); it++)//所得每一位*2
        {
            *it = (*it) * 2;
        }
        for (size_t i = 0; i < result.size(); i++)//判断每一位
        {
            if (result[i] > 9)//如果该为>=10
            {
                if (i == result.size() - 1)//如果是最高位
                {
                    result.push_back(result[i] / 10);//增加一位
                }
                else
                {
                    result[i + 1] += result[i] / 10;//进位
                }
                result[i] %= 10;//进位之后本位处理
            }
        }
    }
    reverse(result.begin(),result.end());
    for(int i=0;i<result.size();i++)
        cout<<result[i];
//    for (int i = result.size() - 1; i > -1; i--)//存储和自然读数顺序相反
//    {
//        cout << result[i];
//    }
//    cout << endl;

    return 0;
}
