class Solution {
public:
    bool findSafeWalk(vector<vector<int>>& grid, int health) {
        int m = grid.size();
        int n = grid[0].size();

        int startHealth = health - grid[0][0];

        if (startHealth <= 0)
            return false;

        vector<vector<int>> best(m, vector<int>(n, -1));
        queue<pair<pair<int, int>, int>> q;

        best[0][0] = startHealth;
        q.push({{0, 0}, startHealth});

        int dr[4] = {-1, 1, 0, 0};
        int dc[4] = {0, 0, -1, 1};

        while (!q.empty()) {
            auto cur = q.front();
            q.pop();

            int r = cur.first.first;
            int c = cur.first.second;
            int remHealth = cur.second;

            if (r == m - 1 && c == n - 1)
                return true;

            for (int k = 0; k < 4; k++) {
                int nr = r + dr[k];
                int nc = c + dc[k];

                if (nr < 0 || nr >= m || nc < 0 || nc >= n)
                    continue;

                int newHealth = remHealth - grid[nr][nc];

                if (newHealth <= 0)
                    continue;

                if (newHealth > best[nr][nc]) {
                    best[nr][nc] = newHealth;
                    q.push({{nr, nc}, newHealth});
                }
            }
        }

        return false;
    }
};
