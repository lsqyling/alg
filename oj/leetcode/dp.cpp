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
    static int numDistinct(std::string s, std::string t) {
        int n = static_cast<int>(s.size());
        int m = static_cast<int>(t.size());
        // dp[i][j]：s[前缀长度为订的所有子序列中，有多少个子序列等于t[前缀长度为订
        std::vector<std::vector<unsigned long>> dp(n + 1, std::vector<unsigned long>(m + 1));
        for (int i = 0; i <= n; ++i)
            dp[i][0] = 1;

        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= m; ++j)
            {
                dp[i][j] = dp[i-1][j];
                if (s[i-1] == t[j-1])
                    dp[i][j] += dp[i-1][j-1];
            }
        }

        return (int)dp[n][m];
    }
    static int numDistinct_(std::string s, std::string t) {
        int n = static_cast<int>(s.size());
        int m = static_cast<int>(t.size());
        // dp[i][j]：s[前缀长度为订的所有子序列中，有多少个子序列等于t[前缀长度为订
        std::vector<unsigned long long> dp(m + 1);
        dp[0] = 1;

        for (int i = 1; i <= n; ++i)
        {
            for (int j = m; j >= 1; --j)
            {
                if (s[i-1] == t[j-1])
                    dp[j] += dp[j-1];
            }
        }
        return (int)dp[m];
    }
};
}

namespace leetcode_72 {
// 72. Edit Distance
class Solution {
public:
    int minDistance(std::string word1, std::string word2) {
        return md_common(word1, word2, 1, 1, 1);
    }
    int md_common(std::string_view word1, std::string_view word2, int a, int b, int c) {
        int n = static_cast<int>(word1.size());
        int m = static_cast<int>(word2.size());
        // dp[i][j]:
        // s1[前缀长度为i]想变成s2[前缀长度为j]，至少付出多少代价
        std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1));
        for (int i = 1; i <= n; ++i)
            dp[i][0] = i * b;
        for (int j = 1; j <= m; ++j)
            dp[0][j] = j * a;

        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= m; ++j)
            {
                if (word1[i-1] == word2[j-1])
                    dp[i][j] = dp[i-1][j-1];
                else
                {
                    dp[i][j] = std::min(std::min(dp[i-1][j] + b, dp[i][j-1] + a), dp[i-1][j-1] + c);
                }
            }
        }

        return dp[n][m];
    }
};
}

namespace leetcode_97 {
// 交错字符串
// 97. Interleaving String
class Solution {
public:
    static bool isInterleave(std::string s1, std::string s2, std::string s3) {
        int n = static_cast<int>(s1.size());
        int m = static_cast<int>(s2.size());
        if (n + m != s3.size())
            return false;
        // dp[i][j]：
        // s1[前缀长度为i]和s2[前缀长度为j]，能否交错组成出s3[前缀长度为i+j]
        std::vector<std::vector<bool>> dp(n + 1, std::vector<bool>(m + 1));
        dp[0][0] = true;
        for (int i = 1; i <= n; ++i)
        {
            if (s1[i-1] != s3[i-1])
                break;
            dp[i][0] = true;
        }
        for (int j = 1; j <= m; ++j)
        {
            if (s2[j-1] != s3[j-1])
                break;
            dp[0][j] = true;
        }
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= m; ++j)
            {
                dp[i][j] = (s1[i-1] == s3[i+j-1] && dp[i-1][j]) || (s2[j-1] == s3[i+j-1] && dp[i][j-1]);
            }
        }

        return dp[n][m];
    }
};
}

namespace leetcode_474 {
// 一和零（多维费用背包)
// 474. Ones and Zeroes
class Solution {
public:
    static int findMaxForm(std::vector<std::string>& strs, int m, int n) {
        std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1));
        for (auto &str : strs)
        {
            auto ret = count_zeros_ones(str);
            for (int z = m; z >= ret.first; --z)
            {
                for (int o = n; o >= ret.second; --o)
                {
                    dp[z][o] = std::max(dp[z][o],  1 + dp[z-ret.first][o-ret.second]);
                }
            }
        }

        return dp[m][n];
    }
    // strs.[i。...]自由选择，希望零的数量不超过z、一的数量不超过o
    // 最多能选多少个字符串
    int bf(std::vector<std::string>& strs, int i, int z, int o)
    {
        if (i == strs.size())
            return 0;
        //不使用当前的strs[i]字符串
        int p1 = bf(strs, i + 1, z, o);
        //使用当前的strs[i]字符串
        int p2 = 0;
        auto ret = count_zeros_ones(strs[i]);
        if (ret.first <= z && ret.second <= o)
            p2 = bf(strs, i + 1, z - ret.first, o - ret.second);

        return std::max(p1, p2);
    }
    static std::pair<int, int> count_zeros_ones(std::string_view s)
    {
        int z = 0;
        int o = 0;
        for (auto c : s)
        {
            if (c == '1')
                ++o;
            if (c == '0')
                ++z;
        }
        return {z, o};
    }
};
}

namespace leetcode_879 {
// 盈利计划（多维费用背包）
// 879. Profitable Schemes
class Solution {
public:
    static int profitableSchemes(int n, int minProfit, std::vector<int>& group, std::vector<int>& profit) {
        //i=没有工作的时候，i==g.length
        std::vector<std::vector<int>> dp(n + 1, std::vector<int>(minProfit + 1));
        for (int r = 0; r <= n; ++r)
        {
            dp[r][0] = 1;
        }
        int m = static_cast<int>(group.size());
        for (int i = m - 1; i >= 0; --i)
        {
            for (int r = n; r >= 0; --r)
            {
                for (int s = minProfit; s >= 0; --s)
                {
                    int p1 = dp[r][s];
                    int p2 = group[i] <= r ? dp[r-group[i]][std::max(0, s-profit[i])] : 0;
                    dp[r][s] = (p1 + p2) % MOD;
                }
            }
        }

        return dp[n][minProfit];
    }
    // i：来到i号工作
    // r：员工额度还有r人，如果r<=0说明已经没法再选择工作了
    // s：利润还有s才能达标，如果s<=0说明之前的选择已经让利润达标了
    // 返回：i....r、s，有多少种方案
    int bf(std::vector<int>& group, std::vector<int>& profit, int i, int r, int s)
    {
        if (r <= 0)
        {
            //人已经耗尽了，之前可能选了一些工作
            return s <= 0 ? 1 : 0;
        }
        // r > 0
        if (i == group.size())
        {
            // 工作耗尽了
            return s <= 0 ? 1 : 0;
        }
        //之前做了一些选择，不要当前工作
        int p1 = bf(group, profit, i + 1, r, s);
        //要当前工作
        int p2 = 0;
        if (group[i] <= r)
        {
            p2 = bf(group, profit, i + 1, r - group[i], s - profit[i]);
        }

        return p1 + p2;
    }

private:
    static constexpr int MOD = 1000'000'007;

};
}

namespace leetcode_688 {
// 骑士在棋盘上的概率
// 688. Knight Probability in Chessboard
class Solution {
public:
    double knightProbability(int n, int k, int row, int column) {
        std::vector<std::vector<std::vector<double>>>
                dp(n, std::vector<std::vector<double>>(n, std::vector<double>(k + 1, -1)));

        return bf(n, row, column, k, dp);

    }
    //从（i，j）出发还有k步要走，返回最后在棋盘上的概率
    double bf(int n, int i, int j, int k, std::vector<std::vector<std::vector<double>>> &dp)
    {
        if (i < 0 || i >= n || j < 0 || j >= n)
            return 0;
        if (dp[i][j][k] != -1)
            return dp[i][j][k];
        double ans = 0;
        if (k == 0)
            ans = 1;
        else
        {
            ans += bf(n, i - 2, j + 1, k - 1, dp) / 8;
            ans += bf(n, i - 1, j + 2, k - 1, dp) / 8;
            ans += bf(n, i + 1, j + 2, k - 1, dp) / 8;
            ans += bf(n, i + 2, j + 1, k - 1, dp) / 8;
            ans += bf(n, i + 2, j - 1, k - 1, dp) / 8;
            ans += bf(n, i + 1, j - 2, k - 1, dp) / 8;
            ans += bf(n, i - 1, j - 2, k - 1, dp) / 8;
            ans += bf(n, i - 2, j - 1, k - 1, dp) / 8;
        }

        dp[i][j][k] = ans;
        return ans;
    }

};
}

namespace leetcode_2435 {
// 矩阵中和能被K整除的路径
// 2435. Paths in Matrix Whose Sum Is Divisible by K
class Solution {
public:
    static int numberOfPaths(std::vector<std::vector<int>>& grid, int k) {
        // 套路：把路径和模k的结果当成一个扩展维度。
        // dp[i][j][v]表示从左上走到(i,j)，且路径和模k的结果为v时的路径数。
        // 初始值dp[0][0][grid[0][0] mod k]=1，答案为dp[m−1][n−1][0]。
        // dp[i][j][(v+grid[i][j]) mod k]=dp[i][j−1][v]+dp[i−1][j][v]
        // 代码实现时，为了避免判断是否越界，可以把下标都加一。此时可以设初始值dp[0][1][0]=1（或者dp[1][0][0]=1）简化一点点代码。
        int m = static_cast<int>(grid.size());
        int n = static_cast<int>(grid[0].size());
        std::vector<std::vector<std::vector<int>>> dp(m + 1, std::vector<std::vector<int>>(n + 1, std::vector<int>(k)));
        dp[0][1][0] = 1;
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                for (int v = 0; v < k; ++v)
                {
                    dp[i + 1][j + 1][(v + grid[i][j]) % k] = (dp[i + 1][j][v] + dp[i][j + 1][v]) % MOD;
                }

            }
        }

        return dp[m][n][0];
    }

private:
    static constexpr int MOD = 1000'000'007;
};
}

namespace leetcode_87 {
// 扰乱字符串
// 87. Scramble String
class Solution {
public:
    static bool isScramble(std::string s1, std::string s2) {
        int n = static_cast<int>(s1.size());
        std::vector<std::vector<std::vector<bool>>>
                dp(n, std::vector<std::vector<bool>>(n, std::vector<bool>(n + 1, false)));
        // 填写len=1层，所有的格子
        for (int l1 = 0; l1 < n; l1++) {
            for (int l2 = 0; l2 < n; l2++) {
                dp[l1][l2][1] = s1[l1] == s2[l2];
            }
        }
        for (int len = 2; len <= n; len++) {
            // 注意如下的边界条件 : l1 <= n - len l2 <= n - len
            for (int l1 = 0; l1 <= n - len; l1++) {
                for (int l2 = 0; l2 <= n - len; l2++) {
                    for (int k = 1; k < len; k++) {
                        if (dp[l1][l2][k] && dp[l1 + k][l2 + k][len - k]) {
                            dp[l1][l2][len] = true;
                            break;
                        }
                    }
                    if (!dp[l1][l2][len]) {
                        for (int i = l1 + 1, j = l2 + len - 1, k = 1; k < len; i++, j--, k++) {
                            if (dp[l1][j][k] && dp[i][l2][len - k]) {
                                dp[l1][l2][len] = true;
                                break;
                            }
                        }
                    }
                }
            }
        }
        return dp[0][0][n];
    }
};
}

namespace leetcode_53 {
// 子数组最大累加和
// 53. Maximum Subarray
class Solution {
public:
    static int maxSubArray(std::vector<int>& nums) {
        int n = static_cast<int>(nums.size());
        std::vector<int> dp(n);

        dp[0] = nums[0];
        int ans = dp[0];
        for (int i = 1; i < n; ++i)
        {
            dp[i] = std::max(nums[i], dp[i-1] + nums[i]);
            ans = std::max(ans, dp[i]);
        }
        return ans;
    }
    // 找到拥有最大累加和的子数组
    // 更新好全局变量left、right、sum
    // 上游调用函数可以直接使用这三个变量
    // 相当于返回了三个值
    struct result
    {
        int left, right, sum;
    };
    static result extra(std::vector<int>& nums) {
        int sum = std::numeric_limits<int>::min();
        int left, right;
        for (int l = 0, r = 0, pre = std::numeric_limits<int>::min(); r < nums.size(); ++r)
        {
            if (pre > 0)
                pre += nums[r];
            else
            {
                pre = nums[r];
                l = r;
            }
            if (pre > sum)
            {
                sum = pre;
                left = l;
                right = r;
            }
        }
        return {left, right, sum};
    }

};
}

namespace leetcode_198 {
// 不能选相邻元素的最大累加和问题
// 198. House Robber
class Solution {
public:
    static int rob(std::vector<int>& nums) {
        int n = static_cast<int>(nums.size());
        if (n == 1)
            return nums[0];
        if (n == 2)
            return std::max(nums[0], nums[1]);
        //dp[i]：nums[0...i]范围上可以随意选择数字，但是不能选相邻数，能得到的最大累加和
        std::vector<int> dp(n);
        dp[0] = nums[0];
        dp[1] = std::max(nums[0], nums[1]);
        for (int i = 2; i < n; ++i)
        {
            dp[i] = std::max(dp[i-1], dp[i-2] + nums[i]);
        }

        return dp[n-1];
    }
};
}

namespace leetcode_918 {
// 环形数组的子数组最大累加和
// 918. Maximum Sum Circular Subarray
class Solution {
public:
    static int maxSubarraySumCircular(std::vector<int>& nums) {
        int n = static_cast<int>(nums.size());
        std::vector<int> dp(n);
        int all = nums[0];
        int maxsum = nums[0], minsum = nums[0];
        for (int i = 1, maxpre = nums[0], minpre = nums[0]; i < n; ++i)
        {
            all += nums[i];
            maxpre = std::max(nums[i], maxpre + nums[i]);
            maxsum = std::max(maxsum, maxpre);

            minpre = std::min(nums[i], minpre + nums[i]);
            minsum = std::min(minsum, minpre);
        }

        return all == minsum ? maxsum : std::max(maxsum, all - minsum);
    }
};
}

namespace leetcode_213 {
// 环形数组中不能选相邻元素的最大累加和
// 213. House Robber II
class Solution {
public:
    static int rob(std::vector<int>& nums) {
        int n = static_cast<int>(nums.size());
        if (n == 1)
            return nums[0];

        return std::max(best(nums, 1, n - 1), nums[0] + best(nums, 2, n - 2));
    }
    // nums.[l....r]范围上，没有环形的概念
    // 返回：可以随意选择数字，但不能选择相邻数字的情况下，最大累加和
    static int best(std::vector<int> &nums, int l, int r)
    {
        if (l > r)
            return 0;
        if (l == r)
            return nums[l];
        if (l + 1 == r)
            return std::max(nums[l], nums[r]);
        int prep = nums[l];
        int pre = std::max(nums[l], nums[l+1]);
        for (int i = l + 2; i <= r; ++i)
        {
            int cur = std::max(pre, nums[i] + std::max(0, prep));
            prep = pre;
            pre = cur;
        }

        return pre;
    }
};
}

namespace leetcode_2560 {
// 打家劫舍IV
// 2560. House Robber IV
class Solution {
public:
    static int minCapability(std::vector<int>& nums, int k) {
        int n = static_cast<int>(nums.size());
        int l = nums[0], r = nums[0];
        for (int i = 1; i < n; ++i)
        {
            r = std::max(r, nums[i]);
            l = std::min(l, nums[i]);
        }
        int m, ans = 0;
        while (l <= r)
        {
            m = (l + r) / 2;
            if (most_rob(nums, n, m) >= k)
            {
                ans = m;
                r = m - 1;
            }
            else
            {
                l = m + 1;
            }
        }

        return ans;
    }
    // 盗贼能力为ability时 返回盗贼最多能窃取多少间房屋
    // 注意限制：不能窃取相邻房屋
    static int most_rob(std::vector<int> &nums, int n, int ability)
    {
        if (n == 1)
            return nums[0] <= ability ? 1 : 0;
        if (n == 2)
            return (nums[0] <= ability || nums[1] <= ability) ? 1 : 0;
        std::vector<int> dp(n);
        dp[0] = nums[0] <= ability ? 1 : 0;
        dp[1] = (nums[0] <= ability || nums[1] <= ability) ? 1 : 0;
        for (int i = 2; i < n; ++i)
        {
            dp[i] = std::max(dp[i-1], (nums[i] <= ability ? 1 : 0) + dp[i-2]);
        }

        return dp[n-1];
    }
    // 继续贪心优化
    static int most_rob1(std::vector<int> &nums, int n, int ability)
    {
        int ans = 0;
        for (int i = 0; i < n; ++i)
        {
            if (nums[i] <= ability)
            {
                ++ans;
                ++i;
            }
        }
        return ans;
    }
};
}

namespace leetcode_1724 {
// 子矩阵最大累加和问题
// 面试题 17.24. Max Submatrix LCCI
class Solution {
public:
    static std::vector<int> getMaxMatrix(std::vector<std::vector<int>>& matrix) {
        int n = static_cast<int>(matrix.size());
        int m = static_cast<int>(matrix[0].size());
        int max = std::numeric_limits<int>::min();
        int a = 0, b = 0;
        int c = 0, d = 0;
        std::vector<int> nums( m );
        for (int i = 0; i < n; ++i)
        {
            std::fill(nums.begin(), nums.end(), 0);
            for (int j = i; j < n; ++j)
            {
                //子数组中找到拥有最大累加和的子数组
                for (int l = 0, r = 0, pre = std::numeric_limits<int>::min(); r < m; ++r)
                {
                    nums[r] += matrix[j][r];
                    if (pre >= 0)
                        pre += nums[r];
                    else
                    {
                        pre = nums[r];
                        l = r;
                    }
                    if (pre > max)
                    {
                        max = pre;
                        a = i;
                        b = l;
                        c = j;
                        d = r;
                    }
                }

            }
        }

        return {a, b, c, d};
    }
};
}

namespace leetcode_152 {
// 乘积最大子数组
// 152. Maximum Product Subarray
class Solution {
public:
    static int maxProduct(std::vector<int>& nums) {
        int ans = nums[0];
        for (int i = 1, max = nums[0], min = nums[0], curmax, curmin; i < nums.size(); ++i)
        {
            curmin = std::min(nums[i], std::min(min * nums[i], max * nums[i]));
            curmax = std::max(nums[i], std::max(min * nums[i], max * nums[i]));
            min = curmin;
            max = curmax;
            ans = std::max(ans, max);
        }

        return ans;
    }
};
}

namespace max_sum_divided_by7 {
// 子序列累加和必须被7整除的最大累加和
// 给定一个非负数组nums
// 可以任意选择数字组成子序列，但是子序列的累加和必须被7整除
// 返回最大累加和
class solution
{
public:
    static int max_sum(std::vector<int> &nums)
    {
        int n = static_cast<int>(nums.size());
        // dp[i][j]:
        // nums.前i个数形成的子序列一定要做到，子序列累加和%7==j
        // 这样的子序列最大累加和是多少
        // 注意：dp[i][j]==-1代表不存在这样的子序列
        std::vector<std::vector<int>> dp(n + 1, std::vector<int>(MOD, -1));
        dp[0][0] = 0;
        for (int i = 1, x, curmod, need; i <= n; ++i)
        {
            x = nums[i-1];
            curmod = nums[i-1] % MOD;
            for (int j = 0; j < MOD; ++j)
            {
                dp[i][j] = dp[i-1][j];
                need = (j - curmod + MOD) % MOD;
                if (dp[i-1][need] != -1)
                    dp[i][j] = std::max(dp[i][j], dp[i-1][need] + x);
            }
        }

        return dp[n][0];
    }
private:
    static constexpr int MOD = 7;
};
}

namespace magic_scroll_problem {
// 魔法卷轴
// 给定一个数组nums，其中可能有正、负、0
// 每个魔法卷轴可以把nums中连续的一段全变成0 你希望数组整体的累加和尽可能大
// 卷轴使不使用、使用多少随意，但一共只有2个魔法卷轴
// 请返回数组尽可能大的累加和
class solution
{
public:
    static int max_sum(std::vector<int> &nums)
    {
        int n = static_cast<int>(nums.size());
        if (n == 0)
            return 0;
        // 情况1：完全不使用卷轴
        int p1 = 0;
        for (auto x : nums)
            p1 += x;
        // prefix[i]：0~i范围上一定要用1次卷轴的情况下，0~i范围上整体最大累加和多少
        std::vector<int> prefix(n);
        // 每一步的前缀和
        int sum = nums[0];
        // maxpresum：之前所有前缀和的最大值
        int maxpresum = std::max(0, nums[0]);
        for (int i = 1; i < n; ++i)
        {
            prefix[i] = std::max(prefix[i-1] + nums[i], maxpresum);
            sum += nums[i];
            maxpresum = std::max(maxpresum, sum);
        }
        // 情况二：必须用1次卷轴
        int p2 = prefix[n-1];
        // suffix[i]：i~n-1范围上一定要用1次卷轴的情况下，i~n-1范围上整体最大累加和多少
        std::vector<int> suffix(n);
        sum = nums[n-1];
        maxpresum = std::max(0, nums[n-1]);
        for (int i = n - 2; i >= 0; --i)
        {
            suffix[i] = std::max( suffix[i+1] + nums[i], maxpresum );
            sum += nums[i];
            maxpresum = std::max(sum, maxpresum);
        }
        // 情况二：必须用2次卷轴
        int p3 = std::numeric_limits<int>::min();
        for (int i = 1; i < n; ++i)
            p3 = std::max(p3, prefix[i-1] + suffix[i]);

        return std::max(p1, std::max(p2, p3));
    }
};
}

namespace leetcode_689 {
// 三个无重叠子数组的最大和
// 689. Maximum Sum of 3 Non-Overlapping Subarrays
class Solution {
public:
    static std::vector<int> maxSumOfThreeSubarrays(std::vector<int>& nums, int k) {
        int n = static_cast<int>(nums.size());
        // sums[i]：以i开头并且长度为k的子数组的累加和
        std::vector<int> sums( n );
        for (int l = 0, r = 0, sum = 0; r < n; ++r)
        {
            sum += nums[r];
            if (r - l + 1 == k)
            {
                sums[l] = sum;
                sum -= nums[l];
                ++l;
            }
        }
        // prefix[i]：
        // 0~i范围上所有长度为k的子数组中，拥有最大累加和的子数组，是以什么位置开头的
        std::vector<int> prefix(n);
        for (int l = 1, r = k; r < n; ++l, ++r)
        {
            if (sums[l] > sums[prefix[r-1]])
            {
                prefix[r] = l;
            }
            else
            {
                prefix[r] = prefix[r-1];
            }
        }
        // suffix[i]:
        // i~n-1范围上所有长度为k的子数组中，拥有最大累加和的子数组，是以什么位置开头的
        std::vector<int> suffix(n);
        suffix[n-k] = n - k;
        for (int l = n - k - 1; l >= 0; --l)
        {
            if (sums[l] >= sums[suffix[l+1]])
            {
                suffix[l] = l;
            }
            else
            {
                suffix[l] = suffix[l+1];
            }
        }
        int a = 0, b = 0, c = 0 ;
        int max = 0;
        for (int p, s, i = k, j = 2 * k - 1, sum; j < n - k; ++i, ++j)
        {
            p = prefix[i-1];
            s = suffix[j+1];
            sum = sums[p] + sums[i] + sums[s];
            if (sum > max)
            {
                max = sum;
                a = p;
                b = i;
                c = s;
            }
        }

        return {a, b, c};
    }
};
}

namespace max_sum_reverse {
// 可以翻转1次的情况下子数组最大累加和给定一个数组nums，
// 现在允许你随意选择数组连续一段进行翻转，也就是子数组逆序的调整
// 比如翻转[1，2,3，4，5，6]的[2~4]范围，得到的是[1,2，5，4,3，6]
// 返回必须随意翻转1次之后，子数组的最大累加和
class solution
{
public:
    static int max_sum(std::vector<int> &nums)
    {
        int n = static_cast<int>(nums.size());
        // start[i]：所有必须以i开头的子数组中，最大累加和是多少
        std::vector<int> start(n);
        start[n-1] = nums[n-1];
        for (int i = n - 2; i >= 0; --i)
        {
            start[i] = nums[i] + std::max(0, start[i+1]);
        }
        int ans = start[0];
        //end：子数组必须以i结尾，其中的最大累加和
        int end = nums[0];
        int maxend = nums[0];
        // maxEnd:
        // 0~i-1范围上
        // 子数组必须以0结尾，其中的最大累加和
        // 子数组必须以1结尾，其中的最大累加和
        // ...
        // 子数组必须以i-1结尾，其中的最大累加和
        // 所有情况中，最大的那个累加和就是maxEnd
        for (int i = 1; i < n; ++i)
        {
            // maxend       i...
            // 枚举划分点：   i...
            ans = std::max(ans, maxend + start[i]);
            //子数组必须以i结尾，其中的最大累加和
            end = nums[i] + std::max(0, end);
            maxend = std::max(end, maxend);
        }
        ans = std::max(ans, maxend);
        return ans;
    }
};
}

namespace leetcode_300 {
// 最长递增子序列
// 300. Longest Increasing Subsequence
class Solution {
public:
    static int lengthOfLIS(std::vector<int>& nums) {
        int n = static_cast<int>(nums.size());
        std::vector<int> ends(n);
        int len = 0;
        //len表示ends数组目前的有效区长度
        //ends[0.。.len-1]是有效区，有效区内的数字一定严格升序
        for (int i = 0, find; i < n; ++i)
        {
            find = bs1(ends, len, nums[i]);
            if (find == -1)
                ends[len++] = nums[i];
            else
            {
                ends[find] = nums[i];
            }
        }

        return len;
    }
    static int bs1(std::vector<int> &ends, int len, int num)
    {
        int l = 0, r = len - 1;
        int m, ans = -1;
        while (l <= r)
        {
            m = (l + r) / 2;
            if (num <= ends[m])
            {
                r = m - 1;
                ans = m;
            }
            else
            {
                l = m + 1;
            }
        }
        return ans;
    }
    //普通解法的动态规划
    //时间复杂度0（n^2），数组稍大就会超时
    static int lengthOfLIS1(std::vector<int>& nums) {
        int n = static_cast<int>(nums.size());
        std::vector<int> dp(n);
        int ans = 0;
        for (int i = 0; i < n; ++i)
        {
            dp[i] = 1;
            for (int j = 0; j < i; ++j)
            {
                if (nums[j] < nums[i])
                    dp[i] = std::max(dp[i], dp[j] + 1);
            }
            ans = std::max(ans, dp[i]);
        }
        return ans;
    }
};
}

namespace leetcode_354 {
// 俄罗斯套娃信封问题
// 354. Russian Doll Envelopes
class Solution {
public:
    int maxEnvelopes(std::vector<std::vector<int>>& envelopes) {
        int n = static_cast<int>(envelopes.size());
        //排序策略：
        //宽度从小到大
        //宽度一样，高度从大到小
        auto cmp = [](auto &e1, auto &e2) {
            if (e1[0] != e2[0])
                return e1[0] < e2[0];
            else
                return e1[1] > e2[1];
        };
        std::sort(envelopes.begin(), envelopes.end(), cmp);
        std::vector<int> ends( n );
        int len = 0;
        for (int i = 0, find, num; i < n; ++i)
        {
            num = envelopes[i][1];
            find = bs(ends, len, num);
            if (find == -1)
                ends[len++] = num;
            else
            {
                ends[find] = num;
            }
        }

        return len;
    }
    int bs(std::vector<int> &ends, int len, int num)
    {
        int l = 0, r = len - 1, m, ans = -1;
        while (l <= r)
        {
            m = (l + r) / 2;
            if (ends[m] >= num)
            {
                ans = m;
                r = m - 1;
            }
            else
            {
                l = m + 1;
            }
        }
        return ans;
    }
};
}

namespace leetcode_2111 {
// 使数组K递增的最少操作次数
// 2111. Minimum Operations to Make the Array K-Increasing
class Solution {
public:
    int kIncreasing1(std::vector<int>& arr, int k) {
        int n = static_cast<int>(arr.size());
        int ans = 0;
        std::vector<int> nums( n );
        for (int i = 0, size; i < k; ++i)
        {
            size = 0;
            //把每一组的数字放入容器
            for (int j = i; j < n; j += k)
            {
                nums[size++] = arr[j];
            }
            //当前组长度 - 当前组最长不下降子序列长度 = 当前组至少需要修改的数字个数
            ans += size - lengthof_nodecreasing(nums, size);
        }
        return ans;
    }
    static int kIncreasing(std::vector<int>& arr, int k) {
        int n = static_cast<int>(arr.size());
        int ans = 0;
        for (int i = 0; i < k; ++i)
        {
            std::vector<int> f;
            int len = 0;
            for (int j = i; j < n; j += k)
            {
                ++len;
                auto it = std::upper_bound(f.begin(), f.end(), arr[j]);
                if (it == f.end())
                    f.push_back(arr[j]);
                else
                {
                    *it = arr[j];
                }
            }
            ans += len - static_cast<int>(f.size());
        }
        return ans;
    }
    int lengthof_nodecreasing(std::vector<int> &nums, int size)
    {
        std::vector<int> ends(nums.size());
        int len = 0;
        for (int i = 0, find; i < size; ++i)
        {
            find = bs(ends, len, nums[i]);
            if (find == -1)
                ends[len++] = nums[i];
            else
            {
                ends[find] = nums[i];
            }
        }
        return len;
    }
    int bs(std::vector<int> &ends, int len, int num)
    {
        int l = 0, r = len - 1, ans = -1;
        int m;
        while (l <= r)
        {
            m = (l + r) / 2;
            if (num < ends[m])
            {
                ans = m;
                r = m - 1;
            }
            else
            {
                l = m + 1;
            }
        }
        return ans;
    }
};
}

namespace leetcode_646 {
// 最长数对链
// 646. Maximum Length of Pair Chain
class Solution {
public:
    int findLongestChain(std::vector<std::vector<int>>& pairs) {
        int n = static_cast<int>(pairs.size());
        auto cmp = [](auto &p1, auto &p2) {
            return p1[0] < p2[0];
        };
        std::sort(pairs.begin(), pairs.end(), cmp);
        std::vector<int> ends(n);
        int len = 0;
        for (auto &pair : pairs)
        {
            int find = bs(ends, len, pair[0]);
            if (find == -1)
                ends[len++] = pair[1];
            else
            {
                ends[find] = std::min(ends[find], pair[1]);
            }
        }
        return len;
    }
    int bs(std::vector<int> &ends, int len, int num)
    {
        int l = 0, r = len - 1, ans = -1;
        int m;
        while (l <= r)
        {
            m = (l + r) / 2;
            if (num <= ends[m])
            {
                ans = m;
                r = m - 1;
            }
            else
            {
                l = m + 1;
            }
        }
        return ans;
    }
};
}

namespace _01backpack {
// 01backpack 标准模板
class solution
{
public:
    void read()
    {
        std::cin >> t >> n;
        int c, v;
        for (int i = 0; i < n; ++i)
        {
            std::cin >> c >> v;
            cost.push_back(c);
            val.push_back(v);
        }
    }
    // 严格位置依赖的动态规划
    // n个物品编号1~n，第i号物品的花费cost[i]、价值val[i]
    // cost、val数组是全局变量，已经把数据读入了
    int compute1()
    {
        std::vector<std::vector<int>> dp(n + 1, std::vector<int>(t + 1));
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 0; j <= t; ++j)
            {
                dp[i][j] = dp[i-1][j];
                if (j - cost[i] >= 0)
                {
                    dp[i][j] = std::max(dp[i][j], dp[i-1][j-cost[i]] + val[i]);
                }
            }
        }
        return dp[n][t];
    }
    // 空间压缩
    int compute2()
    {
        std::vector<int> dp(t + 1);
        for (int i = 1; i <= n; ++i)
        {
            for (int j = t; j >= cost[i]; --j)
            {
                dp[j] = std::max(dp[j], dp[j-cost[i]] + val[i]);
            }
        }
        return dp[t];
    }

private:
    std::vector<int> cost;
    std::vector<int> val;
    int n{0}, t{0};
};
void test()
{
    solution so;
    so.read();
    std::cout << so.compute2();
}
}

namespace bytedance_006 {
/*
 * 某公司游戏平台的夏季特惠开始了，你决定入手一些游戏。现在你一共有X元的预算，
 * 该平台上所有的 n 个游戏均有折扣，标号为 i 的游戏的原价ai元，现价只要bi元
 * （也就是说该游戏可以优惠ai−bi元）并且你购买该游戏能获得快乐值为wi。
 * 由于优惠的存在，你可能做出一些冲动消费导致最终买游戏的总费用超过预算，
 * 但只要满足获得的总优惠金额不低于超过预算的总金额，那在心理上就不会觉得吃亏。
 * 现在你希望在心理上不觉得吃亏的前提下，获得尽可能多的快乐值。
 */
constexpr int N = 501;
constexpr int X = 100'001;
int cost[N];
long val[N];
long dp[X];

int n, m, x;
long compute();
void entry()
{
    std::cin >> n >> x;
    int ai, bi; long wi;
    m = 1;
    long ans = 0;
    for (int i = 0, well; i < n; ++i)
    {
        std::cin >> ai >> bi >> wi;
        well = ai - bi - bi;
        if (well >= 0)
        {
            x += well;
            ans += wi;
        }
        else
        {
            cost[m] = -well;
            val[m++] = wi;
        }
    }
    ans += compute();
    std::cout << ans;
}

long compute()
{
    for (int i = 1; i <= m; ++i)
    {
        for (int j = x; j >= cost[i]; --j)
        {
            dp[j] = std::max(dp[j], dp[j-cost[i]] + val[i]);
        }
    }
    return dp[x];
}
}

namespace leetcode_494 {
// 494. 目标和
class Solution {
public:
    int findTargetSumWays(std::vector<int>& nums, int target) {

    }
};
}







































int main()
{
//    _01backpack::test();
    bytedance_006::entry();
    return 0;
}