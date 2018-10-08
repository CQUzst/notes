#include <iostream>
#include <string>
#include <algorithm>
#include <set>
#include <map>
#include <unordered_map>
using namespace std;

class Solution {
public:
    int numMagicSquaresInside(vector<vector<int>>& grid) {
        int rows=grid.size(),cols=grid[0].size();
        int res=0;
        for(int row=0;row<rows-2;row++){
            for(int col=0;col<cols-2;col++){
               if(isMagicSquares(grid,row,col))
                   res++;
            }
        }
        cout<<res;
        return res;
    }
private:
    bool isMagicSquares(vector<vector<int>>& grid,int row,int col){
        vector<int>vec;
        for(int i=0;i<3;i++)
            for(int j=0;j<3;j++){
                if(grid[row+i][col+j]>9)
                    return false;
                if(grid[row+i][col+j]<1)
                    return false;
                vec.push_back(grid[row+i][col+j]);
            }
        sort(vec.begin(),vec.end());
        for(int i=0;i<8;i++)
            if(vec[i]==vec[i+1]) return false;

        int sum=grid[row][col]+grid[row][col+1]+grid[row][col+2];
        for(int i=row;i<row+3;i++){
            int tmp=grid[i][col]+grid[i][col+1]+grid[i][col+2];
            if(tmp!=sum)
                return false;
        }
        for(int j=col;j<col+3;j++){
            if(grid[row][j]+grid[row+1][j]+grid[row+2][j]!=sum)
                return false;
        }
        if(grid[row][col]+grid[row+1][col+1]+grid[row+2][col+2]!=sum)
            return false;
        if(grid[row+2][col]+grid[row+1][col+1]+grid[row][col+2]!=sum)
            return false;
        return true;
    }
}su;


int main(){
    vector<int> n0({3,2,9,2,7});
    vector<int> n1({6,1,8,4,2});
    vector<int> n2({7,5,3,2,7});
    vector<int> n3({2,9,4,9,6});

    vector<vector<int>> nums;
    nums.push_back(n0);
    nums.push_back(n1);
    nums.push_back(n2);
    nums.push_back(n3);
    su.numMagicSquaresInside(nums);

    return 0;
}
