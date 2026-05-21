class Solution {
public:
    int longestCommonPrefix(vector<int>& arr1, vector<int>& arr2) {

        unordered_set<string> prefixes;

        for (int num : arr1) {
            string s = to_string(num);

            string pref = "";

            for (char ch : s) {
                pref += ch;
                prefixes.insert(pref);
            }
        }

        int ans = 0;

        for (int num : arr2) {
            string s = to_string(num);

            string pref = "";

            for (int i = 0; i < s.size(); i++) {
                pref += s[i];

                if (prefixes.count(pref)) {
                    ans = max(ans, i + 1);
                }
            }
        }

        return ans;
    }
};
