#include "../utilities.hpp"

/**
 * 排序作为一种基础而强大的预处理手段，在算法和编程问题中具有广泛的应用价值。
 * 虽然排序本身不直接解决问题，但它能简化问题结构、暴露规律、降低复杂度，从而帮助我们更高效地求解。
 *
 * 排序在各类典型题目中的作用及对应题型：
 * 1. 双指针 / 两数之和类问题
 * 2. 贪心算法类问题
 * 3. 区间合并 / 调度类问题
 * 4. 查找第 K 大 / Top-K 问题
 *
*/

namespace leetcode_56 {
// 56. 合并区间
class Solution {
public:
    std::vector<std::vector<int>> merge(std::vector<std::vector<int>>& intervals) {
        // 第一步：按起始位置排序
        auto cmp = [](const std::vector<int> &a, const std::vector<int> &b) {
            return a[0] < b[0];
        };
        std::sort(intervals.begin(), intervals.end(), cmp);

        // 第二步：合并重叠区间
        std::vector<std::vector<int>> overlap;
        overlap.push_back(intervals[0]);

        for (int i = 1; i < intervals.size(); ++i) {
            int curr_start = intervals[i][0];
            int curr_end = intervals[i][1];
            auto &last_overlap = overlap.back();
            int lastend = last_overlap[1];
            if (curr_start <= lastend) {
                // 重叠或相连，合并
                last_overlap[1] = std::max(lastend, curr_end);
            }
            else {
                // 不重叠，加入新区间
                overlap.push_back(intervals[i]);
            }
        }
        return overlap;
    }
};
}

namespace leetcode_57 {
// v57. 插入区间
class Solution {
public:
    std::vector<std::vector<int>> insert(std::vector<std::vector<int>>& intervals, std::vector<int>& newInterval) {
        std::vector<std::vector<int>> result;
        int i = 0, n = intervals.size();

        // 1. Add all intervals ending before newInterval starts (no overlap)
        while (i < n && intervals[i][1] < newInterval[0]) {
            result.push_back(intervals[i]);
            ++i;
        }
        // 2. Merge all overlapping intervals with newInterval
        // Now intervals[i][0] <= newInterval[1] (they may overlap)
        while (i < n && intervals[i][0] < newInterval[1]) {
            newInterval[0] = std::min(newInterval[0], intervals[i][0]);
            newInterval[1] = std::min(newInterval[1], intervals[i][1]);
            ++i;
        }
        result.push_back(newInterval);
        // 3. Add all intervals starting after newInterval ends (no overlap)
        while (i < n) {
            result.push_back(intervals[i]);
            ++i;
        }
        return result;
    }
};
}






























int main() {
    return 0;
}