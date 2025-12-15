#include "../utilities.hpp"
/**
 * 贪心算法（Greedy Algorithm）是一种在每一步选择中都采取当前状态下最优（或局部最优）的选择，
 * 从而希望最终得到全局最优解的算法策略。
 *
 * 贪心算法的核心思想是： “只看眼前，不考虑未来” —— 在每一步决策时，都做出在当前看来最好的选择，
 * 而不回溯、不重新考虑之前的决策。
 *
 * 虽然贪心算法不能保证对所有问题都能得到全局最优解，但对于某些特定类型的问题（具有贪心选择性质和最优子结构），
 * 它确实能高效地求出最优解。
 */

namespace leetcode_55 {
// 55. 跳跃游戏
class Solution {
public:
    bool canJump(std::vector<int>& nums) {
        int n = nums.size();
        if (n <= 1) {
            // 已经在终点
            return true;
        }
        // 当前能到达的最远下标
        int max_reach = 0;
        for (int i = 0;i < n; ++i) {
            // 如果当前位置不可达，提前结束
            if (max_reach < i) {
                return false;
            }
            // 更新最远可达位置
            max_reach = std::max(max_reach, i + nums[i]);
            // 如果已经能到达或超过最后一个下标
            if (max_reach >= n - 1) {
                return true;
            }
        }
        return false;
    }
};
}

namespace leetcode_60 {
// 60. 排列序列
class Solution {
public:
    std::string getPermutation(int n, int k) {
        // 预计算阶乘：fact[i] = i!
        std::vector<int> fact(n, 1);
        for (int i = 1; i < n; ++i) {
            fact[i] = fact[i-1] * i;
        }

        // 初始化可用数字 [1, 2, ..., n]
        std::vector<int> nums;
        for (int i = 1; i <= n; ++i) {
            nums.push_back(i);
        }

        std::string result;
        --k; // 转为0-based

        // 从高位到低位确定每一位
        for (int i = n - 1; i >= 0; --i) {
            int index = i / fact[i];
            k %= fact[i];

            result += std::to_string(nums[index]);
            nums.erase(nums.begin() + index);
        }

        return result;
    }
};
}


















int main() {
    return 0;
}
