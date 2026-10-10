class Solution {
public:
    long long minSumSquareDiff(vector<int>& nums1, vector<int>& nums2, int k1, int k2) {
        int n = nums1.size();

        priority_queue<int> pq;
        for (int i = 0; i < n; ++i) {
            pq.push(abs(nums1[i] - nums2[i]));
        }

        int K = k1 + k2;

        while (K > 0 && pq.top() > 0) {
            int largestDiff = pq.top();
            pq.pop();
            pq.push(largestDiff - 1);
            K--;
        }

        long long result = 0;
        while (!pq.empty()) {
            long long d = pq.top();
            pq.pop();
            result += d * d;
        }

        return result;
    }
};
