class Solution {
public:
    int maxProduct(int n) {
        int anMax1 = 0, anMax2 = 0;

        while (n > 0) {
            int anDigit = n % 10;

            if (anDigit >= anMax1) {
                anMax2 = anMax1;
                anMax1 = anDigit;
            } else if (anDigit > anMax2) {
                anMax2 = anDigit;
            }

            n /= 10;
        }

        return anMax1 * anMax2;
    }
};
