class Solution:
    def longestPalindrome(self, s):
        if len(s)==0:
        	return s
        maxLen=1
        start=0
        for i in range(len(s)):
        	if i-maxLen >=1 and s[i-maxLen-1:i+1]==s[i-maxLen-1:i+1][::-1]:
        		start=i-maxLen-1
        		maxLen+=2
        		continue

        	if i-maxLen >=0 and s[i-maxLen:i+1]==s[i-maxLen:i+1][::-1]:
        		start=i-maxLen
        		maxLen+=1
        return s[start:start+maxLen]

'''
假设i为最大回文子串右侧边界

s[i-maxLen:i+1]为回文 说明最长回文子串奇偶变化 maxLen+1
s[i-maxLen-1:i+1]为回文 说明当前最长回文子串 = 次长回文子串(通常边界是i-1)+2字符 maxLen+2
'''