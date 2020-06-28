// 169. Majority Element
// https://leetcode.com/problems/majority-element/

// 暴力解
// 计算每个元素的出现次数
// Time complexity : O(n^2), Space complexity : O(n)

// 哈希
// 计算每个元素的出现次数
// Time complexity : O(n), Space complexity : O(n)

// 随机
// 随机获得元素，判断是否为主要元素，否则随机获取下一个元素，重复流程
// Time complexity : O(∞), Space complexity : O(1)

// 分治法
// 递归自底而上获取分区主要元素
// Time complexity : O(nlgn), Space complexity : O(lgn)
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        return majorityElementRect(nums, 0, nums.size()-1);
    }
    
    int majorityElementRect(vector<int>& nums, int low, int high)
    {
        if(low==high)
            return nums[low];
        
        int mid = (high-low) / 2 + low;
        int left = majorityElementRect(nums, low, mid);
        int right = majorityElementRect(nums, mid+1, high);
        
        if(left==right)
        {
            return left;
        }
        
        int leftCount = countInRange(nums, left, low, high);
        int rightCount = countInRange(nums, right, low, high);
        
        // cout << mid << " " << left << " " << leftCount << " " << right << " " << rightCount << endl;
        
        return leftCount > rightCount ? left : right;
    }
    
    int countInRange(vector<int>& nums, int n, int low, int high)
    {
        int count = 0;
        for(int i = low; i <= high; i++)
        {
            if( nums[i] == n )
                count++;
        }
        return count;
    }
};


// Boyer-Moore Voting Algorithm
// Time complexity : O(n), Space complexity : O(1)
// 假设第一位是候选人，当出现频率低于其他元素时，下一个元素成为候选人
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int count = 0;
        int candidate;
        for(int i=0; i<nums.size(); i++)
        {
            if (count == 0)
                candidate = nums[i];
            count += nums[i] == candidate ? 1 : -1;
        }
        return candidate;
    }
};