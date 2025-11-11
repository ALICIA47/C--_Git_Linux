class Solution {
public:
    int divide(int dividend, int divisor) {
        // 处理特殊情况：如果被除数是 INT_MIN 且除数是 -1，会导致溢出
        if (dividend == INT_MIN && divisor == -1) {
            return INT_MAX; 
        }

        // 确定结果的符号：如果被除数和除数异号，结果为负
        bool negative = (dividend > 0) ^ (divisor > 0);

        // 将被除数和除数转换为负数，避免溢出
        long long dividend_ll = abs((long long)dividend);
        long long divisor_ll = abs((long long)divisor);

        long long result = 0;
        while (dividend_ll >= divisor_ll) {
            long long temp = divisor_ll;
            long long multiple = 1;
            // 尝试找到最大的倍数，使得 (temp << 1) 仍然小于等于被除数
            while (dividend_ll >= (temp << 1)) {
                temp <<= 1;
                multiple <<= 1;
            }
            // 减去找到的最大倍数
            dividend_ll -= temp;
            // 累加倍数到结果中
            result += multiple;
        }

        // 根据符号返回结果
        return negative ? -result : result;
    }
};
