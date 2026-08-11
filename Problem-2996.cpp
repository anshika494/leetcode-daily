class Solution {
public:
    int missingInteger(vector<int>& nums) {
        int anSum = nums[0];

        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] == nums[i - 1] + 1)
                anSum += nums[i];
            else
                break;
        }

        unordered_set<int> anSet(nums.begin(), nums.end());

        while (anSet.count(anSum))
            anSum++;

        return anSum;
    }
};
