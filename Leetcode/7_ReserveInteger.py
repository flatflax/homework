# # -*- coding: UTF-8 -*- 

'''
1.x=0  2.x<0  3.x>0
商*10 累加
int32->2^31-1
'''
class Solution(object):
    def reverse(self, x):
        """
        :type x: int
        :rtype: int
        """
        if (x == 0) or (x>2147483647) or (x<-2147483647):
            return 0
        if x < 0 :
            return -self.reverse(-x)
        
        y = x
        result = 0
        
        while y > 0 :
            result = result*10 + int(y%10)
			if result>2147483647:
				return 0
            y = int(y/10)
        return result