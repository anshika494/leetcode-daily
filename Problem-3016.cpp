class Solution {
public:
    int minimumPushes(string word) {
        vector<int> anFreq(26, 0);

        for (char anCh : word)
            anFreq[anCh - 'a']++;

        sort(anFreq.begin(), anFreq.end(), greater<int>());

        int anAns = 0;

        for (int anI = 0; anI < 26; anI++) {
            if (anFreq[anI] == 0) break;
            anAns += anFreq[anI] * (anI / 8 + 1);
        }

        return anAns;
    }
};
