class Solution {
public:
    int distinctSubseqII(string s) {
        const long long MOD = 1000000007;
        
        vector<long long> dp(s.length() + 1, 0);
        vector<long long> last(26, 0);

        dp[0] = 1;

        for (int i = 1; i <= s.length(); i++) {
            int ch = s[i - 1] - 'a';

            dp[i] = (2 * dp[i - 1]) % MOD;

            dp[i] = (dp[i] - last[ch] + MOD) % MOD;

            last[ch] = dp[i - 1];
        }
        return (dp[s.length()] - 1 + MOD) % MOD;
    }
};
