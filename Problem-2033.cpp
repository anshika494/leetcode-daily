class Solution {
public:
    int minOperations(vector<vector<int>>& grid, int x) {
        vector<int> nums;

        for (auto &row : grid) {
            for (int val : row) {
                nums.push_back(val);
            }
        }

       int base = nums[0];

        for (int val : nums) {
            if ((val - base) % x != 0) {
                return -1;
            }
        }

        sort(nums.begin(), nums.end());

        int n = nums.size();
        int median = nums[n / 2];

        int operations = 0;

        for (int val : nums) {
            operations += abs(val - median) / x;
        }
        return operations;        
    }
};
