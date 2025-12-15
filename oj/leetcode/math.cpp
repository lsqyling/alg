#include "../utilities.hpp"

/**
 *
 * 数学方面的算法: 最大公约数，最小公倍数，快速幂，排列
*/


namespace leetcode_50 {
// 50. Pow(x, n)
class Solution {
public:
    double myPow(double x, int n) {
        // 转换 n 为 long long 防止 -2^31 取反溢出
        long long exp = n;
        if (exp < 0) {
            x = 1.0 / x;
            exp = -exp;
        }

        double result = 1.0;
        double base = x;

        while (exp > 0) {
            if (exp & 1) {
                result *= base;
            }
            base *= base;
            exp >>= 1;
        }

        return result;
    }
};
}


















int main() {
    return 0;
}