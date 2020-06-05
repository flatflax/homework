// 153. Find Minimum in Rotated Sorted Array
/*
1. 比较字符串
2. 比较字符串中间值和字符串开头值/结束值的大小比较
    2.1 middle > end: 循环字符串的开头在middle之后，start = middle + 1;
    2.2 middle < start: 循环字符串的开头在middle之前, end = middle;
*/

class Solution {
public:
    int findMin(vector<int>& nums) {
        if (nums.size() == 1) return nums[0];
        int start = 0;
        int end = nums.size()-1;
        while(start<=end)
        {
            int middle = (end + start)/2;
            if (nums[middle]>nums[end]) start = middle + 1;
            else if (nums[middle]<nums[start]) end = middle;
            if (nums[start]<= nums[end]) return nums[start];
        }
        return nums[start];
        
    }
};