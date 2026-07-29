class Solution {
public:
    long long C(int n, int r, long long limit) {
        if (r > n) return 0;
        r = min(r, n - r);

        __int128 ans = 1;
        for (int i = 1; i <= r; i++) {
            ans = ans * (n - r + i) / i;
            if (ans > limit) return limit;
        }
        return (long long)ans;
    }

    long long countWays(vector<int>& freq, long long limit) {
        int rem = 0;
        for (int x : freq) rem += x;

        long long ans = 1;
        for (int x : freq) {
            if (x == 0) continue;
            ans = min(limit, ans * C(rem, x, limit) );
            if (ans >= limit) return limit;
            rem -= x;
        }
        return ans;
    }

    string smallestPalindrome(string s, int k) {
        vector<int> freq(26, 0);
        for (char c : s) freq[c - 'a']++;

        vector<int> half(26);
        string mid = "";

        for (int i = 0; i < 26; i++) {
            half[i] = freq[i] / 2;
            if (freq[i] & 1) mid.push_back(char('a' + i));
        }

        long long limit = (long long)k + 1;

        if (countWays(half, limit) < k)
            return "";

        string left = "";
        int len = 0;
        for (int x : half) len += x;

        while (len--) {
            for (int c = 0; c < 26; c++) {
                if (half[c] == 0) continue;

                half[c]--;
                long long cnt = countWays(half, limit);

                if (cnt >= k) {
                    left.push_back(char('a' + c));
                    break;
                }

                k -= cnt;
                half[c]++;
            }
        }

        string right = left;
        reverse(right.begin(), right.end());

        return left + mid + right;
    }
};
