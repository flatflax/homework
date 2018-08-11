class Solution(object):
    def lengthOfLongestSubstring(self, s):
        """
        :type s: str
        :rtype: int
        """
        N = len(s)
        lastsub = ''
        thissub = ''
        for i in range(0, N):
            if s[i:i + 1] in thissub:
                if len(lastsub) < len(thissub):
                    lastsub = thissub
                chaindex = thissub.index(s[i:i + 1])
                thissub = thissub[chaindex + 1:]
            thissub += s[i:i + 1]
            if i == N - 1:
                if len(lastsub) < len(thissub):
                    lastsub = thissub
        return len(lastsub)
