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
