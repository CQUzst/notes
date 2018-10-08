//两数之和
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        // vector<int> a;
        // for(int i=0;i<nums.size();i++)
        //     for(int j=i+1;j<nums.size();j++)
        //         if(nums[i]+nums[j]==target)
        //         {
        //             a.push_back(i);
        //             a.push_back(j);
        //         }
        // return a;
        int N = nums.size();
        vector<int> res;
        map<int ,int> subMap;//map键值对

        for(int i = 0;i<N;i++)
        {
            int temp = target -nums[i];//目标值减去当前值得到另一个值
            //std::map<int,int>::iterator it;
            auto it = subMap.find(temp);//从map中找到这个键值对
            if(it != subMap.end())//说明找到了，就把it的值和第i的位置返回res
            {
                res.push_back(it->second);
                res.push_back(i);
            }
            //前面一段遍历的时候submap是空的，i每+1subMap里面添加一个键值对，到后面的i多了subMap也多了
            subMap[nums[i]] = i;//然后再把submap中对应的位置的值置为相应的i值
        }
        
        return res;
    }
};
//三数之和
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) 
    {
        vector<vector<int>>res;
        int n=nums.size();
        sort (nums.begin(),nums.end());//排序
        for(int i=0;i<n;i++) 
        {
            if(nums[i]>0) break;//当遍历到正数的时候就break
            if(i>0&&nums[i]==nums[i-1]) continue;//重复就跳过.相同的数字不会两次
            int target=0-nums[i];//对于遍历到的数，用0减去这个fix的数得到一个target，然后再找到两个数之和等于target
            int j=i+1,k=n-1;
            while(j<k)
            {
                if(nums[j]+nums[k]==target)
                {
                    res.push_back({nums[i],nums[j],nums[k]});
                    while(j<k&&nums[j]==nums[j+1]) ++j;
                    while(j<k&&nums[k-1]==nums[k]) --k;
                    ++j;
                    --k;
                }
                else if(nums[j]+nums[k]<target) ++j;
                else --k;
            }
        }
    return res;
    }
};
//四数之和
class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<vector<int>>res;
        if(nums.size()<4) return res;
        sort (nums.begin(),nums.end());//排序
        for(int i=0;i<nums.size()-3;i++){
            if(i>0&&nums[i]==nums[i-1]) continue;
            for(int j=i+1;j<nums.size()-2;j++){
                if(j> i+1 &&nums[j]==nums[j-1]) continue;
                int left=j+1,right=nums.size()-1;
                while(left<right){
                    int sum=nums[i]+nums[j]+nums[left]+nums[right];
                    if(sum==target){
                        res.push_back({nums[i],nums[j],nums[left],nums[right]});
                        while (left<right&&nums[left]==nums[left+1]) left++;
                        while(left<right&&nums[right]==nums[right-1])right--;
                        left++;
                        right--;
                    }
                    else if(sum>target) right--;
                    else left++;
                }
            }
        }
        // set<vector<int>> st(res.begin(), res.end());//去重
        // res.assign(st.begin(), st.end());
        return res;
        
        // vector<vector<int>> res;
        // int n = nums.size();
        // if (nums.size()<4) return res;
        // sort(nums.begin(), nums.end());
        // for (int i = 0; i < nums.size() - 3; i++){
        //     if (i > 0 && nums[i] == nums[i-1]) continue;
        //     if (nums[i]+nums[i+1]+nums[i+2]+nums[i+3] > target)break;
        //     if (nums[i]+nums[n-3]+nums[n-2]+nums[n-1] < target)continue;
        //     for (int j = i+1; j < nums.size() - 2; j++){
        //         if (j > i+1 && nums[j] == nums[j-1])continue;
        //         if (nums[i]+nums[j]+nums[j+1]+nums[j+2] > target)break;
        //         if (nums[i]+nums[j]+nums[n-2]+nums[n-1] < target)continue;
        //         int left = j + 1;
        //         int right = n - 1;
        //         while(left < right){
        //             if (nums[i]+nums[j]+nums[left]+nums[right] < target)left++;
        //             else if (nums[i]+nums[j]+nums[left]+nums[right] > target)right--;
        //             else{
        //                 res.push_back(vector<int>{nums[i],nums[j],nums[left],nums[right]});
        //                 do{left++;}while(left<right && nums[left]==nums[left-1]);
        //                 do{right--;}while(left<right && nums[right]==nums[right+1]);
        //             }
        //         }
        //     }
        // }
        // return res;
    }
};
//四数之和II
class Solution {
public:
    int fourSumCount(vector<int>& A, vector<int>& B, vector<int>& C, vector<int>& D) {
        int res = 0;
        int n=A.size();
        unordered_map<int, int> m(2*n*n);
        
        for (int i = 0; i <n; ++i) {
            for (int j = 0; j < n; ++j) {
                m[A[i] + B[j]]++;//每个值的可能组合数
            }
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                unordered_map<int,int> ::iterator it;
                it=m.find(0-C[i]-D[j]);
                if(it!=m.end())
                    res += it->second;
            }
        }
        return res;
        // unordered_map<int,int> recordCD(2*A.size()*A.size());
        // for(int i =0;i<A.size();i++)
        //     for(int j =0;j<A.size();j++)
        //         recordCD[C[i]+D[j]] ++;
        // int nums=0;
        // for(int i =0;i<A.size();i++)
        //     for(int j =0;j<A.size();j++){
        //         auto it = recordCD.find( 0-(A[i]+B[j]));
        //         if(it !=recordCD.end()){
        //             nums += it->second;
        //         }       
        //     }
        // return nums;
    }
};