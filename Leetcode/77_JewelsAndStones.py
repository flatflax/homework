class Solution(object):
    def numJewelsInStones(self, J, S):
        """
        :type J: str
        :type S: str
        :rtype: int
        """
        J1 = [j for j in J]
        S1 = [s for s in S]
        sum = 0
        for j in J1:
            for s in S1:
                if s==j:
                    sum+=1
        return sum