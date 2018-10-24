#include <iostream>
#include <vector>
using namespace std;
class Solution {
public:
    vector<vector<string> > solveNQueens(int n) {
        vector<vector<string> > res;
        vector<string>cur(n, string(n,'.'));
        helper(cur, 0,res);
        for(size_t i=0;i<res.size();i++){
            for(size_t j=0;j<res[i].size();j++){
                cout<<res[i][j]<<endl;
            }
            cout<<endl;
        }
        return res;
    }
    void helper(vector<string> &cur, int row,vector<vector<string> > &res)
    {
        if(row == cur.size())//N个皇后已经摆好
        {
            res.push_back(cur);//返回一个解
            return;
        }
        for(int col = 0; col < cur.size(); col++)//逐次尝试第k个皇后的位置
            if(isValid(cur, row, col)){//位置合法就进行下一层放置
                cur[row][col] = 'Q';
                helper(cur, row+1,res);
                cur[row][col] = '.';//递归的精髓，进入下一层递归前的变动要返回原状
            }
    }
    bool isValid(vector<string> &cur, int row, int col)
    {
        //排除列重复
        for(int i = 0; i < row; i++)
            if(cur[i][col] == 'Q')return false;
        //右对角线(只需要判断对角线上半部分，因为后面的行还没有开始放置)往右上
        for(int i = row-1, j=col-1; i >= 0 && j >= 0; i--,j--)
            if(cur[i][j] == 'Q')return false;
        //左对角线(只需要判断对角线上半部分，因为后面的行还没有开始放置)往左上
        for(int i = row-1, j=col+1; i >= 0 && j < cur.size(); i--,j++)
            if(cur[i][j] == 'Q')return false;
        return true;
    }
};
int main(){
    Solution s;
    int n=4;
    s.solveNQueens(n);
    return 0;
}

