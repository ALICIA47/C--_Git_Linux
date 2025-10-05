class Solution {
public:
    int reverse(int x) {
        int n = 0;
        int max = 2147483647;
        int min = -2147483648;

        while (x != 0) {
            int pop = x % 10;
            x /= 10;

            if (n > max / 10 || (n == max / 10 && pop > 7)) return 0;
            if (n < min / 10 || (n == min / 10 && pop < -8)) return 0;

            n = n * 10 + pop;
        }

        return n;
    }
};