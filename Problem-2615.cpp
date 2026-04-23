class Solution {
public:
    vector<long long> distance(vector<int>& nums) {
        int n = nums.size();
        vector<long long> arr(n, 0);

        unordered_map<int, vector<int>> mp;

        for (int i = 0; i < n; i++) {
            mp[nums[i]].push_back(i);
        }

        for (auto &it : mp) {
            vector<int> &indices = it.second;
            int m = indices.size();

            vector<long long> prefix(m, 0);
            prefix[0] = indices[0];

            for (int i = 1; i < m; i++) {
                prefix[i] = prefix[i - 1] + indices[i];
            }

            for (int i = 0; i < m; i++) {
                long long left = 0, right = 0;

                if (i > 0) {
                    left = (long long)i * indices[i] - prefix[i - 1];
                }

                if (i < m - 1) {
                    right = (prefix[m - 1] - prefix[i]) - 
                            (long long)(m - i - 1) * indices[i];
                }

                arr[indices[i]] = left + right;
            }
        }
        return arr;        
    }
};