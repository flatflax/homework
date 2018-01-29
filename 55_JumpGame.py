class Solution(object):
    def canJump(self, nums):
        N = len(nums) - 1
        l1 = N
        for i in range(N, -1, -1):
            furtherPosition = min(N, i + nums[i])
            if furtherPosition >= l1:
                l1 = i

        if 0 == l1:
            return True
        else:
            return False
