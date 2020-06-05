// 940. Distinct Subsequences II
/*
1.
S = "ab"
dp[0] = 2, as it counts ("", "a")
dp[1] = 4, as it counts ("", "a", "b", "ab");
dp[k] = 2 * dp[k-1] - dp[last[S[k]] - 1]


2. 从字符串结尾开始，计算每个字母起始的字串值
S = "aba"
2.1 S[2] f["a"]=1:"a"
2.2 S[1] f["b"]=2:"b","ba"; f["a"]=1:"a"
2.3 S[0] f["b"]=2:"b","ba"; f["a"]=4:"a","ab","ba","aa"(f["b"]+f["a"]+1)
2.4 ans=f["b"]+f["a"]=6
*/

class Solution {
public:
    int distinctSubseqII(string &s) {
        long mod = 1e9+7;
        int ans=0;
        int len = s.size();
        int f[26] = {};
        
        for(int i=len-1;i>=0;i--)
        {
            int a=1;
            for(int j=0;j<26;j++)
            {
                a+=f[j];
                a %= mod;
            }
            f[s[i]-'a'] = a;
        }
        for(int i=0;i<26;i++)
        {
            ans += f[i];
            ans %= mod;
        }
        return ans;
    }
};