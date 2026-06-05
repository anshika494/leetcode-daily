class Solution {
public:
    struct Node {
        long long cnt;
        long long wav;
    };

    string s;
    Node dp[20][11][11][2];
    bool vis[20][11][11][2];

    Node dfs(int pos, int prev2, int prev1, bool tight, bool started) {
        if (pos == (int)s.size()) {
            return {1, 0};
        }

        if (!tight && vis[pos][prev2 + 1][prev1 + 1][started]) {
            return dp[pos][prev2 + 1][prev1 + 1][started];
        }

        int limit = tight ? s[pos] - '0' : 9;
        Node res = {0, 0};

        for (int d = 0; d <= limit; d++) {
            bool ntight = tight && (d == limit);

            if (!started && d == 0) {
                Node nxt = dfs(pos + 1, -1, -1, ntight, false);
                res.cnt += nxt.cnt;
                res.wav += nxt.wav;
            } else if (!started) {
                Node nxt = dfs(pos + 1, -1, d, ntight, true);
                res.cnt += nxt.cnt;
                res.wav += nxt.wav;
            } else if (prev2 == -1) {
                Node nxt = dfs(pos + 1, prev1, d, ntight, true);
                res.cnt += nxt.cnt;
                res.wav += nxt.wav;
            } else {
                int add = ((prev1 > prev2 && prev1 > d) ||
                           (prev1 < prev2 && prev1 < d));

                Node nxt = dfs(pos + 1, prev1, d, ntight, true);

                res.cnt += nxt.cnt;
                res.wav += nxt.wav + 1LL * add * nxt.cnt;
            }
        }

        if (!tight) {
            vis[pos][prev2 + 1][prev1 + 1][started] = true;
            dp[pos][prev2 + 1][prev1 + 1][started] = res;
        }

        return res;
    }

    long long solve(long long n) {
        if (n <= 0) return 0;

        s = to_string(n);
        memset(vis, 0, sizeof(vis));

        return dfs(0, -1, -1, true, false).wav;
    }

    long long totalWaviness(long long num1, long long num2) {
        return solve(num2) - solve(num1 - 1);
    }
};
