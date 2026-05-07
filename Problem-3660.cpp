class Solution {
public:
    vector<int> maxValue(vector<int>& nums) {
        int mx = *max_element(nums.begin(), nums.end());

        vector<int> ans(nums.size(), mx);

        return ans;        
    }
};
