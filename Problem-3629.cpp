class Solution {
public:
    bool isPrime(int x) {

        if (x < 2)
            return false;
        if (x == 2)
            return true;
        if (x % 2 == 0)
            return false;

        for (int i = 3; i * i <= x; i += 2) {
            if (x % i == 0) return false;
        }
        return true;
    }

    int minJumps(vector<int>& nums) {

        int n = nums.size();
        unordered_map<int, vector<int>> divisibleIndices;
        vector<vector<int>> factors(n);

        for (int i = 0; i < n; i++) {
            int x = nums[i];
            for (int p = 2; p * p <= x; p++) {
                if (x % p == 0) {
                    factors[i].push_back(p);
                    while (x % p == 0)
                        x /= p;
                }
            }

            if (x > 1)
                factors[i].push_back(x);

            for (int p : factors[i]) {
                divisibleIndices[p].push_back(i);
            }
        }

        vector<int> dist(n, INT_MAX);
        queue<int> q;

        dist[0] = 0;
        q.push(0);

        unordered_set<int> usedPrime;

        while (!q.empty()) {
            int i = q.front();
            q.pop();
            int steps = dist[i];

            if (i == n - 1)
                return steps;

            if (i - 1 >= 0 && dist[i - 1] == INT_MAX) {
                dist[i - 1] = steps + 1;
                q.push(i - 1);
            }

            if (i + 1 < n && dist[i + 1] == INT_MAX) {
                dist[i + 1] = steps + 1;
                q.push(i + 1);
            }

            if (isPrime(nums[i])) {
                int p = nums[i];

                if (!usedPrime.count(p)) {
                    usedPrime.insert(p);
                    for (int nxt : divisibleIndices[p]) {
                        if (dist[nxt] == INT_MAX) {
                            dist[nxt] = steps + 1;
                            q.push(nxt);
                        }
                    }
                }
            }
        }
        return -1;
    }
};
