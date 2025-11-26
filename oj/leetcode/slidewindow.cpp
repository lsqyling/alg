#include "../utilities.hpp"

/**
 * 滑动窗口相关的题目
 * 滑动窗口的关键：找到 范围 和答案指标 之间的 单调性关系 (类似贪心)
 * 滑动过程：滑动窗口可以用简单变量或者结构来维护信息
 * 求解大流程：求子数组在每个位置开头或结尾情况下的答案(开头还是结尾在于个人习惯)
 */

namespace leetcode_3 {
// 3. Longest Substring Without Repeating Characters
class Solution {
public:
    static int lengthOfLongestSubstring(std::string s) {
        // 设置字符上次出现的位置 数组
        std::vector<int> last(256, -1);
        int ans = 0;
        for (int l = 0, r = 0; r < s.size(); ++r) {
            l = std::max(l, last[s[r]] + 1);
            last[s[r]] = r;
            ans = std::max(ans, r - l + 1);
        }
        return ans;
    }
};
}

namespace leetcode_11 {
//11. Container With Most Water
class Solution {
public:
    static int maxArea(std::vector<int>& height) {
        int n = (int)height.size();
        int ans = 0;

        for (int l = 0, r = n - 1; l < r; )
        {
            ans = std::max(ans, std::min(height[l], height[r]) * (r - l));
            if (height[l] <= height[r])
                ++l;
            else
                --r;
        }

        return ans;
    }
};
}

namespace leetcode_30 {
// 30. Substring with Concatenation of All Words
class Solution {
public:
    std::vector<int> findSubstring(std::string s, std::vector<std::string>& words) {
        if (s.empty() || words.empty()) return {};

        int wordlen = words[0].size();
        int wordcount = words.size();
        int totallen = wordlen * wordcount;
        int n = s.size();

        if (totallen > n) return {};

        // 统计 words 中每个单词的出现次数
        std::unordered_map<std::string, int> wordfreq;
        for (const auto& word : words) {
            ++wordfreq[word];
        }

        std::vector<int> result;

        // 遍历所有可能的起始偏移：0 到 wordlen - 1
        for (int i = 0; i < wordlen; ++i) {
            std::unordered_map<std::string, int> windowfreq;
            int left = i;          // 窗口左边界（字符索引）
            int wordnum = 0;       // 当前窗口中有效单词的数量

            // j 是当前待加入窗口的单词起始位置（步长为 wordLen）
            for (int j = i; j <= n - wordlen; j += wordlen) {
                std::string word = s.substr(j, wordlen);

                if (wordfreq.count(word)) {
                    ++windowfreq[word];
                    ++wordnum;

                    // 如果该单词数量超过所需，收缩窗口左侧
                    while (windowfreq[word] > wordfreq[word]) {
                        std::string leftWord = s.substr(left, wordlen);
                        --windowfreq[leftWord];
                        --wordnum;
                        left += wordlen;
                    }

                    // 如果窗口中单词数量正好等于所需总数，记录起始位置
                    if (wordnum == wordcount) {
                        result.push_back(left);
                    }
                } else {
                    // 遇到不在 words 中的单词，重置窗口
                    windowfreq.clear();
                    wordnum = 0;
                    left = j + wordlen; // 下一个可能的起点
                }
            }
        }

        return result;
    }
};
}

namespace leetcode_41 {
//41. First Missing Positive
class Solution {
public:
    static int firstMissingPositive(std::vector<int>& nums) {
        int l = 0;
        int r = (int)nums.size();

        while (l < r)
        {
            if (nums[l] == l + 1)
                ++l;
            else if (nums[l] <= l || nums[l] > r || nums[nums[l]-1] == nums[l])
                std::swap(nums[l], nums[--r]);
            else
                std::swap(nums[l], nums[nums[l]-1]);
        }

        return l + 1;
    }
};
}

namespace leetcode_42 {
//42. Trapping Rain Water
class Solution {
public:
    static int trap(std::vector<int>& height) {
        int n = (int)height.size();
        std::vector<int> left(n);
        std::vector<int> right(n);
        left[0] = height[0];
        for (int i = 1; i < n; ++i)
            left[i] = std::max(left[i-1], height[i]);
        right[n-1] = height[n-1];
        for (int j = n - 2; j >= 0; --j)
            right[j] = std::max(right[j+1], height[j]);

        int ans = 0;
        for (int i = 1; i < n - 1; ++i)
        {
            ans += std::max( std::min(left[i], right[i]) - height[i], 0 );
        }

        return ans;
    }

    static int trap_v(std::vector<int>& height)
    {
        int n = (int)height.size();
        int lmax = height[0], rmax = height[n-1];
        int l = 1, r = n - 2;
        int ans =  0;
        while (l <= r)
        {
            if (lmax <= rmax)
            {
                ans += std::max(0, lmax - height[l]);
                lmax = std::max(lmax, height[l++]);
            }
            else
            {
                ans += std::max(0, rmax - height[r]);
                rmax = std::max(rmax, height[r--]);
            }
        }

        return ans;
    }
};
}

namespace leetcode_70 {
// 76. Minimum Window Substring
class Solution {
public:
    static std::string minWindow(std::string s, std::string t) {
        if (s.size() < t.size()) {
            return {};
        }
        int cnt[256]{};
        for (auto c : t) {
            cnt[c]--;
        }
        int len = std::numeric_limits<int>::max();
        int start = 0;
        for (int l = 0, r = 0, debt = t.size(); r < s.size(); ++r) {
            if (cnt[s[r]]++ < 0) {
                --debt;
            }
            if (debt == 0) {
                while (cnt[s[l]] > 0) {
                    cnt[s[l++]]--;
                }
                if (r - l + 1 < len) {
                    len = r - l + 1;
                    start = l;
                }
            }
        }
        return len == std::numeric_limits<int>::max() ? std::string{} : s.substr(start, len);
    }
};
}

namespace leetcode_76 {
//76. Minimum Window Substring
class Solution {
public:
    static std::string minWindow(std::string s, std::string_view t) {
        if (s.size() < t.size())
            return {};
        int cnt[256]{};
        for (auto c : t)
            cnt[c]--;
        int len = std::numeric_limits<int>::max();
        int start = 0;
        for (int l = 0, r = 0, debt = (int)t.size(); r < s.size(); ++r)
        {
            if (cnt[s[r]]++ < 0)
                --debt;
            if (debt == 0)
            {
                while (cnt[s[l]] > 0)
                    cnt[s[l++]]--;
                if (r - l + 1 < len)
                {
                    len = r - l + 1;
                    start = l;
                }
            }
        }

        return len == std::numeric_limits<int>::max() ? "" : s.substr(start, len);
    }
};
}

namespace leetcode_134 {
//134. Gas Station
class Solution {
public:
    static int canCompleteCircuit(std::vector<int>& gas, std::vector<int>& cost) {
        int n = (int)gas.size();
        for (int l = 0, r = 0, sum; l < n; l = r + 1, r = l)
        {
            sum = 0;
            while (sum + gas[r%n] - cost[r%n] >= 0)
            {
                if (r - l + 1 == n)
                    return l;
                sum += gas[r%n] - cost[r%n];
                ++r;
            }
        }
        return -1;
    }
};
}

namespace leetcode_209 {
//209. Minimum Size Subarray Sum
class Solution {
public:
    static int minSubArrayLen(int target, std::vector<int>& nums) {
        int ans = std::numeric_limits<int>::max();
        for (int r = 0, l = 0, sum = 0; r < nums.size(); ++r)
        {
            sum += nums[r];
            while (sum - nums[l] >= target)
            {
                sum -= nums[l++];
            }
            if (sum >= target)
                ans = std::min(ans, r - l + 1);
        }

        return ans == std::numeric_limits<int>::max() ? 0 : ans;
    }
};
}

namespace leetcode_287 {
//287. Find the Duplicate Number
class Solution {
public:
    static int findDuplicate(std::vector<int>& nums) {
        if (nums.size() < 2)
            return -1;
        int slow = nums[0];
        int fast = nums[nums[0]];
        while (slow != fast)
        {
            slow = nums[slow];
            fast = nums[nums[fast]];
        }
        fast = 0;
        while (slow != fast)
        {
            slow = nums[slow];
            fast = nums[fast];
        }

        return slow;
    }
};
}

namespace leetcode_395 {
//395. Longest Substring with At Least K Repeating Characters
class Solution {
public:
    static int longestSubstring(std::string s, int k) {
        int cnt[256];
        int ans = 0;
        for (int t = 1; t <= 26; ++t)
        {
            std::fill_n(cnt, 256, 0);
            for (int l = 0, r = 0, collect = 0, satisfy = 0; r < s.size(); ++r)
            {
                ++cnt[s[r]];
                if (cnt[s[r]] == 1)
                    ++collect;
                if (cnt[s[r]] == k)
                    ++satisfy;
                while (collect > t)
                {
                    if (cnt[s[l]] == 1)
                        --collect;
                    if (cnt[s[l]] == k)
                        --satisfy;
                    cnt[s[l++]]--;
                }
                if (satisfy == t)
                    ans = std::max(ans, r - l + 1);
            }
        }

        return ans;
    }
};
}

namespace leetcode_410 {
//410. Split Array Largest Sum
class Solution {
public:
    static int splitArray(std::vector<int>& nums, int k) {
        long sum = 0;
        for (auto n : nums)
            sum += n;

        long ans = 0;
        for (long l = 0, r = sum, mid, need; l <= r; )
        {
            mid = l + ((r - l) >> 1);
            need = f(nums, mid);
            if (need <= k)
            {
                ans = mid;
                r = mid - 1;
            }
            else
            {
                l = mid + 1;
            }
        }

        return ans;
    }

    static int f(std::vector<int> &nums, int limit)
    {
        int parts = 1;
        int sum = 0;
        for (auto n : nums)
        {
            if (n > limit)
                return std::numeric_limits<int>::max();
            if (sum + n > limit)
            {
                ++parts;
                sum = n;
            }
            else
            {
                sum += n;
            }
        }
        return parts;
    }
};
}

namespace leetcode_475 {
//475. Heaters
class Solution {
public:
    static int findRadius(std::vector<int>& houses, std::vector<int>& heaters) {
        std::sort(houses.begin(), houses.end());
        std::sort(heaters.begin(), heaters.end());

        int ans = 0;
        for (int i = 0, j = 0; i < houses.size(); ++i)
        {
            while (!best(houses, heaters, i, j))
                ++j;
            ans = std::max(ans, std::abs(heaters[j] - houses[i]));
        }
        return ans;
    }

    static bool best(std::vector<int> &houses, std::vector<int> &heaters, int i, int j)
    {
        return (j == heaters.size() - 1 || std::abs(heaters[j] - houses[i]) < std::abs(heaters[j+1] - houses[i]));
    }
};
}

namespace leetcode_719 {
//719. Find K-th Smallest Pair Distance
class Solution {
public:
    static int smallestDistancePair(std::vector<int>& nums, int k) {
        std::sort(nums.begin(), nums.end());
        int ans = 0;
        int n = (int)nums.size();
        for (int l = 0, r = nums[n-1] - nums[0], mid; l <= r; )
        {
            mid = l + ((r - l) >> 1);
            int cnt = f(nums, mid);
            if (cnt >= k)
            {
                ans = mid;
                r = mid - 1;
            }
            else
            {
                l = mid + 1;
            }
        }

        return ans;
    }

    static int f(std::vector<int> &nums, int limit)
    {
        int ans = 0;
        for (int l = 0, r = 0; l < nums.size(); ++l)
        {
            while (r + 1 < nums.size() && nums[r+1] - nums[l] <= limit)
                ++r;
            ans += r - l;
        }

        return ans;
    }
};
}

namespace leetcode_875 {
//875. Koko Eating Bananas
class Solution {
public:
    static int minEatingSpeed(std::vector<int>& piles, int h) {
        int l = 1;
        int r = 0;
        for (auto &m : piles)
            r = std::max(r, m);

        int ans = 0;
        while (l <= r)
        {
            auto mid = l + ( (r - l) >> 1 );
            if (hours(piles, mid) <= h)
            {
                ans = mid;
                r = mid - 1;
            }
            else
                l = mid + 1;
        }

        return ans;
    }

    static long hours(std::vector<int> &piles, int speed)
    {
        long ret = 0;
        for (auto h : piles)
            ret += (h + speed - 1) / speed;
        return ret;
    }
};
}

namespace leetcode_881 {
//881. Boats to Save People
class Solution {
public:
    static int numRescueBoats(std::vector<int>& people, int limit) {
        std::sort(people.begin(), people.end());
        int ans = 0;
        int sum = 0;
        int l = 0, r = (int)people.size() - 1;
        while (l <= r)
        {
            sum = l == r ? people[l] : people[l] + people[r];
            if (sum > limit)
                --r;
            else
            {
                ++l;
                --r;
            }
            ++ans;
        }

        return ans;
    }
};
}

namespace leetcode_922 {
//922. Sort Array By Parity II
class Solution {
public:
    static std::vector<int> sortArrayByParityII(std::vector<int>& nums) {
        int k = (int)nums.size() - 1;
        for (int i = 0, j = 1; i < nums.size() && j < nums.size(); )
        {
            if (nums[k] % 2 == 1)
            {
                std::swap(nums[k], nums[j]);
                j += 2;
            }
            else
            {
                std::swap(nums[k], nums[i]);
                i += 2;
            }
        }

        return nums;
    }
};
}

namespace leetcode_992 {
//992. Subarrays with K Different Integers
class Solution {
public:
    int subarraysWithKDistinct(std::vector<int>& nums, int k) {
        return nums_of_no_more_than(nums, k) - nums_of_no_more_than(nums, k - 1);
    }

    int nums_of_no_more_than(std::vector<int> &nums, int k)
    {
        std::fill_n(cnt, N, 0);
        int ans = 0;
        for (int l = 0, r = 0, collect = 0; r < nums.size(); ++r)
        {
            if (++cnt[nums[r]] == 1)
                collect++;
            while (collect > k)
            {
                if (--cnt[nums[l++]] == 0)
                    --collect;
            }
            ans += r - l + 1;
        }
        return ans;
    }

private:
    static constexpr int N = 20001;
    int cnt[N]{};
};
}

namespace leetcode_1234 {
//1234. Replace the Substring for Balanced String
class Solution {
public:
    static int balancedString(std::string str) {
        int n = (int)str.size();
        std::vector<int> s(n);
        int cnt[4]{};
        for (int i = 0; i < n; ++i)
        {
            s[i] = chartoi(str[i]);
            cnt[s[i]]++;
        }
        int debt = 0;
        for (int &i : cnt)
        {
            if (i < n / 4)
                i = 0;
            else
            {
                i = n / 4 - i;
                debt -= i;
            }
        }
        if (debt == 0)
            return 0;
        int ans = std::numeric_limits<int>::max();
        for (int l = 0, r = 0; r < n; ++r)
        {
            if (cnt[s[r]]++ < 0)
                debt--;
            if (debt == 0)
            {
                while (cnt[s[l]] > 0)
                    cnt[s[l++]]--;
                ans = std::min(ans, r - l + 1);
            }
        }
        return ans;
    }

    static int chartoi(char c)
    {
        switch (c)
        {
            case 'W':
                return 1;
            case 'E':
                return 2;
            case 'R':
                return 3;
            default:
                return 0;
        }
    }
};
}

namespace leetcode_2141 {
//2141. Maximum Running Time of N Computers
class Solution {
public:
    static long long maxRunTime(int n, std::vector<int>& batteries) {
        long sum = 0;
        for (auto t : batteries)
            sum += t;
        long ans = 0;
        for (long l = 0, r = sum, mid; l <= r;)
        {
            mid = l + ((r - l) >> 1);
            if (f(n, mid, batteries))
            {
                ans = mid;
                l = mid + 1;
            }
            else
            {
                r = mid - 1;
            }
        }
        return ans;
    }

    static bool f(int n, long time, std::vector<int> &batteries)
    {
        long sum = 0;
        for (auto x : batteries)
        {
            if (x > time)
                --n;
            else sum += x;
            if (sum >= n * time)
                return true;
        }
        return false;
    }
};
}




int main(int argc, char *argv[]) {
    return 0;
}






