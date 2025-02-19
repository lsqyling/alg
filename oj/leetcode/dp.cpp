#include "../utilities.hpp"

namespace fib {
int fib_v0(int n)
{
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;
    return fib_v0(n - 1) + fib_v0(n - 2);
}

int fib_v1_(int n, std::vector<int> &dp)
{
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;
    if (dp[n] != -1)
        return dp[n];
    dp[n] = fib_v1_(n - 1, dp) + fib_v1_(n - 2, dp);
    return dp[n];
}
int fib_v1(int n)
{
    std::vector<int> dp(n + 1, -1);
    return fib_v1_(n, dp);
}
int fib_v2(int n)
{
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;
    std::vector<int> dp(n + 1);
    dp[1] = 1;
    for (int i = 2; i <= n; ++i)
    {
        dp[i] = dp[i-1] + dp[i-2];
    }
    return dp[n];
}
int fib_v3(int n)
{
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;
    int p = 0, q = 1;
    for (int i = 2, cur; i <= n; ++i)
    {
        cur = p + q;
        p = q;
        q = cur;
    }
    return q;
}
namespace leetcode_509 {
// 509. Fibonacci Number
class Solution
{
public:
    static int fib(int n)
    {
        if (n == 0)
            return 0;
        if (n == 1)
            return 1;
        int p = 0, q = 1;
        for (int i = 2; i <= n; ++i)
        {
            auto cur = p + q;
            p = q;
            q = cur;
        }
        return q;
    }
};
}
}

namespace leetcode_983 {
// 983. Minimum Cost For Tickets
class Solution {
public:
    static int mincostTickets(std::vector<int>& days, std::vector<int>& costs) {
        // bf
//        return brute_force(days, costs, 0);
        // 动态规划 从底到顶
        int n = static_cast<int>(days.size());
        std::vector<int> dp(n + 1, std::numeric_limits<int>::max());
        dp[n] = 0;
        for (int i = n - 1; i >= 0; --i)
        {
            for (int k = 0, j = i; k < 3; ++k)
            {
                while (j < days.size() && days[i] + d[k] > days[j])
                    ++j;
                dp[i] = std::min(dp[i], costs[k] + dp[j]);
            }
        }

        return dp[0];
    }
    int mincostTickets_v(std::vector<int>& days, std::vector<int>& costs) {
        // 动态规划 从顶到底
        int n = static_cast<int>(days.size());
        std::vector<int> dp(n, std::numeric_limits<int>::max());

        return bf_v(days, costs, 0, dp);
    }
    int bf_v(std::vector<int> &days, std::vector<int> &costs, int i, std::vector<int> &dp)
    {
        if (i == days.size())
            return 0;
        if (dp[i] != std::numeric_limits<int>::max())
            return dp[i];
        int ans = std::numeric_limits<int>::max();
        for (int k = 0, j = i; k < 3; ++k)
        {
            while (j < days.size() && days[i] + d[k] > days[j])
                ++j;
            ans = std::min(ans, costs[k] + bf_v(days, costs, j, dp));
        }

        dp[i] = ans;
        return ans;
    }
    // 暴力破解
    // days[i...] 最少花费多少
    int brute_force(std::vector<int> &days, std::vector<int> &costs, int i)
    {
        if (i == days.size())
            return 0;
        // i: 第days[i]天有一场旅行
        // i... 最少花费多少
        int ans = std::numeric_limits<int>::max();
        for (int k = 0, j = i; k < 3; ++k)
        {
            // k: 方案标号
            while (j < days.size() && days[i] + d[k] > days[j])
            {
                ++j;
            }
            ans = std::min(ans, costs[k] + brute_force(days, costs, j));
        }

        return ans;
    }
private:
    static constexpr int d[3]{1, 7, 30};
};
}

namespace leetcode_91 {
// 91. Decode Ways
class Solution {
public:
    int numDecodings(std::string s) {
        int n = static_cast<int>(s.size());
        std::vector<int> dp(n + 1, -1);

        return bf_v(s, 0, dp);

    }
    static int numDecodings_(std::string s) {
        int n = static_cast<int>(s.size());
        std::vector<int> dp(n + 1);
        dp[n] = 1;
        for (int i = n - 1; i >= 0; --i)
        {
            if (s[i] == '0')
                dp[i] = 0;
            else
            {
                dp[i] = dp[i+1];
                if (i + 1 < s.size() && (s[i] - '0') * 10 + s[i+1] - '0' <= 26)
                {
                    dp[i] += dp[i+2];
                }
            }
        }
        return dp[0];
    }
    // s[i...] 有多少中转化方案
    int bf(std::string_view s, int i)
    {
        if (i == s.size())
            return 1;
        int ans;
        if (s[i] == '0')
            ans = 0;
        else
        {
            ans = bf(s, i + 1);
            if (i + 1 < s.size() && (s[i]-'0') * 10 + (s[i+1] - '0') <= 26)
            {
                ans += bf(s, i + 2);
            }
        }

        return ans;
    }
    // 从顶到底动态规划
    int bf_v(std::string_view s, int i, std::vector<int> &dp)
    {
        if (i == s.size())
            return 1;
        if (dp[i] != -1)
            return dp[i];
        int ans;
        if (s[i] == '0')
            ans = 0;
        else
        {
            ans = bf_v(s, i + 1, dp);
            if (i + 1 < s.size() && ( s[i] - '0' ) * 10 + s[i+1] - '0' <= 26)
                ans += bf_v(s, i + 2, dp);
        }
        dp[i] = ans;
        return ans;
    }

};
}

namespace leetcode_639 {
// 639. Decode Ways II
class Solution {
public:
    static int numDecodings(std::string s)
    {
        int n = static_cast<int>(s.size());
        std::vector<long> dp(n + 1);
        dp[n] = 1;
        for (int i = n - 1; i >= 0; --i)
        {
            if (s[i] != '0')
            {

                // i 单独转
                dp[i] = (s[i] == '*' ? 9 : 1) * dp[i + 1];
                // i, i+1 一起转化 <= 26
                if (i + 1 < n)
                {
                    // 有i+1位置
                    if (s[i] != '*')
                    {
                        if (s[i + 1] != '*')
                        {
                            if ((s[i] - '0') * 10 + s[i + 1] - '0' <= 26)
                                dp[i] += dp[i + 2];
                        }
                        else
                        {
                            // n *
                            // i i+1
                            if (s[i] == '1')
                                dp[i] += 9 * dp[i + 2];
                            if (s[i] == '2')
                                dp[i] += 6 * dp[i + 2];
                        }
                    }
                    else
                    {
                        if (s[i + 1] != '*')
                        {
                            // * n
                            // i i+1
                            if (s[i + 1] <= '6')
                                dp[i] += 2 * dp[i + 2];
                            else
                                dp[i] += dp[i + 2];
                        }
                        else
                        {
                            // * *
                            // i i+1
                            dp[i] += 15 * dp[i + 2];
                        }
                    }
                }
                dp[i] %= MOD;
            }
        }
        return dp[0];
    }
    // s[i....］有多少种有效转化
    int bf(std::string_view s, int i)
    {
        if (i == s.size())
            return 1;
        if (s[i] == '0')
            return 0;
        // i 单独转
        int ans = ( s[i] == '*' ? 9 : 1 ) * bf(s, i + 1);
        // i, i+1 一起转化 <= 26
        if (i + 1 < s.size())
        {
            // 有i+1位置
            if (s[i] != '*')
            {
                if (s[i+1] != '*')
                {
                    if (( s[i] - '0') * 10 + s[i+1] - '0' <= 26)
                        ans += bf(s, i + 2);
                }
                else
                {
                    // n *
                    // i i+1
                    if (s[i] == '1')
                        ans += 9 * bf(s, i + 2);
                    if (s[i] == '2')
                        ans += 6 * bf(s, i + 2);
                }
            }
            else
            {
                if (s[i+1] != '*')
                {
                    // * n
                    // i i+1
                    if (s[i+1] <= '6')
                        ans += 2 * bf(s, i + 2);
                    else
                        ans += bf(s, i + 2);
                }
                else
                {
                    // * *
                    // i i+1
                    ans += 15 * bf(s, i + 2);
                }
            }
        }

        return ans;
    }
private:
    static constexpr int MOD = 1000'000'007;
};
}

namespace leetcode_264 {
// 264. Ugly Number II
class Solution {
public:
    static int nthUglyNumber(int n) {
        std::vector<int> dp(n + 1);
        dp[1] = 1;
        for (int s = 2, i = 1, j = 1, k = 1; s <= n; ++s)
        {
            int a = dp[i] * 2;
            int b = dp[j] * 3;
            int c = dp[k] * 5;
            int cur = std::min(std::min(a, b), c);
            if (cur == a)
                ++i;
            if (cur == b)
                ++j;
            if (cur == c)
                ++k;
            dp[s] = cur;
        }

        return dp[n];
    }
};
}

namespace leetcode_32 {
// 32. Longest Valid Parentheses
class Solution {
public:
    static int longestValidParentheses(std::string s) {
        int n = static_cast<int>(s.size());
        //dp[0...n-1]
        //dp[i]：子串必须以i位置的字符结尾的情况下，往左最多推多远能整体有效
        std::vector<int> dp(n);
        int ans = 0;
        for (int i = 1, p; i < n; ++i)
        {
            if (s[i] == ')')
            {
                p = i - dp[i-1] - 1;
                if (p >= 0 && s[p] == '(')
                {
                    dp[i] = dp[i-1] + 2 + (p - 1 >= 0 ? dp[p-1] : 0);
                }
            }
            ans = std::max(ans, dp[i]);
        }

        return ans;
    }
};
}

namespace leetcode_476 {
// 467. Unique Substrings in Wraparound String
class Solution {
public:
    static int findSubstringInWraproundString(std::string str) {
        int n = static_cast<int>(str.size());
        std::vector<int> s(n);
        for (int i = 0; i < n; ++i)
            s[i] = str[i] - 'a';
        // dp[O]：s中必须以'a'的子串，最大延伸长度是多少，延伸一定要跟据base串的规则
        std::vector<int> dp(26);
        dp[s[0]] = 1;

        for (int i = 1, pre, cur, len = 1; i < n; ++i)
        {
            cur = s[i];
            pre = s[i-1];
            if ((pre == 25 && cur == 0) || pre + 1 == cur)
                ++len;
            else
                len = 1;
            dp[cur] = std::max(dp[cur], len);
        }

        int ans = 0;
        for (int i = 0; i < 26; ++i)
        {
            ans += dp[i];
        }
        return ans;
    }
};
}

namespace leetcode_940 {
// 940. Distinct Subsequences II
class Solution {
public:
    static int distinctSubseqII(std::string s) {
        // dp[i] i= 字符 - ‘a' : 子序列以 a.b.c...z 结尾的个数
        std::vector<int> dp(26);
        // all -- 有一个空集
        int all = 1, newadd;
        for (auto x : s)
        {
            newadd = (all - dp[x-'a']) % MOD;
            dp[x-'a'] = ( dp[x-'a'] + newadd ) % MOD;
            all = (all + newadd) % MOD;
        }

        return (all - 1 + MOD) % MOD;
    }
private:
    static constexpr int MOD = 1000'000'007;
};
}

namespace leetcode_64 {
// 64. Minimum Path Sum
class Solution {
public:
    static int minPathSum(std::vector<std::vector<int>>& grid) {
        int n = static_cast<int>(grid.size());
        int m = static_cast<int>(grid[0].size());
        //先让dp表，变成想象中的表的第0行的数据
        std::vector<int> dp(m);
        dp[0] = grid[0][0];
        for (int j = 1; j < m; ++j)
            dp[j] = dp[j-1] + grid[0][j];
        for (int i = 1; i < n; ++i)
        {
            // i=1，dp表变成想象中的表的第1行的数据
            // i=3，dp表变成想象中的表的第3行的数据
            // i=n-1，dp表变成想象中的表的第n-1行的数据
            dp[0] += grid[i][0];
            for (int j = 1; j < m; ++j)
            {
                dp[j] = std::min(dp[j-1], dp[j]) + grid[i][j];
            }
        }
        return dp[m-1];
    }
    static int minPathSum_v1(std::vector<std::vector<int>>& grid) {
        int n = static_cast<int>(grid.size());
        int m = static_cast<int>(grid[0].size());
        // 从（0，0）到（i，j）最小路径和 dp[i][j]
        std::vector<std::vector<int>> dp(n, std::vector<int>(m));
        dp[0][0] = grid[0][0];
        for (int i = 1; i < n; ++i)
            dp[i][0] = dp[i-1][0] + grid[i][0];
        for (int j = 1; j < m; ++j)
            dp[0][j] = dp[0][j-1] + grid[0][j];
        for (int i = 1; i < n; ++i)
        {
            for (int j = 1; j < m; ++j)
            {
                dp[i][j] = std::min(dp[i-1][j], dp[i][j-1]) + grid[i][j];
            }
        }

        return dp[n-1][m-1];
    }
    // 从（0，0）到（i，j）最小路径和
    // 一定每次只能向右或者向下
    int bf(std::vector<std::vector<int>>& grid, int i, int j)
    {
        if (i == 0 && j == 0)
            return grid[0][0];
        int up = std::numeric_limits<int>::max();
        int left = std::numeric_limits<int>::max();
        if (i - 1 >= 0)
            up = bf(grid, i - 1, j);
        if (j - 1 >= 0)
            left = bf(grid, i, j - 1);

        return grid[i][j] + std::min(up, left);
    }
    int minPathSum_v(std::vector<std::vector<int>>& grid) {
        int n = static_cast<int>(grid.size());
        int m = static_cast<int>(grid[0].size());
        std::vector<std::vector<int>> dp(n, std::vector<int>(m, -1));

        return bf_v(grid, n - 1, m - 1, dp);

    }
    int bf_v(std::vector<std::vector<int>>& grid, int i, int j, std::vector<std::vector<int>>& dp)
    {
        if (dp[i][j] != -1)
            return dp[i][j];
        int ans;
        if (i == 0 && j == 0)
            ans = grid[0][0];
        else
        {
            int up = std::numeric_limits<int>::max();
            int left = std::numeric_limits<int>::max();
            if (i - 1 >= 0)
                up = bf_v(grid, i - 1, j, dp);
            if (j - 1 >= 0)
                left = bf_v(grid, i, j - 1, dp);

            ans =  grid[i][j] + std::min(up, left);
        }
        dp[i][j] = ans;
        return ans;
    }
};
}

namespace leetcode_79 {
// 79. Word Search
class Solution {
public:
    bool exist(std::vector<std::vector<char>>& board, const std::string &word) {
        for (int i = 0; i < board.size(); ++i)
        {
            for (int j = 0; j < board[0].size(); ++j)
            {
                if (bf(board, word, i, j, 0))
                    return true;
            }
        }
        return false;
    }
    bool bf(std::vector<std::vector<char>>& board, std::string_view word, int i, int j, int k) {
        if (k == word.size())
            return true;
        if (i < 0 || i == board.size() || j < 0 || j == board[0].size() || board[i][j] != word[k])
            return false;
        auto tmp = board[i][j];
        board[i][j] = 0;
        bool ans = bf(board, word, i - 1, j, k + 1)
                || bf(board, word, i, j - 1, k + 1)
                || bf(board, word, i + 1, j, k + 1)
                || bf(board, word, i, j + 1, k + 1);

        board[i][j] = tmp;
        return ans;
    }
};
}

namespace leetcode_1143 {
// 1143. Longest Common Subsequence
class Solution {
public:
    static int longestCommonSubsequence_(std::string text1, std::string text2) {
        if (text1.size() < text2.size())
            std::swap(text1, text2);
        int n = static_cast<int>(text1.size());
        int m = static_cast<int>(text2.size());
        std::vector<int> dp(m + 1);
        for (int i = 1; i <= n; ++i)
        {
            int leftup = 0, backup;
            for (int j = 1; j <= m; ++j)
            {
                backup = dp[j];
                if (text1[i-1] == text2[j-1])
                    dp[j] = leftup + 1;
                else
                    dp[j] = std::max(dp[j], dp[j-1]);
                leftup = backup;
            }
        }
        return dp[m];
    }
    static int longestCommonSubsequence(std::string text1, std::string text2) {
        int n = static_cast<int>(text1.size());
        int m = static_cast<int>(text2.size());
        // dp[len1][len2] : 前缀为len1,len2 最长公共子序列的长度
        std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1));
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= m; ++j)
            {
                if (text1[i-1] == text2[j-1])
                    dp[i][j] = dp[i-1][j-1] + 1;
                else
                {
                    dp[i][j] = std::max(dp[i-1][j], dp[i][j-1]);
                }
            }
        }
        return dp[n][m];
    }
    // s1[前缀长度为len1]对应s2[前缀长度为len2]
    // 最长公共子序列长度
    int bf(std::string_view s1, std::string_view s2, int len1, int len2)
    {
        if (len1 == 0 || len2 == 0)
            return 0;
        int ans;
        if (s1[len1-1] == s2[len2-1])
            ans = bf(s1, s2, len1- 1, len2 - 1) + 1;
        else
            ans = std::max(bf(s1, s2, len1 - 1, len2), bf(s1, s2, len1, len2 - 1));

        return ans;
    }
};
}

namespace leetcode_516 {
// 最长回文子序列
// 516. Longest Palindromic Subsequence
class Solution {
public:
    static int longestPalindromeSubseq(std::string s) {
        int n = static_cast<int>(s.size());
        std::vector<std::vector<int>> dp(n, std::vector<int>(n));
        for (int i = n - 1; i >= 0; --i)
        {
            dp[i][i] = 1;
            if (i + 1 < n)
                dp[i][i+1] = s[i] == s[i+1] ? 2 : 1;
            for (int j = i + 2; j < n; ++j)
            {
                if (s[i] == s[j])
                    dp[i][j] = 2 + dp[i+1][j-1];
                else
                    dp[i][j] = std::max(dp[i+1][j], dp[i][j-1]);
            }
        }

        return dp[0][n-1];
    }
    // s[l...r]最长回文子序列长度
    // l<=r
    int bf(std::string_view s, int l , int r)
    {
        if (l == r)
            return 1;
        if (l + 1 == r)
            return s[l] == s[r] ? 2 : 1;
        if (s[l] == s[r])
            return 2 + bf(s, l + 1, r - 1);
        else
            return std::max(bf(s, l + 1, r), bf(s, l, r - 1));
    }
};
}

namespace leetcode_329 {
// 矩阵中的最长递增路径
// 329. Longest Increasing Path in a Matrix
class Solution {
public:
    int longestIncreasingPath(std::vector<std::vector<int>>& matrix) {
        int n = static_cast<int>(matrix.size());
        int m = static_cast<int>(matrix[0].size());

        int ans = 0;
        std::vector<std::vector<int>> dp(n, std::vector<int>(m));
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; ++j)
            {
                ans = std::max(ans, bf(matrix, dp, i, j));
            }
        }

        return ans;
    }
    int bf(std::vector<std::vector<int>>& matrix, std::vector<std::vector<int>>& dp, int i, int j)
    {
        if (dp[i][j] != 0)
            return dp[i][j];
        int next = 0;
        if (i > 0 && matrix[i-1][j] > matrix[i][j])
            next = std::max(next, bf(matrix, dp, i - 1, j));
        if (i + 1 < matrix.size() && matrix[i+1][j] > matrix[i][j])
            next = std::max(next, bf(matrix, dp, i + 1, j));
        if (j + 1 < matrix[0].size() && matrix[i][j+1] > matrix[i][j])
            next = std::max(next, bf(matrix, dp, i, j + 1));
        if (j > 0 && matrix[i][j-1] > matrix[i][j])
            next = std::max(next, bf(matrix, dp, i, j - 1));

        dp[i][j] = next + 1;
        return dp[i][j];
    }
};
}

namespace leetcode_115 {
// 115. Distinct Subsequences
class Solution {
public:
    int numDistinct(std::string s, std::string t) {

    }
};
}






























int main()
{
    return 0;
}