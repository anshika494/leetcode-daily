class Solution {
public:
    bool hasValidPath(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();

        vector<vector<int>> dirs = {
            {},
            {0, 1},
            {2, 3},
            {0, 3},
            {1, 3},
            {0, 2},
            {1, 2}
        };

        vector<pair<int,int>> moves = {
            {0, -1}, {0, 1}, {-1, 0}, {1, 0}
        };

        vector<int> opp = {1, 0, 3, 2};

        queue<pair<int,int>> q;
        vector<vector<bool>> vis(m, vector<bool>(n, false));

        q.push({0, 0});
        vis[0][0] = true;

        while (!q.empty()) {
            auto [x, y] = q.front();
            q.pop();

            if (x == m - 1 && y == n - 1)
                return true;

            int type = grid[x][y];

            for (int d : dirs[type]) {
                int nx = x + moves[d].first;
                int ny = y + moves[d].second;

                if (nx < 0 || ny < 0 || nx >= m || ny >= n)
                    continue;
                if (vis[nx][ny])
                    continue;

                int nextType = grid[nx][ny];

                for (int backDir : dirs[nextType]) {
                    if (backDir == opp[d]) {
                        vis[nx][ny] = true;
                        q.push({nx, ny});
                        break;
                    }
                }
            }
        }
        return false;
    }
};
