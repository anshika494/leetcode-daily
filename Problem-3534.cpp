class Solution {
public:
    vector<int> pathExistenceQueries(int n, vector<int>& nums, int maxDiff,
                                     vector<vector<int>>& queries) {

        vector<pair<int,int>> arr;
        for (int i = 0; i < n; i++)
            arr.push_back({nums[i], i});

        sort(arr.begin(), arr.end());

        // position of each original node in sorted order
        vector<int> pos(n);
        for (int i = 0; i < n; i++)
            pos[arr[i].second] = i;

        // component id
        vector<int> comp(n);
        int id = 0;
        comp[0] = 0;
        for (int i = 1; i < n; i++) {
            if (arr[i].first - arr[i - 1].first > maxDiff)
                id++;
            comp[i] = id;
        }

        // farthest reachable index in one jump
        vector<int> reach(n);
        int r = 0;
        for (int i = 0; i < n; i++) {
            while (r + 1 < n &&
                   arr[r + 1].first - arr[i].first <= maxDiff)
                r++;
            reach[i] = r;
        }

        const int LOG = 18;

        vector<vector<int>> up(LOG, vector<int>(n));

        up[0] = reach;

        for (int k = 1; k < LOG; k++) {
            for (int i = 0; i < n; i++)
                up[k][i] = up[k - 1][up[k - 1][i]];
        }

        vector<int> ans;

        for (auto &q : queries) {

            int u = pos[q[0]];
            int v = pos[q[1]];

            if (u > v)
                swap(u, v);

            if (comp[u] != comp[v]) {
                ans.push_back(-1);
                continue;
            }

            if (u == v) {
                ans.push_back(0);
                continue;
            }

            int cur = u;
            int steps = 0;

            for (int k = LOG - 1; k >= 0; k--) {
                if (up[k][cur] < v) {
                    cur = up[k][cur];
                    steps += (1 << k);
                }
            }

            ans.push_back(steps + 1);
        }

        return ans;
    }
};
