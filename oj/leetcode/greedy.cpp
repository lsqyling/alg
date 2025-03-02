#include "../utilities.hpp"

namespace leetcode_179 {
// 179. 最大数
class Solution {
public:
    static std::string largestNumber(std::vector<int>& nums) {
        std::vector<std::string> ns;
        for (auto c : nums)
            ns.emplace_back(std::to_string(c));

        auto cmp = [](auto &s1, auto &s2) {
            return s2 + s1 < s1 + s2;
        };
        std::sort(ns.begin(), ns.end(), cmp);
        if (ns[0] == "0")
            return "0";
        std::string ans;
        for (auto &s : ns)
            ans += s;

        return ans;
    }
};
}

namespace leetcode_1029 {
// 1029. 两地调度
class Solution {
public:
    static int twoCitySchedCost(std::vector<std::vector<int>>& costs) {
        int n = static_cast<int>(costs.size());
        std::vector<int> arr(n);
        int sum = 0;
        for (int i = 0; i < n; ++i)
        {
            arr[i] = costs[i][1] - costs[i][0];
            sum += costs[i][0];
        }

        std::sort(arr.begin(), arr.end());
        int m = n / 2;
        for (int i = 0; i < m; ++i)
        {
            sum += arr[i];
        }
        return sum;
    }
};
}

namespace leetcode_1553 {
// 1553. 吃掉 N 个橘子的最少天数
class Solution {
public:
    int minDays(int n) {
        if (n <= 1)
            return n;
        if (dp.find(n) != dp.end())
            return dp[n];

        int ans = std::min(n%2 + 1 + minDays(n/2), n%3 + 1 + minDays(n/3));
        dp[n] = ans;
        return ans;
    }
private:
    std::unordered_map<int, int> dp;
};
}

namespace leetcode_630 {
// 630. 课程表 III
class Solution {
public:
    static int scheduleCourse(std::vector<std::vector<int>>& courses) {
        auto cmp = [](auto &c1, auto &c2) {
            return c1[1] < c2[1];
        };
        std::sort(courses.begin(), courses.end(), cmp);
        std::priority_queue<int> heap;
        int time = 0;
        for (auto &c : courses)
        {
            if (time + c[0] <= c[1])
            {
                heap.push(c[0]);
                time += c[0];
            }
            else
            {
                if (!heap.empty() && heap.top() > c[0])
                {
                    time += c[0] - heap.top();
                    heap.pop();
                    heap.push(c[0]);
                }
            }
        }

        return (int)heap.size();
    }
};
}

namespace leetcode_1167 {
// 1167. 连接木棍的最低费用 - 力扣（LeetCode）
class Solution
{
public:
    static int connectSticks(std::vector<int> &arr)
    {
        std::priority_queue<int, std::vector<int>, std::greater<>> heap;
        for (auto &n : arr)
            heap.push(n);
        int sum = 0;
        int cur = 0;
        while (heap.size() > 1)
        {
            auto t0 = heap.top(); heap.pop();
            auto t1 = heap.top(); heap.pop();
            cur = t0 + t1;
            sum += cur;
            heap.push(cur);
        }

        return sum;
    }
};
}

namespace leetcode_LCR_132 {
// LCR 132. 砍竹子 II
class Solution {
public:
    static int cuttingBamboo(int n) {
        if (n == 2)
            return 1;
        if (n == 3)
            return 2;
        int tail = n % 3 == 0 ? 1 : (n % 3 == 1 ? 4 : 2);
        int p = ( tail == 1 ? n : n - tail ) / 3;

        return power(3, p) * tail % MOD;
    }
    static long power(long x, int n)
    {
        long ans = 1;
        while (n)
        {
            if ((n & 1) == 1)
                ans = ans * x % MOD;
            x = x * x % MOD;
            n >>= 1;
        }
        return ans;
    }
private:
    static constexpr int MOD = 1000'000'007;
};
}

namespace leetcode_1353 {
// 1353. 最多可以参加的会议数目
class Solution {
public:
    static int maxEvents(std::vector<std::vector<int>>& events) {
        int n = static_cast<int>(events.size());
        auto cmp = [](auto &a, auto &b) {
            return a[0] < b[0];
        };
        std::sort(events.begin(), events.end(), cmp);
        int min = events[0][0];
        int max = events[0][1];
        for (int i = 1; i < n; ++i)
            max = std::max(max, events[i][1]);

        // 小根堆 : 会议的结束时间
        std::priority_queue<int, std::vector<int>, std::greater<>> heap;
        int i = 0, ans = 0;
        for (int day = min; day <= max; ++day)
        {
            while (i < n && events[i][0] == day)
                heap.push(events[i++][1]);
            while (!heap.empty() && heap.top() < day)
                heap.pop();
            if (!heap.empty())
            {
                heap.pop();
                ++ans;
            }
        }

        return ans;
    }
};
}

namespace leetcode_502 {
// 502. IPO
class Solution {
public:
    static int findMaximizedCapital(int k, int w, std::vector<int>& profits, std::vector<int>& capital) {
        int n = static_cast<int>(profits.size());
        //花费小根堆
        //代表被锁住的项目
        auto cmp = [](auto a, auto b) { return a.c > b.c ;};
        std::priority_queue<project, std::vector<project>, decltype(cmp)> minheap(cmp);
        //利润大根堆
        //代表被解锁的项目
        auto cmp1 = [](auto a, auto b) { return a.p < b.p; };
        std::priority_queue<project, std::vector<project>, decltype(cmp1)> maxheap(cmp1);
        for (int i = 0; i < n; ++i)
        {
            minheap.push({profits[i], capital[i]});
        }
        while (k)
        {
            while (!minheap.empty() && minheap.top().c <= w)
            {
                maxheap.push(minheap.top());
                minheap.pop();
            }
            if (maxheap.empty())
                break;
            w += maxheap.top().p;
            maxheap.pop();
            --k;
        }

        return w;
    }
private:
    struct project
    {
        int p;
        int c;
    };
};
}

namespace AbsoluteValueAddToArray {
//给定一个非负数组arr，计算任何两个数差值的绝对值
//如果arr中没有，都要加入到arr里，但是只加一份然后新的arr，继续计算任何两个数差值的绝对值如果
//arr中没有，都要加入到arr里，但是只加一份一直到arr大小固定，返回arr最终的长度来自真实大厂笔试，没有在线测试，对数器验证，
int gcd(int a, int b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}
int lenof(std::vector<int> &arr)
{
    int max = 0;
    //找到任意一个非0的值
    int gcd = 0;
    for (auto num : arr)
    {
        max = std::max(max, num);
        if (num)
            gcd = num;
    }
    if (gcd == 0)
        return (int)arr.size();
    std::unordered_map<int, int> cnts;
    for (auto num : arr)
    {
        if (num)
            gcd = AbsoluteValueAddToArray::gcd(gcd, num);
        cnts[num]++;
    }
    int ans = max / gcd;
    int maxcnt = 0;
    for (auto [ key, val ] : cnts)
    {
        if (key)
            ans += cnts[key] - 1;
        maxcnt = std::max(maxcnt, cnts[key]);
    }
    ans += cnts[0] > 0 ? cnts[0] : (maxcnt > 1 ? 1 : 0);
    return ans;
}
}

namespace leetcode_581 {
// 581. 最短无序连续子数组
class Solution {
public:
    static int findUnsortedSubarray(std::vector<int>& nums) {
        int n = static_cast<int>(nums.size());
        //max>当前数，认为不达标
        //从左往右遍历，记录最右不达标的位置
        int right = -1;
        int max = std::numeric_limits<int>::min();
        for (int i = 0; i < n; ++i)
        {
            if (max > nums[i])
                right = i;
            max = std::max(max, nums[i]);
        }
        //min<当前数，认为不达标
        //从右往左遍历，记录最左不达标的位置
        int min = std::numeric_limits<int>::max();
        int left = n;
        for (int i = n - 1; i >= 0; --i)
        {
            if (min < nums[i])
                left = i;
            min = std::min(min, nums[i]);
        }
        return std::max(0, right - left + 1);
    }
};
}

namespace leetcode_623 {
// 632. 最小区间
class Solution {
public:
    static std::vector<int> smallestRange(std::vector<std::vector<int>>& nums) {
        int k = static_cast<int>(nums.size());
        auto cmp = [](auto a, auto b) {
            if (a.v != b.v)
                return a.v < b.v;
            else
                return a.i < b.i;
        };
        std::set<node, decltype(cmp)> ol(cmp);
        for (int i = 0; i < k; ++i)
        {
            ol.insert({nums[i][0], i, 0});
        }
        int r = std::numeric_limits<int>::max();
        int a = 0;
        int b = 0;
        node max{}, min{};
        while (ol.size() == k)
        {
            max = *ol.rbegin();
            min = *ol.begin();
            ol.erase(ol.begin());
            if (max.v - min.v < r)
            {
                r = max.v - min.v;
                a = min.v;
                b = max.v;
            }
            if (min.j + 1 < nums[min.i].size())
                ol.insert({nums[min.i][min.j+1], min.i, min.j + 1});
        }

        return {a, b};
    }
private:
    struct node
    {
        int v; //值
        int i; //当前值来自哪个数组
        int j; //当前值来自i号数组的什么位置
    };
};
}

namespace GroupBuyTickets {
struct game
{
    int ki{0};
    int bi{0};
    int people{0};

    //如果再来一人，这个项目得到多少钱
    [[nodiscard]]
    int earn() const
    {
        //bi－（people+1）*ki：当前的人，门票原价减少了，当前的门票价格
        //people*ki：当前人的到来，之前的所有人，门票价格都再减去ki
        return bi - (people + 1) * ki - people * ki;
    }
};
int enough(std::vector<std::vector<int>> &games, int n)
{
    auto cmp = [](const auto &a, const auto &b) {
        return a.earn() > b.earn();
    };
    // 大根堆
    std::priority_queue<game, std::vector<game>, decltype(cmp)> heap(cmp);
    for (auto &g : games)
        heap.push({g[0], g[1], 0});
    int ans = 0;
    for (int i = 0; i < n; ++i)
    {
        if (heap.top().earn() <= 0)
            break;
        auto cur = heap.top(); heap.pop();
        ans += cur.earn();
        cur.people++;
        heap.push(cur);
    }

    return ans;
}
}

namespace leetcode_1675 {
// 1675. 数组的最小偏移量
class Solution {
public:
    static int minimumDeviation(std::vector<int>& nums) {
        std::set<int> ol;
        for (auto num : nums)
        {
            if (num % 2 == 0)
                ol.insert(num);
            else
                ol.insert(num * 2);
        }
        int ans = *ol.rbegin() - *ol.begin();
        while (ans && *ol.rbegin() % 2 == 0)
        {
            int max = *ol.rbegin();
            ol.erase(max);
            ol.insert(max / 2);
            ans = std::min(ans, *ol.rbegin() - *ol.begin());
        }

        return ans;
    }
};
}

namespace leetcode_781 {
// 781. 森林中的兔子
class Solution {
public:
    static int numRabbits(std::vector<int>& answers) {
        std::sort(answers.begin(), answers.end());
        int n = static_cast<int>(answers.size());
        int ans = 0;
        for (int i = 0, j = 1, x; i < n; ++j)
        {
            x = answers[i];
            while (j < n && x == answers[j])
                ++j;
            ans += (j - i + x) / (x + 1) * (x + 1);
            i = j;
        }
        return ans;
    }
};
}

namespace leetcode_2449 {
// 2449. 使数组相似的最少操作次数
class Solution {
public:
    static long long makeSimilar(std::vector<int>& nums, std::vector<int>& target) {
        auto cmp = [](int a, int b) {
            if (a % 2 != b % 2)
                return a % 2 > b % 2;
            else
                return a < b;
        };
        std::sort(nums.begin(), nums.end(), cmp);
        std::sort(target.begin(), target.end(), cmp);
        long ans = 0;
        int n = static_cast<int>(nums.size());
        for (int i = 0; i < n; ++i)
        {
            ans += std::abs(nums[i] - target[i]);
        }
        return ans / 4;
    }
};
}


































int main()
{
    std::priority_queue<int, std::vector<int>, std::greater<>> heap;
    for (int i = 0; i < 10; ++i)
        heap.push(i);
    std::cout << heap.top();
    return 0;
}