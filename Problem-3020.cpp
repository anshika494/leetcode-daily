class Solution {
public:
    int maximumLength(vector<int>& nums) {
        unordered_map<long long, int> freq;
        for (int x : nums)
            freq[x]++;

        int ans = 1;

        if (freq.count(1)) {
            int c = freq[1];
            ans = max(ans, (c % 2 == 1) ? c : c - 1);
        }

        for (auto &[start, cnt] : freq) {
            if (start == 1)
                continue;

            long long cur = start;
            int len = 1;

            while (freq[cur] >= 2) {
                __int128 sq = (__int128)cur * cur;
                if (sq > LLONG_MAX)
                    break;

                long long nxt = (long long)sq;
                if (!freq.count(nxt))
                    break;

                len += 2;
                cur = nxt;
            }
            ans = max(ans, len);
        }
        return ans;
    }
};
