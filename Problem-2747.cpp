class Solution {
public:
    vector<int> countServers(int n, vector<vector<int>>& logs, int x, vector<int>& queries) {
        int m = queries.size();

        vector<pair<int, int>> q;

        for (int i = 0; i < m; i++) {
            q.push_back({queries[i], i});
        }

        sort(logs.begin(), logs.end(), [](auto &a, auto &b) {
            return a[1] < b[1];
        });

        sort(q.begin(), q.end());

        unordered_map<int, int> freq;
        vector<int> ans(m);

        int left = 0, right = 0;

        for (auto &[time, idx] : q) {
            while (right < logs.size() && logs[right][1] <= time) {
                freq[logs[right][0]]++;
                right++;
            }

            while (left < right && logs[left][1] < time - x) {
                freq[logs[left][0]]--;

                if (freq[logs[left][0]] == 0) {
                    freq.erase(logs[left][0]);
                }
                left++;
            }

            ans[idx] = n - freq.size();
        }

        return ans;
    }
};
