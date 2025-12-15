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
        // 特殊情况：任意数 为0，结果为0
        if (num1 == "0" || num2 == "0") {
            return "0";
        }
        int m = num1.size();
        int n = num2.size();
        // 最多 n + m 位
        std::vector<int> pos(n + m, 0);

        // 从右向左遍历字符
        for (int i = m - 1; i >= 0; --i) {
            for (int j = n - 1; j >= 0; --j) {
                int mul = (num1[i] - '0') * (num2[j] - '0');
                int p1 = i + j;    // 高位
                int p2 = i + j + 1;    // 低位
                int sum = mul + pos[p2]; // 加上已有的值

                pos[p2] = sum % 10;
                pos[p1] += sum / 10;
            }
        }
        // 转换为字符串
        std::string result;
        int i = 0;
        while (i < pos.size() - 1 && pos[i] == 0) {
            ++i;
        }
        for (; i < pos.size(); ++i) {
            result += static_cast<char>(pos[i] + '0');
        }
        return result;
    }
};
}

namespace leetcode_49 {
// 49. Group Anagrams
class Solution {
public:
    std::vector<std::vector<std::string>> groupAnagrams(std::vector<std::string>& strs) {
        std::unordered_map<std::string, std::vector<std::string>> groups;
        for (auto &str : strs) {
            std::string key = str;
            std::sort(key.begin(), key.end());
            groups[key].push_back(str);
        }
        std::vector<std::vector<std::string>> result;
        for (auto &pair : groups) {
            result.push_back(std::move(pair.second));
        }
        return result;
    }
};
}

namespace leetcode_58 {
// 58. 最后一个单词的长度
class Solution {
public:
    int lengthOfLastWord(std::string s) {
        int n = s.size();
        int i = n - 1;

        // 1. 跳过末尾的空格
        while (i >= 0 && s[i] == ' ') {
            --i;
        }
        // 2. 统计最后一个单词的长度
        int len = 0;
        while (i >= 0 && s[i] != ' ') {
            ++len;
            --i;
        }
        return len;
    }
};
}















int main(int argc, char *argv[]) {
    return 0;
}