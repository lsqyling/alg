#include "../utilities.hpp"


/**
 * 回溯算法（Backtracking）是一种系统地搜索所有（或部分）候选解的算法策略，
 * 常用于解决组合、排列、子集、约束满足等问题。它的核心思想是： “试错 + 撤销” —— 尝试每一种可能的选择，
 * 如果发现当前选择无法得到合法解，就撤销这个选择（回溯），尝试下一个。
 *
 * 核心思想
 * 回溯 = 递归 + 剪枝 + 状态恢复
 * 递归：逐层构建解（比如填数独、走迷宫、选数字）；
 * 剪枝：在递归过程中，如果当前路径已经不满足条件，就提前终止，避免无效搜索；
 * 状态恢复（回溯）：递归返回后，撤销上一步的操作，使状态回到之前，以便尝试其他选择。
 * 回溯的本质是 深度优先搜索（DFS） 在解空间树上的应用。
*/

namespace leetcode_37 {
// 37. Sudoku Solver
class Solution {
public:
    void solveSudoku(std::vector<std::vector<char>>& board) {
        backtrack(board);
    }
    bool backtrack(std::vector<std::vector<char>>& board) {
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                if (board[i][j] == '.') {
                    for (char c = '1'; c <= '9'; ++c) {
                        if (isvalid(board, i, j, c)) {
                            board[i][j] = c;
                            if (backtrack(board)) {
                                return true;
                            }
                            board[i][j] = '.';
                        }
                    }
                    return false;
                }
            }
        }
        return true;
    }
    bool isvalid(const std::vector<std::vector<char>> &board, int row, int col, char c) {
        // 检查行
        for (int j = 0; j < 9; ++j) {
            if (board[row][j] == c) {
                return false;
            }
        }
        // 检查列
        for (int i = 0; i < 9; ++i) {
            if (board[i][col] == c) {
                return false;
            }
        }
        // 检查3 X 3 宫格
        int startrow = (row / 3) * 3;
        int startcol = (col / 3) * 3;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (board[startrow+i][startcol+j] == c) {
                    return false;
                }
            }
        }
        return true;
    }
};
}

namespace leetcode_39 {
// 39. Combination Sum
class Solution {
public:
    std::vector<std::vector<int>> combinationSum(std::vector<int>& candidates, int target) {
        std::vector<std::vector<int>> result;
        std::vector<int> path;
        // 用于剪枝优化
        std::sort(candidates.begin(), candidates.end());
        backtrack(candidates, target, 0, path, result);
        return result;
    }

    void backtrack(const std::vector<int> &candidates, int target,
                   int index, std::vector<int> &path, std::vector<std::vector<int>> &result) {
        if (target == 0) {
            result.push_back(path);
            return;
        }
        for (int i = index; i < candidates.size(); ++i) {
            // 剪枝
            if (candidates[i] > target) {
                break;
            }
            path.push_back(candidates[i]);
            backtrack(candidates, target - candidates[i], i, path, result);
            path.pop_back();// 回溯
        }

    }
};
}

namespace leetcode_40 {
// 40. Combination Sum II
class Solution {
public:
    std::vector<std::vector<int>> combinationSum2(std::vector<int>& candidates, int target) {
        std::vector<int> path;
        std::vector<std::vector<int>> result;
        // 排序是去重和剪枝的前提
        std::sort(candidates.begin(), candidates.end());
        backtrack(candidates, target, 0, path, result);
        return result;
    }
    void backtrack(const std::vector<int> &candidates, int target,
                   int index, std::vector<int> &path, std::vector<std::vector<int>> &result) {
        if (target == 0) {
            result.push_back(path);
            return;
        }
        for (int i = index; i < candidates.size(); ++i) {
            // 剪枝：当前数字已超过剩余目标值
            if (candidates[i] > target) {
                break;
            }
            // 去重：跳过同一层中重复的元素
            if (i > index && candidates[i] == candidates[i-1]) {
                continue;
            }
            path.push_back(candidates[i]);
            // i+1：每个元素只能用一次
            backtrack(candidates, target - candidates[i], i + 1, path, result);
            path.pop_back();
        }
    }
};
}






int main(int argc, char *argv[]) {
    return 0;
}
