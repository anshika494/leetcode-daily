class Solution {
public:
    int gcd(int a, int b) {

        while (b) {
            int temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }

    bool canMeasureWater(int x, int y, int target) {
        if (target > x + y)
            return false;

        if (target == 0)
            return true;
            
        return (target % gcd(x, y) == 0);        
    }
};
