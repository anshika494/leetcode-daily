class Solution {
public:
    vector<int> gcdValues(vector<int>& nums, vector<long long>& queries) {
        int maxVal = *max_element(nums.begin(), nums.end());
        
        vector<long long> freq(maxVal + 1, 0);
        for (int x : nums)
            freq[x]++;
        
        vector<long long> gcdCount(maxVal + 1, 0);

        for (int g = maxVal; g >= 1; g--) {
            long long cnt = 0;

            for (int m = g; m <= maxVal; m += g)
                cnt += freq[m];

            gcdCount[g] = cnt * (cnt - 1) / 2;

            for (int m = 2*g; m <= maxVal; m += g)
                gcdCount[g] -= gcdCount[m];
        }

        vector<long long> prefix(maxVal + 1, 0);
        for (int i = 1; i <= maxVal; i++)
            prefix[i] = prefix[i-1] + gcdCount[i];

        vector<int> ans;

        for (long long q : queries) {
            int g = lower_bound(prefix.begin(), prefix.end(), q + 1) - prefix.begin();
            ans.push_back(g);
        }
        return ans;
    }
};
