class Solution:
    def climbStairs(self, n):
        """
        :type n: int
        :rtype: int
        """
        x = 1
        y = 2
        if n == 1:
            return 1
        elif n==2:
            return 2
        result = 0
        for i in range(3,n+1):
            result = x + y
            x,y = y,result
        return result

'''
当前台阶 = 上一级台阶+1步 / 上两级台阶+2步
因此可以到达当前台阶的方法数 = 上级台阶方法数 + 上上级台阶方法数
'''