class Solution {
public:
    vector<vector<char>> rotateTheBox(vector<vector<char>>& boxGrid) {
        int m = boxGrid.size();
        int n = boxGrid[0].size();

        vector<vector<char>> result(n, vector<char>(m, '.'));

        for (int i = 0; i < m; i++) {
            int emptyPos = n - 1;
            for (int j = n - 1; j >= 0; j--) {
                if (boxGrid[i][j] == '*') {
                    result[j][m - 1 - i] = '*';
                    emptyPos = j - 1;
                }

                else if (boxGrid[i][j] == '#') {
                    result[emptyPos][m - 1 - i] = '#';
                    emptyPos--;

                }
            }
        }
        return result;        
    }
};
