//存在重复元素II
class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        // unordered_map<int,int>m;
        // for(int i=0;i<nums.size();i++){
        //     if(i>k)
        //         m[nums[i-k-1]]--;
        //     m[nums[i]]++;
        //     if(m[nums[i]]>1)
        //         return true;
        // }
        // return false;
        
        
        // unordered_map<int,int> record;
        // for(int i=0;i<nums.size(); i++){
        //     if(record.find(nums[i])==record.end())
        //         record[nums[i]] = i;
        //     else if(i-record[nums[i]]<=k)
        //         return true;
        //     else
        //         record[nums[i]] = i;//更新最近的位置
        // }
        // return false;
        
        
        unordered_map<int,int> m;
        int j = 0;
        for (int i = 0; i < nums.size(); ++i){
            if (i - j > k){
                m.erase(nums[j++]);
            }
            if (m.find(nums[i])!=m.end()){
                return true;
            }
            m.insert({nums[i],i});
        }
        return false;
    }
};

//存在重复元素III
class Solution {
public:
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
        // map<long long, int> m;
        // int j = 0;
        // for (int i = 0; i < nums.size(); ++i) 
        // {
        //     if (i - j > k)
        //     {
        //         m.erase(nums[j++]);
        //     }
        //     auto a = m.lower_bound((long long)nums[i] - t);
        //     if (a != m.end() && abs(a->first - nums[i]) <= t)
        //     {
        //         return true;
        //     }
        //     m[nums[i]] = i;
        // }
        // return false;
        
        set<long long> knear; //有序序列
        for (int i = 0; i < nums.size(); i++){
            if (i > k) //将窗口k之前的set序列删掉
                knear.erase(nums[i - k - 1]);   
            long long a = nums[i];
            //set<long long>::iterator
            //lower_bound(val)返回set中大于或等于val的第一个元素位置。如果所有元素都小于val，则返回end
            auto p = knear.lower_bound(a - t);// *p-nums[i]>=-t
            if (p != knear.end() && *p - a <= t)//还需要满足 *p - nums[i] <= t
                return true;
            knear.insert(nums[i]);//往set序列里面添加元素，维持一个宽度为k的窗口
        }
        return false;
    }
};