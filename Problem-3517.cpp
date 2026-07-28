class Solution {
public:
    string smallestPalindrome(string s) {
        vector<int> anFreq(26, 0);

        for (char anCh : s)
            anFreq[anCh - 'a']++;

        string anHalf = "", anMid = "";

        for (int anI = 0; anI < 26; anI++) {
            if (anFreq[anI] % 2)
                anMid = char('a' + anI);

            anHalf.append(anFreq[anI] / 2, char('a' + anI));
        }

        string anRev = anHalf;
        reverse(anRev.begin(), anRev.end());

        return anHalf + anMid + anRev;
    }
};
