class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {
        unordered_set<int> st;
        int n = nums.size();

        for (int x : nums)
            st.insert(x);

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                for (int k = j + 1; k < n; k++) {
                    st.insert(nums[i] ^ nums[j] ^ nums[k]);
                }
            }
        }

        return st.size();
    }
};
