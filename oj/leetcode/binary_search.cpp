#include "../utilities.hpp"

/**
 * 二分查找（Binary Search）是一种在有序数组中查找特定元素的高效算法。
 * 它的核心思想是"分而治之"——通过不断将搜索区间减半来快速定位目标元素。
 *
 * 算法特性 时间复杂度：O(log n) 空间复杂度：O(1) - 迭代版本
 * 前提条件：数组必须是有序的 优点：查找效率极高 缺点：要求数据有序，不适合频繁插入删除的场景
 */

// find x in arr[L, R], returns the pos of x, otherwise returns -1;
int find(const std::vector<int> &arr, int x)
{
    int l = 0, r = arr.size() - 1, m;
    while (l <= r)
    {
        m = l + ((r - l) >> 1);
        if (x < arr[m])
            r = m - 1;
        else if (arr[m] < x)
            l = m + 1;
        else
            return m;
    }
    return -1;
}


//  find >= x in arr[L, R], returns the pos, otherwise -1 instead.
int find_left(const std::vector<int> &arr, int x)
{
    int l = 0, r = arr.size() - 1, m;
    int pos = -1;
    while (l <= r)
    {
        m = l + (r - l) / 2;
        if (x <= arr[m])
        {
            pos = m;
            r = m - 1;
        }
        else
            l = m + 1;
    }
    return pos;
}

//  find <= x in arr[L, R], returns the rightmost pos, otherwise -1 instead.
int find_right(const std::vector<int> &arr, int x)
{
    int l = 0, r = arr.size() - 1, m;
    int pos = -1;
    while (l <= r)
    {
        m = l + (r - l) / 2;
        if (arr[m] <= x)
        {
            pos = m;
            l = m + 1;
        }
        else
            r = m - 1;
    }
    return pos;
}

void test_finds()
{
    std::vector<int> arr{0, 3, 4, 6, 8, 12, 15, 21, 21, 21, 23, 25};
    std::cout << std::format("23 pos: {}\n", find(arr, 23));
    std::cout << std::format("22 pos: {}\n", find(arr, 22));

    std::cout << std::format(">=26 left pos: {}\n", find_left(arr, 26));
    std::cout << std::format("<=21 right pos: {}\n", find_right(arr, 21));
}

namespace leetcode_33 {
// 33. Search in Rotated Sorted Array
class Solution {
public:
    int search(std::vector<int>& nums, int target) {
        int left = 0, right = nums.size() - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (target == nums[mid]) {
                return mid;
            }
            // 判断左部分是否有序
            if (nums[left] <= nums[mid]) {
                // 左部分 [left, mid] 有序
                if (nums[left] <= target && target < nums[mid]) {
                    right = mid - 1;
                }
                else {
                    left = mid + 1;
                }
            }
            else {
                // 右部分有序
                if (nums[mid] < target && target <= nums[right]) {
                    left = mid + 1;
                }
                else {
                    right = mid - 1;
                }
            }
        }
        return -1;
    }
};
}

namespace leetcode_34 {
// 34. Find First and Last Position of Element in Sorted Array
class Solution {
public:
    std::vector<int> searchRange(std::vector<int>& nums, int target) {
        if (nums.empty()) {
            return {-1, -1};
        }
        int left = find_left(nums, target);
        if (left == -1) {
            return {-1, -1};
        }
        int right = find_right(nums, target);
        return {left, right};
    }
    int find_left(const std::vector<int> &nums, int target) {
        int left = 0, right = nums.size() - 1;
        int pos = -1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (target == nums[mid]) {
                pos = mid;
                right = mid - 1;
            }
            else if (nums[mid] < target) {
                left = mid + 1;
            }
            else {
                right = mid - 1;
            }
        }
        return pos;
    }
    int find_right(const std::vector<int> &nums, int target) {
        int left = 0, right = nums.size() - 1;
        int pos = -1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] == target) {
                pos = mid;
                left = mid + 1;
            }
            else if (nums[mid] < target) {
                left = mid + 1;
            }
            else {
                right = mid - 1;
            }
        }
        return pos;
    }
};
}

namespace leetcode_35 {
// 35. Search Insert Position
class Solution {
public:
    int searchInsert(std::vector<int>& nums, int target) {
        int left = 0, right = nums.size();
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] >= target) {
                right = mid;
            }
            else {
                left = mid + 1;
            }
        }
        return left;
    }
};
}

namespace leetcode_162 {
//162. Find Peak Element
class Solution
{
public:
    int findPeakElement(std::vector<int> &nums)
    {
        int n = nums.size();
        if (n == 1)
            return 0;
        if (nums[0] > nums[1])
            return 0;
        if (nums[n-1] > nums[n-2])
            return n - 1;

        int l = 0, r = n - 1, m;
        while (l <= r)
        {
            m = l + (r - l) / 2;
            if (nums[m+1] > nums[m])
                l = m;
            else if (nums[m-1] > nums[m])
                r = m;
            else
                return m;
        }
        return  -1;
    }
};
}


int main()
{
    test_finds();

    return 0;
}









