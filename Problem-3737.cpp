class Solution {
public:
    struct Fenwick {
        int n;
        vector<int> bit;

        Fenwick(int sz) : n(sz), bit(sz + 1, 0) {}

        void update(int idx, int val) {
            while (idx <= n) {
                bit[idx] += val;
                idx += idx & -idx;
            }
        }

        int query(int idx) {
            int res = 0;
            while (idx > 0) {
                res += bit[idx];
                idx -= idx & -idx;
            }
            return res;
        }
    };

    int countMajoritySubarrays(vector<int>& nums, int target) {
        int n = nums.size();

        vector<int> prefix(n + 1, 0);
        for (int i = 0; i < n; i++)
            prefix[i + 1] = prefix[i] + (nums[i] == target ? 1 : -1);

        vector<int> comp = prefix;
        sort(comp.begin(), comp.end());
        comp.erase(unique(comp.begin(), comp.end()), comp.end());

        Fenwick ft(comp.size());

        int ans = 0;
        for (int x : prefix) {
            int idx = lower_bound(comp.begin(), comp.end(), x) - comp.begin() + 1;
            ans += ft.query(idx - 1);
            ft.update(idx, 1);
        }

        return ans;
    }
};
