#include <array>
#include "../utilities.hpp"
/**
 * 简单模拟和复杂模拟：
 * 核心：理解题意，构造合适解题模型
 *
 * 在计算机算法中，“模拟”（Simulation） 是一种直接按照题目描述的过程、规则或现实场景，
 * 一步一步地用程序复现其行为的解题思想。
 * 它不依赖复杂的数学公式、数据结构优化或高级算法技巧，而是忠实还原问题本身的逻辑流程。
 *
*/

namespace leetcode_36 {
// 36. Valid Sudoku
class Solution {
public:
    bool isValidSudoku(std::vector<std::vector<char>>& board) {
        std::array<std::array<int, 10>, 10> a, b, c;
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                if (std::isdigit(board[i][j])) {
                    int k = board[i][j] - '0';
                    if (++a[i][k] == 2 || ++b[j][k] == 2 || ++c[i/3*3+j/3][k] == 2) {
                        return false;
                    }
                }
            }
        }
        return true;
    }
};
}

namespace leetcode_48 {
// 48. Rotate Image
class Solution {
public:
    void rotate(std::vector<std::vector<int>>& matrix) {
        int n = matrix.size();

        // 转置
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                std::swap(matrix[i][j], matrix[j][i]);
            }
        }
        // 反转行
        for (int i = 0; i < n; ++i) {
            std::reverse(matrix[i].begin(), matrix[i].end());
        }
    }
};
}

namespace leetcode_54 {
// 54. 螺旋矩阵
class Solution {
public:
    std::vector<int> spiralOrder(std::vector<std::vector<int>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();

        int top = 0, bottom = m - 1;
        int left = 0, right = n - 1;

        std::vector<int> result;
        while (top <= bottom && left <= right) {
            // left -> right
            for (int i = left; i <= right; ++i) {
                result.push_back(matrix[top][i]);
            }
            ++top;
            // top -> bottom
            for (int i = top; i <= bottom; ++i) {
                result.push_back(matrix[i][right]);
            }
            --right;
            if (top <= bottom) {
                // right -> left
                for (int i = right; i >= left; --i) {
                    result.push_back(matrix[bottom][i]);
                }
                --bottom;
            }
            if (left <= right) {
                // bottom -> top
                for (int i = bottom; i >= top; --i) {
                    result.push_back(matrix[i][left]);
                }
                ++left;
            }
        }
        return result;
    }
};
}

namespace leetcode_59 {
// 59. 螺旋矩阵 II
class Solution {
public:
    std::vector<std::vector<int>> generateMatrix(int n) {
        std::vector<std::vector<int>> matrix(n, std::vector<int>(n));
        int top = 0, bottom = n - 1;
        int left = 0, right = n - 1;
        int num = 1;
        const int total = n * n;

        while (num <= total) {
            // 1. 从左到右（top 行）
            for (int i = left; i <= right; ++i) {
                matrix[top][i] = num++;
            }
            ++top;
            // 2. 从上到下（right 列）
            for (int i = top; i <= bottom; ++i) {
                matrix[i][right] = num++;
            }
            --right;
            // 3. 从右到左（bottom 行）
            for (int i = right; i >= left; --i) {
                matrix[bottom][i] = num++;
            }
            --bottom;
            // 4. 从下向上（left 列）
            for (int i = bottom; i >= top; --i) {
                matrix[i][left] = num++;
            }
            ++left;
        }

        return matrix;
    }
};
}



































int main(int argc, char *argv[]) {
    return 0;
}