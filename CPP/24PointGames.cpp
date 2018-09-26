#include <iostream>
#include<string>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    bool judgePoint24(vector<int>& nums) {
        bool res = false;

        vector<double> arr(nums.begin(), nums.end());//把整数都转成double类型方便做除法
        helper(arr, res);
        return res;
    }

    void helper(vector<double>& nums,bool& res) {//递归
        double eps = 0.0001;
        if (res) return;
        if (nums.size() == 1) {//只剩一个值说明是最终结果，判断是否在误差范围内，如果是24直接返回true
            if (abs(nums[0] - 24) < eps)
                res = true;
            return;
        }
        for (int i = 0; i < nums.size(); ++i) {
            for (int j = 0; j < i; ++j) {
                double p = nums[i], q = nums[j];//遍历任意两个数字，分别用p和q来取出
                vector<double> t{p + q, p - q, q - p, p * q};//然后进行两者的各种加减乘除的运算
                if (p > eps) t.push_back(q / p);//判断除数不为零
                if (q > eps) t.push_back(p / q);//将结果保存进数组临时数组t
                nums.erase(nums.begin() + i);//然后将原数组nums中的p和q移除
                nums.erase(nums.begin() + j);
                for (double d : t) {//遍历临时数组t中的数字，将其加入数组nums
                    nums.push_back(d);
                    helper(nums, res);//然后调用递归函数
                    nums.pop_back();//完成后要移除数字，恢复状态，这是递归解法的要点
                }
                nums.insert(nums.begin() + j, q);//最后还要把p和q再加回原数组nums，还原状态
                nums.insert(nums.begin() + i, p);
            }
        }
    }
}s;
int main()
{
    int A[4]={1,2,3,4};
    vector<int> nums(A,A+4);
    bool flag=s.judgePoint24(nums);
    cout<<flag<<endl;
    return 0;
}


