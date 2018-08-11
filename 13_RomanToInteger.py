class Solution:
    def romanToInt(self, s):
        """
        :type s: str
        :rtype: int
        """
        d = {"I":1,"V":5,"X":10,"L":50,"C":100,"D":500,"M":1000}

        if not s:
            return 0
        else:
            value = d[s[-1]]
            for i in range(len(s)-2,-1,-1):
                c,p = s[i],s[i+1]
                value = value + d[c] if d[c] >= d[p] else value - d[c]
        return value

'''
因为高阶罗马数字前面只能放一个低阶罗马数字
判断当前位置罗马数字和上一个罗马数字的阶级，来决定加减
'''