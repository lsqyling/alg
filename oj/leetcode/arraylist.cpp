//
// Created by 10580.
//
#include "../utilities.hpp"

namespace leetcode_2208 {
/*
 * 2208. Minimum Operations to Halve Array Sum
 * You are given an array nums of positive integers. In one operation, you can choose any number
 * from nums and reduce it to exactly half the number.
 * (Note that you may choose this reduced number in future operations.)
 *
 * Return the minimum number of operations to reduce the sum of nums by at least half.
 *
 */

class Solution {
public:
     static int halveArray(std::vector<int>& nums) {
        std::priority_queue<long> heap;
        long sum = 0;
        for (auto item: nums)
        {
            heap.push((long)item << 20);
            sum += ((long)item << 20);
        }
        sum /= 2;

        int ans = 0;
        for (long minus = 0, tmp; minus < sum; ++ans)
        {
            tmp = heap.top();
            heap.pop();
            tmp /= 2;
            minus += tmp;
            heap.push(tmp);
        }

        return ans;
    }
};
}















int main()
{
    return 0;
}

