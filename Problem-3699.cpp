class Solution {
public:
    static const long long MOD = 1000000007LL;

    int countZigZagArrays(int n, int l, int r) {
        long long m = r - l + 1;

        if (n == 1) return (int)(m % MOD);

        vector<long long> up(m + 1, 0), down(m + 1, 0);

        for (int v = 1; v <= m; v++) {
            up[v] = v - 1;
            down[v] = m - v;
        }

        if (n == 2) {
            long long ans = 0;
            for (int v = 1; v <= m; v++) {
                ans = (ans + up[v] + down[v]) % MOD;
            }
            return (int)ans;
        }

        for (int len = 3; len <= n; len++) {
            vector<long long> newUp(m + 1, 0), newDown(m + 1, 0);

            vector<long long> prefDown(m + 1, 0);
            for (int i = 1; i <= m; i++) {
                prefDown[i] = (prefDown[i - 1] + down[i]) % MOD;
            }

            vector<long long> suffUp(m + 2, 0);
            for (int i = m; i >= 1; i--) {
                suffUp[i] = (suffUp[i + 1] + up[i]) % MOD;
            }

            for (int v = 1; v <= m; v++) {
                newUp[v] = prefDown[v - 1];      // u < v
                newDown[v] = suffUp[v + 1];      // u > v
            }

            up.swap(newUp);
            down.swap(newDown);
        }

        long long ans = 0;
        for (int v = 1; v <= m; v++) {
            ans = (ans + up[v] + down[v]) % MOD;
        }

        return (int)ans;
    }
};
