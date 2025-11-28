#include <array>
#include "../utilities.hpp"
/**
 * 简单模拟和复杂模拟：
 * 核心：理解题意，构造合适解题模型
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





















int main(int argc, char *argv[]) {
    return 0;
}