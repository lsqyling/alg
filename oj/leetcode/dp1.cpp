#include "../utilities.hpp"

/**
 * 动态规划（Dynamic Programming，简称 DP）是一种用于求解具有重叠子问题和最优子结构特性的优化问题的算法设计思想。
 * 其核心思想是将复杂问题分解为更小的子问题，通过保存子问题的解避免重复计算，从而高效地求得原问题的最优解。
 *
 *
*/


namespace leetcode_44 {
// 44. Wildcard Matching
class Solution {
public:
    bool isMatch(std::string s, std::string p) {
         int m = s.size(), n = p.size();
         // 定义 dp[i][j] 表示 s 的前 i 个字符和 p 的前 j 个字符是否匹配。
         std::vector<std::vector<bool>> dp(m + 1, std::vector<bool>(n + 1, false));
         // 空字符串和空模式匹配
         dp[0][0] = true;
         // 处理模式以 * 开头的情况，例如 "***a"
         for (int j = 1; j <= n; ++j) {
             if (p[j-1] == '*') {
                 dp[0][j] = dp[0][j-1];
             }
         }
         for (int i = 1; i <= m; ++i) {
             for (int j = 1; j <= n; ++j) {
                 if (p[j-1] == '?' || p[j-1] == s[i-1]) {
                     dp[i][j] = dp[i-1][j-1];
                 }
                 else if (p[j-1] == '*') {
                     dp[i][j] = dp[i-1][j] || dp[i][j-1];
                 }
             }
         }
         return dp[m][n];
    }
};
}

namespace leetcode_62 {
// 62. 不同路径
class Solution {
public:
    int uniquePaths(int m, int n) {
        // 设 dp[i][j] 表示从 (0,0) 到 (i,j) 的不同路径数。
        std::vector<std::vector<int>> dp(m, std::vector<int>(n, 1));
        // 初始化
        // 第一行：只能一直向右 → dp[0][j] = 1
        // 第一列：只能一直向下 → dp[i][0] = 1
        //  状态转移方程
        // dp[i][j] = dp[i-1][j] + dp[i][j-1]
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                dp[i][j] = dp[i-1][j] + dp[i][j-1];
            }
        }

        return dp[m-1][n-1];
    }
};
}

namespace leetcode_63 {
// 63. 不同路径 II
class Solution {
public:
    int uniquePathsWithObstacles(std::vector<std::vector<int>>& obstacleGrid) {
        int m = obstacleGrid.size();
        int n = obstacleGrid[0].size();

        // 起点或终点有障碍，直接返回 0
        if (obstacleGrid[0][0] == 1 || obstacleGrid[m-1][n-1] == 1) {
            return 0;
        }
        // 设 dp[i][j] 表示从 (0,0) 到 (i,j) 的不同路径数。
        std::vector<std::vector<long>> dp(m, std::vector<long>(n, 0));
        // 初始化起点
        dp[0][0] = 1;
        // 初始化第一行
        for (int j = 1; j < n; ++j) {
            if (obstacleGrid[0][j] == 0) {
                dp[0][j] = dp[0][j-1]; // 只能从左边来
            }
            // 否则保持0（有障碍）
        }
        // 初始化第一列
        for (int i = 1; i < m; ++i) {
            if (obstacleGrid[i][0] == 0) {
                dp[i][0] = dp[i-1][0]; // 只能从上面来
            }
            // 否则保持0 （有障碍）
        }
        // 填充其余格子
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                if (obstacleGrid[i][j] == 0) {
                    dp[i][j] = dp[i-1][j] + dp[i][j-1];
                }
                // 否则 dp[i][j] 保持 0
            }
        }

        return dp[m-1][n-1];
    }
};
}






































int main(int argc, char *argv[]) {
    return 0;
}