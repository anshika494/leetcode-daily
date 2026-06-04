class Solution {
public:
    struct Node {
        long long cnt;
        long long waviness;
    };

    string s;
    Node dp[11][11][11][2][2];
    bool vis[11][11][11][2][2];

    Node dfs(int pos, int prev2, int prev1, bool tight, bool started) {
        if (pos == (int)s.size()) {
            return {1, 0};
        }

        if (!tight && vis[pos][prev2][prev1][0][started]) {
            return dp[pos][prev2][prev1][0][started];
        }

        Node ans = {0, 0};
        int limit = tight ? s[pos] - '0' : 9;

        for (int d = 0; d <= limit; d++) {
            bool ntight = tight && (d == limit);

            if (!started && d == 0) {
                Node nxt = dfs(pos + 1, 10, 10, ntight, false);
                ans.cnt += nxt.cnt;
                ans.waviness += nxt.waviness;
                continue;
            }

            if (!started) {
                Node nxt = dfs(pos + 1, 10, d, ntight, true);
                ans.cnt += nxt.cnt;
                ans.waviness += nxt.waviness;
                continue;
            }

            long long add = 0;

            if (prev2 != 10) {
                bool peak = (prev1 > prev2 && prev1 > d);
                bool valley = (prev1 < prev2 && prev1 < d);

                if (peak || valley) add = 1;
            }

            Node nxt = dfs(pos + 1, prev1, d, ntight, true);

            ans.cnt += nxt.cnt;
            ans.waviness += nxt.waviness + add * nxt.cnt;
        }

        if (!tight) {
            vis[pos][prev2][prev1][0][started] = true;
            dp[pos][prev2][prev1][0][started] = ans;
        }

        return ans;
    }

    long long solve(long long x) {
        if (x < 0) return 0;

        s = to_string(x);
        memset(vis, 0, sizeof(vis));

        return dfs(0, 10, 10, true, false).waviness;
    }

    int totalWaviness(int num1, int num2) {
        return (int)(solve(num2) - solve((long long)num1 - 1));
    }
};
