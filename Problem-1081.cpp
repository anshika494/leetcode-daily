class Solution {
public:
    string smallestSubsequence(string s) {
        vector<int> freq(256, 0);
        vector<bool> visited(256, false);

        for (char c : s)
            freq[c]++;

        string st;

        for (char c : s) {
            freq[c]--;

            if (visited[c])
                continue;

            while (!st.empty() && st.back() > c && freq[st.back()] > 0) {
                visited[st.back()] = false;
                st.pop_back();
            }

            st.push_back(c);
            visited[c] = true;
        }

        return st;
    }
};
