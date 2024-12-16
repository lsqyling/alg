//
// Created by 10580.
//
#include "../utilities.hpp"


namespace prefix_tree {
class trie
{
public:
    trie() : root(new trie_node) {}

    void insert(std::string_view word)
    {
        auto node = root;
        node->pass++;
        for (int i = 0, idx; i < word.size(); ++i)
        {
            idx = word[i] - 'a';
            if (node->next[idx] == nullptr)
                node->next[idx] = new trie_node;
            node = node->next[idx];
            node->pass++;
        }
        node->end++;
    }

    [[nodiscard]]
    int count_words_equal_to(std::string_view word) const
    {
        auto node = root;
        for (char i : word)
        {
            auto idx = i - 'a';
            if (node->next[idx] == nullptr)
                return 0;
            node = node->next[idx];
        }
        return node->end;
    }

    [[nodiscard]]
    int count_words_starting_with(std::string_view prefix) const
    {
        auto node = root;
        for (int i = 0, idx; i < prefix.size(); ++i)
        {
            idx = prefix[i] - 'a';
            if (node->next[idx] == nullptr)
                return 0;
            node = node->next[idx];
        }
        return node->pass;
    }


    void erase(std::string_view word)
    {
        if (count_words_equal_to(word) > 0)
        {
            auto node = root;
            node->pass--;
            for (int i = 0, idx; i < word.size(); ++i)
            {
                idx = word[i] - 'a';
                if (--node->next[idx]->pass == 0)
                {
                    delete_nodes(node->next[idx], i, word);
                    node->next[idx] = nullptr;
                    return ;
                }
                node = node->next[idx];
            }
            --node->end;
        }
    }
private:
    struct trie_node
    {
        int pass{0};
        int end{0};
        trie_node *next[26]{};
    };

    static void delete_nodes(trie_node *node, int start, std::string_view word)
    {
        for (int i = start + 1, idx; i < word.size(); ++i)
        {
            idx = word[i] - 'a';
            auto p = node;
            if (node->next[idx])
                node = node->next[idx];
            else
                break;
            delete p;
        }
    }

    trie_node *root;
};
}

namespace static_trie {
constexpr int N = 150000;

int trie[N][26];
int pass[N], end[N];
int cnt = 0;

void rebuild()
{
    for (int i = 1; i <= cnt; ++i)
    {
        std::fill_n(trie[i], 3, 0);
        pass[i] = end[i] = 0;
    }
    cnt = 1;
}

void insert(std::string_view word)
{
    int node = 1;
    pass[node]++;
    for (int i = 0, path; i < word.size(); ++i)
    {
        path = word[i] - 'a';
        if (trie[node][path] == 0)
            trie[node][path] = ++cnt;
        node = trie[node][path];
        pass[node]++;
    }
    end[node]++;
}

int search(std::string_view word)
{
    int node = 1;
    for (int i = 0, path; i < word.size(); ++i)
    {
        path = word[i] - 'a';
        if (trie[node][path] == 0)
            return 0;
        node = trie[node][path];
    }
    return end[node];
}


int prefix_number(std::string_view word)
{
    int node = 1;
    for (int i = 0, path; i < word.size(); ++i)
    {
        path = word[i] - 'a';
        if (trie[node][path] == 0)
            return 0;
        node = trie[node][path];
    }
    return pass[node];
}

void delete_word(std::string_view word)
{
    if (search(word))
    {
        int node = 1;
        for (int i = 0, path; i < word.size(); ++i)
        {
            path = word[i] - 'a';
            if (--pass[trie[node][path]] == 0)
            {
                trie[node][path] = 0;
                return;
            }
            node = trie[node][path];
        }
        end[node]--;
    }
}

void entry()
{
    int m, op;
    char str[25];
    scanf("%d", &m);
    rebuild();
    while (m--)
    {
        scanf("%d%s", &op, str);
        switch (op)
        {
            case 1:
                insert(str);
                break;
            case 2:
                delete_word(str);
                break;
            case 3:
                if (search(str))
                    printf("YES\n");
                else
                    printf("NO\n");
                break;
            case 4:
                printf("%d\n", prefix_number(str));
                break;
            default:
                break;
        }
    }
}
}

namespace nowcoder_prefix_tree {
constexpr int N = 100'005;

int tree[N][12];
int pass[N], end[N];
int cnt = 0;

void rebuild()
{
    for (int i = 1; i <= cnt; ++i)
    {
        std::fill_n(tree[i], 12, 0);
        pass[i] = end[i] = 0;
    }
    cnt = 1;
}

int path_of(char c)
{
    if (c == '-')
        return 10;
    else if (c == '#')
        return 11;
    else
        return c - '0';
}

void insert(std::string_view word)
{
    int node = 1;
    pass[node]++;
    for (int i = 0, path; i < word.size(); ++i)
    {
        path = path_of(word[i]);
        if (tree[node][path] == 0)
            tree[node][path] = ++cnt;
        node = tree[node][path];
        pass[node]++;
    }
    end[node]++;
}

int count_prefix_with(std::string_view prefix)
{
    int node = 1;
    for (int i = 0, path; i < prefix.size(); ++i)
    {
        path = path_of(prefix[i]);
        if (tree[node][path] == 0)
            return 0;
        node = tree[node][path];
    }
    return pass[node];
}

class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     *
     * @param b int整型vector<vector<>>
     * @param a int整型vector<vector<>>
     * @return int整型vector
     */
    static std::vector<int> countConsistentKeys(std::vector<std::vector<int> >& b, std::vector<std::vector<int> >& a) {
        rebuild();
        for (auto &arr : a)
        {
            std::string word;
            for (int i = 1; i < arr.size(); ++i)
                word += std::to_string(arr[i] - arr[i-1]) + "#";
            insert(word);
        }

        std::vector<int> ans;
        for (auto &arr : b)
        {
            std::string word;
            for (int i = 1; i < arr.size(); ++i)
                word += std::to_string(arr[i] - arr[i-1]) + "#";
            ans.push_back(count_prefix_with(word));
        }

        return ans;
    }
};
}

namespace leetcode_421 {
class Solution {
public:
    int findMaximumXOR(std::vector<int>& nums) {
        build(nums);
        int ans = 0;
        for (auto num : nums)
            ans = std::max(ans, max_xor(num));
        clear();
        return ans;
    }
    
    void clear()
    {
        for (int i = 1; i <= cnt; ++i)
        {
            tree[i][0] = tree[i][1] = 0;
        }
        cnt = 0;
    }

    void build(std::vector<int> &nums)
    {
        cnt = 1;
        int max = std::numeric_limits<int>::min();
        for (auto n : nums)
            max = std::max(max, n);

        high = 31 - number_of_leading_zeroes(max);
        for (auto num : nums)
            insert(num);
    }

    void insert(int n)
    {
        int node = 1;
        for (int i = high, path; i >= 0; --i)
        {
            path = (n >> i) & 1;
            if (tree[node][path] == 0)
                tree[node][path] = ++cnt;
            node = tree[node][path];
        }
    }

    int max_xor(int num)
    {
        int ans = 0;
        int node = 1;
        for (int i = high, status, want; i >= 0; --i)
        {
            status = (num >> i) & 1;
            want = status ^ 1;
            if (tree[node][want] == 0)
                want ^= 1;
            ans |= (status ^ want) << i;
            node = tree[node][want];
        }

        return ans;
    }

    static int number_of_leading_zeroes(int num)
    {
        int t = 0;
        do
        {
            ++t;
            num >>= 1;
        } while (num);
        return 32 - t;
    }

private:
    static constexpr int N = 30'000'05;
    int tree[N][2]{};
    int cnt{0};
    int high{0};

};
}

namespace leetcode_212 {
//212. Word Search II
class Solution {
public:
    std::vector<std::string> findWords(std::vector<std::vector<char>>& board, std::vector<std::string>& words) {
        build(words);
        std::vector<std::string> ans;
        for (int i = 0; i < board.size(); ++i)
        {
            for (int j = 0; j < board[0].size(); ++j)
                dfs(board, i, j, 1, ans);
        }

        return ans;
    }

    void build(std::vector<std::string> &words)
    {
        cnt = 1;
        for (auto &s : words)
            insert(s);
    }

    void insert(std::string_view word)
    {
        int node = 1;
        pass[node]++;
        for (int i = 0, path; i < word.size(); ++i)
        {
            path = word[i] - 'a';
            if (trie[node][path] == 0)
                trie[node][path] = ++cnt;
            node = trie[node][path];
            pass[node]++;
        }
        end[node] = word;
    }

    int dfs(std::vector<std::vector<char>> &board, int i, int j, int t, std::vector<std::string> &ans)
    {
        if (i < 0 || i == board.size() || j < 0 || j == board[0].size() || board[i][j] == 0)
            return 0;

        auto tmp = board[i][j];
        int path = tmp - 'a';
        t = trie[t][path];
        if (pass[t] == 0)
            return 0;
        int count = 0;
        if (!end[t].empty())
        {
            count++;
            ans.push_back(end[t]);
            end[t] = {};
        }
        board[i][j] = 0;
        count += dfs(board, i + 1, j, t, ans);
        count += dfs(board, i - 1, j, t, ans);
        count += dfs(board, i, j + 1, t, ans);
        count += dfs(board, i, j - 1, t, ans);
        pass[t] -= count;
        board[i][j] = tmp;

        return count;
    }



private:
    static constexpr int N = 3'000'05;
    int trie[N][26]{};
    int pass[N];
    std::string end[N];
    int cnt{0};
};
}

namespace leetcode_303 {
//303. Range Sum Query - Immutable
class NumArray {
public:
    NumArray(std::vector<int>& nums) : sum(nums.size() + 1) {
        for (int i = 1; i <= nums.size(); ++i)
            sum[i] = sum[i-1] + nums[i-1];
    }

    int sumRange(int left, int right) {
        return sum[right+1] - sum[left];
    }

private:
    std::vector<int> sum;
};
}

namespace max_len_subsum {
constexpr int N = 10'0005;
int nums[N];
std::map<int, int> map;

int max_lenof(int n, int k)
{
    map.clear();
    map[0] = -1;
    int ans = 0;
    for (int i = 0, sum = 0; i < n; ++i)
    {
        sum += nums[i];
        if (auto it = map.find(sum - k); it != map.end())
        {
            ans = std::max(ans, i - map[sum-k]);
        }
        if (auto it = map.find(sum); it == map.end())
            map[sum] = i;
    }

    return ans;
}

void entry()
{
    int n, k;
    scanf("%d%d", &n, &k);
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &nums[i]);
    }
    printf("%d\n", max_lenof(n, k));
}
}

namespace leetcode_560 {
//560. Subarray Sum Equals K
class Solution {
public:
    static int subarraySum(std::vector<int>& nums, int k) {
        std::map<int, int> map;
        map[0] = 1;
        int ans = 0;
        for (int i = 0, sum = 0; i < nums.size(); ++i)
        {
            sum += nums[i];
            ans += map[sum-k];
            ++map[sum];
        }

        return ans;
    }
};
}

namespace leetcode_1124 {
//1124. Longest Well-Performing Interval
class Solution {
public:
    static int longestWPI(std::vector<int>& hours) {
        std::map<int, int> map;
        map[0] = -1;
        int ans = 0;
        for (int i = 0, sum = 0; i < hours.size(); ++i)
        {
            sum += hours[i] > 8 ? 1 : -1;
            if (sum > 0)
                ans = i + 1;
            else
            {
                if (auto it = map.find(sum - 1); it != map.end())
                    ans = std::max(ans, i - map[sum-1]);
            }
            if (auto it = map.find(sum); it == map.end())
                map[sum] = i;
        }
        return ans;
    }
};
}

namespace leetcode_1590 {
//1590. Make Sum Divisible by P
class Solution {
public:
    static int minSubarray(std::vector<int>& nums, int p) {
        int mod = 0;
        for (auto num : nums)
            mod = ( mod + num ) % p;
        if (mod == 0)
            return 0;

        std::unordered_map<int, int> map;
        map[0] = -1;
        int ans = std::numeric_limits<int>::max();
        for (int i = 0, cur = 0, find; i < nums.size(); ++i)
        {
            cur = (cur + nums[i]) % p;
            find = (cur + p - mod) % p;
            if (map.contains(find))
                ans = std::min(ans, i - map[find]);
            map[cur] = i;
        }

        return ans == nums.size() ? -1 : ans;
    }
};
}

namespace leetcode_1371 {
//1371. Find the Longest Substring Containing Vowels in Even Counts
class Solution {
public:
    static int findTheLongestSubstring(std::string s) {
        int map[32];
        std::fill_n(map, 32, -2);
        map[0] = -1;
        int ans = 0;
        for (int i = 0, status = 0, m; i < s.size(); ++i)
        {
            m = move(s[i]);
            if (m != -1)
                status ^= 1 << m;
            if (map[status] != -2)
                ans = std::max(ans, i - map[status]);
            else
                map[status] = i;
        }

        return ans;
    }

    static int move(char c)
    {
        switch (c)
        {

            case 'a':
                return 0;
            case 'e':
                return 1;
            case 'i':
                return 2;
            case 'o':
                return 3;
            case 'u':
                return 4;
            default:
                return -1;
        }
    }
};
}

namespace leetcode_1109 {
//1109. Corporate Flight Bookings
class Solution {
public:
    static std::vector<int> corpFlightBookings(std::vector<std::vector<int>>& bookings, int n) {
        std::vector<int> cnt(n + 2);
        for (auto &arr : bookings)
        {
            cnt[arr[0]] += arr[2];
            cnt[arr[1]+1] -= arr[2];
        }
        for (int i = 1; i < cnt.size(); ++i)
        {
            cnt[i] += cnt[i-1];
        }

        return { cnt.begin() + 1, cnt.begin() + 1 + n };
    }
};
}

namespace leetcode_304 {
//304. Range Sum Query 2D - Immutable
class NumMatrix {
public:
    NumMatrix(std::vector<std::vector<int>>& matrix)
        : sum(matrix.size() + 1, std::vector<int>(matrix[0].size() + 1)) {
        for (int i = 0; i < matrix.size(); ++i)
        {
            for (int j = 0; j < matrix[0].size(); ++j)
            {
                sum[i+1][j+1] = matrix[i][j];
            }
        }
        for (int i = 1; i < sum.size(); ++i)
        {
            for (int j = 1; j < sum[0].size(); ++j)
            {
                sum[i][j] += sum[i][j-1] + sum[i-1][j] - sum[i-1][j-1];
            }
        }

    }

    int sumRegion(int row1, int col1, int row2, int col2) {
        ++row2, ++col2;
        return sum[row2][col2] - sum[row1][col2] - sum[row2][col1] + sum[row1][col1];
    }

private:
    std::vector<std::vector<int>> sum;
};
}

namespace leetcode_1139 {
//1139. Largest 1-Bordered Square
class Solution {
public:
    static int largest1BorderedSquare(std::vector<std::vector<int>>& grid) {
        int n = grid.size();
        int m = grid.size();
        std::vector<std::vector<int>> prefixsum(n + 1, std::vector<int>(m + 1));
        int ans = 0;

        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= m; ++j)
            {
                prefixsum[i][j] = prefixsum[i-1][j] + prefixsum[i][j-1];
                if (grid[i-1][j-1] != 1)
                    continue;
                for (int k = 1; i - k >= 0 && j - k >= 0; ++k)
                {
                    int s1 = prefixsum[i][j] - prefixsum[i-k][j] - prefixsum[i][j-k] + prefixsum[i-k][j-k];
                    int s2 = prefixsum[i-1][j-1] - prefixsum[i-k+1][j-1] - prefixsum[i-1][j-k+1] + prefixsum[i-k+1][j-k+1];
                    int t = k - 2;
                    if (s1 - s2 == k * k - t * t)
                        ans = std::max(ans, k * k);
                }
            }
        }

        return ans;
    }
};
}

int main()
{
    int n = 112;
    std::cout << leetcode_421::Solution::number_of_leading_zeroes(n) << std::endl;
//    static_trie::entry();
    return 0;
}