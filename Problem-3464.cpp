class Solution {
public:
    int maxDistance(int side, vector<vector<int>>& points, int k) {
        long long perimeter = 4LL * side;
        int n = points.size();

        auto toArc = [&](int x, int y) -> long long {
            if (y == 0)
                return x;
            if (x == side)
                return (long long)side + y;
            if (y == side)
                return 2LL * side + (side - x);
            return 3LL * side + (side - y);
        };

        vector<long long> arc(n);
        for (int i = 0; i < n; i++)
            arc[i] = toArc(points[i][0], points[i][1]);
        sort(arc.begin(), arc.end());

        auto feasible = [&](long long d) -> bool {
            vector<long long> arc2;
            arc2.reserve(2 * n);
            for (auto v : arc)
                arc2.push_back(v);
            for (auto v : arc)
                arc2.push_back(v + perimeter);

            for (int s = 0; s < n; s++) {
                long long first = arc2[s];
                long long last  = first;
                int cnt = 1;

                for (int pick = 1; pick < k; pick++) {
                    long long need = last + d;
                    auto it = lower_bound(arc2.begin() + s + 1, arc2.end(), need);
                    if (it == arc2.end() || *it > first + perimeter - d) {
                        cnt = 0;
                        break;
                    }
                    last = *it;
                    cnt++;
                }

                if (cnt == k)
                    return true;
            }
            return false;
        };

        long long lo = 1, hi = perimeter / 2, ans = 0;
        while (lo <= hi) {
            long long mid = lo + (hi - lo) / 2;
            if (feasible(mid)) {
                ans = mid;
                lo = mid + 1; }
            else
                hi = mid - 1;
        }
        return (int)ans;
    }
};
