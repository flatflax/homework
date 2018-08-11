class Solution(object):
    def twoSum(self, nums, target):
        """
        :type nums: List[int]
        :type target: int
        :rtype: List[int]
        """
        N = len(nums)
        result = []
        for i in range(0, N):
            n2 = target - nums[i]
            if n2 in nums[i + 1:N]:
                result.append(i)
                result.append(nums[i + 1:N].index(n2) + i + 1)
                break
        return result
