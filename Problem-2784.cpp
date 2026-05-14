class Solution {
public:
    bool isGood(vector<int>& nums) {
        int sz = nums.size();

        if (sz < 2)
            return false;

        sort(nums.begin(), nums.end());
        int n = sz - 1;

        for (int i = 0; i < n - 1; i++) {
            if (nums[i] != i + 1)
                return false;
        }

        return nums[n - 1] == n && nums[n] == n;
    }
};
