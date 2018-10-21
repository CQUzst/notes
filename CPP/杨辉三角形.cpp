class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> res;
        if(numRows==0)return res;
        vector<int> firstRow;
        firstRow.push_back(1);
        res.push_back(firstRow);
        if(numRows==1)return res;
        vector<int> secRow;
        secRow.push_back(1);
        secRow.push_back(1);
        res.push_back(secRow);
        if(numRows==2)return res;
        for(int i=2;i<numRows;i++){
            vector<int> row;
            row.push_back(1);
            for(int j=1;j<i ;j++){
                row.push_back(res[i-1][j-1]+res[i-1][j]);
                }
            row.push_back(1);
            res.push_back(row);
        }
        return res;
    }
};