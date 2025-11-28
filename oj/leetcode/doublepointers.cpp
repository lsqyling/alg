#include "../utilities.hpp"

/**
 * 双指针法，顾名思义，就是在算法中同时使用两个指针（或者索引）来遍历数据结构（通常是数组、链表或字符串），
 * 以达到特定目的。
 *
 * 双指针法的核心思想是通过用空间换时间的方式，将原本需要多重循环（O(n²) 时间复杂度）的问题，
 * 优化为通过单次或更少次数的遍历（O(n) 时间复杂度）来解决。它通过巧妙地移动两个指针，排除不必要的计算，
 * 从而显著提高算法效率。
 */

namespace leetcode_31 {
// 31. Next Permutation
class Solution {
public:
    void nextPermutation(std::vector<int>& nums) {
        // step1. 从右向左找到第一个下降的位置 nums[i] < nums[i+1]
        int i = nums.size() - 2;
        while (i >= 0 && nums[i] >= nums[i+1]) {
            --i;
        }
        if (i >= 0) {
            // step2. 从右向左找到第一个大于 nums[i] 的 nums[j]
            int j = nums.size() - 1;
            while (nums[j] <= nums[i]) {
                --j;
            }
            // step3. 交换
            std::swap(nums[i], nums[j]);
        }
        // Step 4: 反转 i+1 到末尾
        std::reverse(nums.begin() + i + 1, nums.end());
    }
};
}





















int main(int argc, char *argv[]) {
    return 0;
}