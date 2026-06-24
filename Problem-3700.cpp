class Solution {
public:
    static const long long MOD = 1000000007;

    using Matrix = vector<vector<long long>>;

    Matrix multiply(const Matrix& A, const Matrix& B) {
        int n = A.size();
        Matrix C(n, vector<long long>(n, 0));

        for (int i = 0; i < n; i++) {
            for (int k = 0; k < n; k++) {
                if (A[i][k] == 0) continue;
                for (int j = 0; j < n; j++) {
                    if (B[k][j] == 0) continue;
                    C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % MOD;
                }
            }
        }
        return C;
    }

    Matrix power(Matrix base, long long exp) {
        int n = base.size();
        Matrix res(n, vector<long long>(n, 0));

        for (int i = 0; i < n; i++) res[i][i] = 1;

        while (exp) {
            if (exp & 1) res = multiply(res, base);
            base = multiply(base, base);
            exp >>= 1;
        }
        return res;
    }

    int zigZagArrays(int n, int l, int r) {
        long long m = r - l + 1;

        if (n == 1) return m % MOD;
        if (n == 2) return (m % MOD) * ((m - 1) % MOD) % MOD;

        int S = 2 * m;

        Matrix T(S, vector<long long>(S, 0));

        for (int y = 0; y < m; y++) {
            for (int x = 0; x < y; x++) {
                T[y][m + x] = 1;
            }

            for (int x = y + 1; x < m; x++) {
                T[m + y][x] = 1;
            }
        }

        vector<long long> base(S, 0);

        for (int v = 0; v < m; v++) {
            base[v] = v;
            base[m + v] = m - 1 - v;
        }

        Matrix P = power(T, n - 2);

        vector<long long> finalState(S, 0);

        for (int i = 0; i < S; i++) {
            long long cur = 0;
            for (int j = 0; j < S; j++) {
                cur = (cur + P[i][j] * base[j]) % MOD;
            }
            finalState[i] = cur;
        }

        long long ans = 0;
        for (long long x : finalState) {
            ans = (ans + x) % MOD;
        }

        return (int)ans;
    }
};
