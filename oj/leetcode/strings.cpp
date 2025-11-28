#include "../utilities.hpp"

/**
* 字符串相关的专题
*/

namespace leetcode_38 {
// 38. Count and Say
class Solution {
public:
    std::string countAndSay(int n) {
        if (n == 1) {
            return "1";
        }
        std::string cur = "1";
        for (int i = 2; i <= n; ++i) {
            std::string next;
            int len = cur.size();
            int j = 0;

            while (j < len) {
                char c = cur[j];
                int count = 0;
                // 统计连续相同字符的个数
                while (j < len && cur[j] == c) {
                    ++count;
                    ++j;
                }
                next += std::to_string(count) + c;
            }
            cur = next;
        }
        return cur;
    }
};
}

namespace leetcode_43 {
// 43. Multiply Strings
class Solution {
public:
    std::string multiply(std::string num1, std::string num2) {
    }
};
}


















int main(int argc, char *argv[]) {
    return 0;
}