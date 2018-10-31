class Solution {
public:
    int thirdMax(vector<int>& nums) {
        //利用set的自动排序和自动去重复项的特性
        set<int> s;
        for (int num : nums) {
            //对于遍历到的数字，加入set中，重复项就自动去掉了
            s.insert(num);
            //如果此时set大小大于3个了，那么我们把set的第一个元素去掉，也就是将第四大的数字去掉
            if (s.size() > 3) 
                s.erase(s.begin());
        }
        //set始终维护的是最大的三个不同的数字
        //最后遍历结束后，我们看set的大小是否为3，是的话就返回首元素，不是的话就返回尾元素
        return s.size() == 3 ? *s.begin() : *s.rbegin();
        
        
        // set<int> tmp(nums.begin(), nums.end());
        // int max = INT_MIN;
        // int sec = max;
        // int third = sec;
        // for(int i = 0; i<nums.size(); ++i){
        //     if(nums[i]>max){
        //         third = sec;
        //         sec = max;
        //         max = nums[i];
        //     }
        //     else if(nums[i]!=max && nums[i]>sec){
        //         third = sec;
        //         sec = nums[i];
        //     }
        //     else if(nums[i]!=max && nums[i]!=sec && nums[i]>third)
        //         third = nums[i];
        // }
        // if(tmp.size()>2)
        //     return third;
        // else
        //     return max;
    }
};