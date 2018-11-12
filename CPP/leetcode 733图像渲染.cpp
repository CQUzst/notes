class Solution { 
    public: 
    vector<vector<int>> floodFill(vector<vector<int>>& image,int sr,int sc,int newColor){
        if(image[sr][sc]==newColor)
            return image;
        else
            dfs(image,sr,sc,image[sr][sc],newColor);
        return image;
    } 
private:
    void dfs(vector<vector<int>>&image,int x,int y,int targetColor,int newColor){
        int row=image.size(),col=image[0].size();
        if(x<0||x>=row||y<0||y>=col||image[x][y]!=targetColor)return;
        else{
            image[x][y]=newColor;
            dfs(image,x-1,y,targetColor,newColor);
            dfs(image,x+1,y,targetColor,newColor);
            dfs(image,x,y-1,targetColor,newColor);
            dfs(image,x,y+1,targetColor,newColor);
        }
    }
};
