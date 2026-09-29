class Solution {
public:
    bool hasValidPath(vector<vector<char>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        int len = m + n - 1;

        if (len % 2 != 0)
            return false;

        vector<vector<bool>> dp(n, vector<bool>(len + 1, false));

        // Starting cell must be '('
        if (grid[0][0] == ')')
            return false;

        dp[0][1] = true;

        for (int i = 0; i < m; i++) {

            vector<vector<bool>> cur(n, vector<bool>(len + 1, false));

            for (int j = 0; j < n; j++) {

                if (i == 0 && j == 0) {
                    cur[0][1] = true;
                    continue;
                }

                int change = (grid[i][j] == '(') ? 1 : -1;

                for (int prevBalance = 0; prevBalance <= len; prevBalance++) {

                    bool canReach = false;

                    if (i > 0 && dp[j][prevBalance]) {
                        canReach = true;
                    }

                    if (j > 0 && cur[j - 1][prevBalance]) {
                        canReach = true;
                    }

                    if (!canReach)
                        continue;

                    int newBalance = prevBalance + change;

                    if (newBalance < 0)
                        continue;

                    if (newBalance > len)
                        continue;

                    cur[j][newBalance] = true;
                }
            }

            dp = move(cur);
        }

        return dp[n - 1][0];
    }
};
