class Solution {
public:
    vector<int> maxActiveSectionsAfterTrade(string s, vector<vector<int>>& queries) {
        int n = s.size();

        vector<int> pref(n + 1, 0);
        for (int i = 0; i < n; i++)
            pref[i + 1] = pref[i] + (s[i] == '1');

        struct Seg {
            int l, r;
            char c;
            int len;
        };

        vector<Seg> segs;
        vector<int> segId(n);

        for (int i = 0; i < n;) {
            int j = i;
            while (j < n && s[j] == s[i]) j++;
            segs.push_back({i, j - 1, s[i], j - i});
            for (int k = i; k < j; k++)
                segId[k] = (int)segs.size() - 1;
            i = j;
        }

        int m = segs.size();

        vector<int> gain(m, 0);

        for (int i = 1; i + 1 < m; i++) {
            if (segs[i].c == '1' &&
                segs[i - 1].c == '0' &&
                segs[i + 1].c == '0') {
                gain[i] = segs[i - 1].len + segs[i + 1].len;
            }
        }

        // segment tree
        int SZ = 1;
        while (SZ < m) SZ <<= 1;
        vector<int> st(2 * SZ, 0);

        for (int i = 0; i < m; i++)
            st[SZ + i] = gain[i];

        for (int i = SZ - 1; i; i--)
            st[i] = max(st[i << 1], st[i << 1 | 1]);

        auto queryTree = [&](int l, int r) {
            if (l > r) return 0;
            l += SZ;
            r += SZ;
            int ans = 0;
            while (l <= r) {
                if (l & 1) ans = max(ans, st[l++]);
                if (!(r & 1)) ans = max(ans, st[r--]);
                l >>= 1;
                r >>= 1;
            }
            return ans;
        };

        vector<int> ans;

        for (auto &q : queries) {
            int l = q[0], r = q[1];

            int ones = pref[r + 1] - pref[l];

            int L = segId[l];
            int R = segId[r];

            while (L < m && segs[L].l < l) L++;
            while (R >= 0 && segs[R].r > r) R--;

            int best = queryTree(L, R);

            ans.push_back(ones + best);
        }

        return ans;
    }
};
