#include "../utilities.hpp"

namespace strsubseq {
//字符串的全部子序列
//https://www.nowcoder.com/practice/92e6247998294f2c933906fdedbc6e6a
class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     *
     * @param s string字符串
     * @return string字符串vector
     */
    std::vector<std::string> generatePermutation(std::string s) {
        len = s.size();
        dfs(s, {}, 0);

        return ans;
    }

    void dfs(std::string str, std::string x, int i)
    {
        if (i == len)
        {
            if (!set.contains(x))
            {
                ans.push_back(x);
                set.insert(x);
            }
            return ;
        }
        dfs(str, x, i + 1);
        dfs(str, x + str[i], i + 1);
    }



private:
    int len;
    std::unordered_set<std::string> set;
    std::vector<std::string> ans;

};
}

namespace leetcode_90 {
//90. Subsets II
class Solution {
public:
    std::vector<std::vector<int>> subsetsWithDup(std::vector<int>& nums) {
        std::sort(nums.begin(), nums.end());
        dfs(false, 0, nums);
        return ans;
    }

    void dfs(bool choosepre, int index, std::vector<int>  &nums)
    {
        if (index == nums.size())
        {
            ans.push_back(path);
            return ;
        }
        dfs(false, index + 1, nums);
        if (!choosepre && index > 0 && nums[index-1] == nums[index])
            return ;
        path.push_back(nums[index]);
        dfs(true, index + 1, nums);
        path.pop_back();
    }

private:
    std::vector<int> path;
    std::vector<std::vector<int>> ans;
};
}

namespace leetcode_46 {
//46. Permutations
class Solution {
public:
    std::vector<std::vector<int>> permute(std::vector<int>& nums) {
        dfs(0, nums);
        return ans;
    }

    void dfs(int i, std::vector<int> &nums)
    {
        if (i == nums.size())
        {
            ans.push_back(nums);
            return ;
        }
        for (int j = i; j < nums.size(); ++j)
        {
            std::swap(nums[i], nums[j]);
            dfs(i + 1, nums);
            std::swap(nums[i], nums[j]);
        }
    }


private:
    std::vector<std::vector<int>> ans;

};
}

namespace leetcode_47 {
//47. Permutations II
class Solution {
public:
    std::vector<std::vector<int>> permuteUnique(std::vector<int>& nums) {
        dfs(0, nums);
        return ans;
    }

    void dfs(int i, std::vector<int> &nums)
    {
        if (i == nums.size())
        {
            ans.push_back(nums);
            return ;
        }
        std::unordered_set<int> set;
        for (int j = i; j < nums.size(); ++j)
        {
            if (!set.contains(nums[j]))
            {
                set.insert(nums[j]);
                std::swap(nums[i], nums[j]);
                dfs(i + 1, nums);
                std::swap(nums[i], nums[j]);
            }
        }
    }

private:
    std::vector<std::vector<int>> ans;
};
}

namespace reverse_stack {
int bottom_out(std::stack<int> &);
void reverse(std::stack<int> &stack)
{
    if (stack.empty())
        return ;

    auto val = bottom_out(stack);
    reverse(stack);
    stack.push(val);
}

int bottom_out(std::stack<int> &stack)
{
    auto val = stack.top();
    stack.pop();
    if (stack.empty())
        return val;

    auto next = bottom_out(stack);
    stack.push(val);
    return next;
}

void test_reverse_stack()
{
    std::stack<int> stack;
    for (int i = 0; i < 10; ++i)
    {
        stack.push(i);
    }
    reverse(stack);
    for (int i = 0; i < 10; ++i)
    {
        auto top = stack.top();
        stack.pop();
        std::cout << top << " ";
    }
    std::cout << std::endl;

}
}

namespace sort_stack {
int deep(std::stack<int> &);
int max(std::stack<int> &, int deep);
int times(std::stack<int> &, int max, int deep);
void down(std::stack<int> &, int max, int times, int deep);

void sort(std::stack<int> &stack)
{
    int d = deep(stack);
    while (d)
    {
        auto m = max(stack, d);
        auto t = times(stack, m, d);
        down(stack, m, t, d);
        d -= t;
    }
}


int deep(std::stack<int> &stack)
{
    if (stack.empty())
        return 0;
    auto top = stack.top();
    stack.pop();
    auto d = deep(stack) + 1;
    stack.push(top);
    return d;
}

int max(std::stack<int> &stack, int deep)
{
    if (deep == 0)
        return std::numeric_limits<int>::min();

    auto top = stack.top();
    stack.pop();
    auto restmax = max(stack, deep - 1);
    stack.push(top);
    return std::max(top, restmax);
}

int times(std::stack<int> &stack, int max, int deep)
{
    if (deep == 0)
        return 0;

    auto num = stack.top();
    stack.pop();
    auto resttimes = times(stack, max, deep - 1);
    stack.push(num);

    return (num == max ? 1 : 0) + resttimes;
}

void down(std::stack<int> &stack, int max, int times, int deep)
{
    if (deep == 0)
    {
        for (int i = 0; i < times; ++i)
            stack.push(max);
        return;
    }

    auto num = stack.top();
    stack.pop();
    down(stack, max, times, deep - 1);
    if (num != max)
        stack.push(num);
}

void test_sort_stack()
{
    std::stack<int> stack;
    for (int i = 0; i < 20; ++i)
    {
        stack.push(gen_random(0, 10));
    }

    sort(stack);
    while (!stack.empty())
    {
        auto top = stack.top();
        stack.pop();
        std::cout << top << " ";
    }
    std::cout << std::endl;
}
}

namespace hanoi {
void move(int n, char from, char to, char other);

void hanoi_do(int n)
{
    if (n <= 0)
        return ;
    std::cout << std::format("注意盘子是从小到大编号为1-{}，移动过程如下:\n", n);
    move(n, 'A', 'B', 'C');
}

void move(int n, char from, char to, char other)
{
    if (n == 1)
    {
        std::cout << std::format("圆盘: {}: {} -> {}\n", n, from, to);
        return ;
    }

    move(n-1, from, other, to);
    std::cout << std::format("圆盘: {}: {} -> {}\n", n, from, to);
    move(n-1, other, to, from);
}

void test_hanoi()
{
    int n = 3;
    hanoi_do(n);
}
}

namespace leetcode_772 {
//772.basic calculator iii
class Solution {
public:
    int calculate(std::string str)
    {
        cin.str(str);
        return expression_value();
    }
    int expression_value()
    {
        int result = term_value();
        while (true)
        {
            auto op = cin.peek();
            if (op == '+' || op == '-')
            {
                cin.get();
                int val = term_value();
                if (op == '+')
                    result += val;
                else
                    result -= val;
            }
            else
                break;
        }
        return result;
    }

    int term_value()
    {
        int result = factor_value();
        while(true)
        {
            auto op = cin.peek();
            if (op == '*' || op == '/')
            {
                cin.get();
                int val = factor_value();
                if (op == '*')
                    result *= val;
                else
                    result /= val;
            }
            else
                break;
        }
        return result;
    }

    int factor_value()
    {
        int result = 0;
        auto c = cin.peek();
        if (c == '(')
        {
            cin.get();
            result = expression_value();
            cin.get();
        }
        else
        {
            while (std::isdigit(c))
            {
                result = result * 10 + c - '0';
                cin.get();
                c = cin.peek();
            }
        }
        return result;
    }

private:
    std::istringstream cin;
};
}

void test_leetcode_772()
{
    std::string str{"3+4*5-(2+4)/2-(3*(2+2))"};
    leetcode_772::Solution s;
    std::cout << s.calculate(str) << std::endl;
}



namespace leetcode_394 {
//394. Decode String
class Solution {
public:
    std::string decodeString(std::string s) {
        src = s;
        index = 0;

        return get_string();
    }

    std::string get_string()
    {
        if (index == src.size() || src[index] == ']')
            return {};

        std::string ret;
        char cur = src[index];
        int reptimes = 1;

        if (std::isdigit(cur))
        {
            reptimes = get_num();
            ++index;
            auto str = get_string();
            ++index;
            while (reptimes--) ret += str;
        }
        else if (std::isalpha(cur))
        {
            ret += cur;
            ++index;
        }

        return ret + get_string();
    }

    int get_num()
    {
        int ans = 0;
        while (index < src.size() && std::isdigit(src[index]))
            ans = ans * 10 + src[index++] - '0';
        return ans;
    }
private:
    std::string src;
    int index;
};
}

namespace leetcode_726 {
// 726. Number of Atoms
class Solution {
public:
    std::string countOfAtoms(std::string formula) {
        where = 0;
        auto tm = dfs(formula, 0);
        std::string ans;
        for (auto &it : tm)
        {
            ans += it.first;
            if (it.second > 1)
                ans += std::to_string(it.second);
        }
        return ans;
    }

    std::map<std::string, int> dfs(const std::string &str, int i)
    {
        std::map<std::string, int> ans;
        std::map<std::string, int> pre;
        std::string name;
        int cnt = 0;

        while (i < str.size() && str[i] != ')')
        {
            if ((str[i] >= 'A' && str[i] <= 'Z') || str[i] == '(')
            {
                fill(ans, name, pre, cnt);
                name.clear();
                pre.clear();
                cnt = 0;
                if (str[i] >= 'A' && str[i] <= 'Z')
                    name += str[i++];
                else
                {
                    pre = dfs(str, i + 1);
                    i = where + 1;
                }

            }
            else if (str[i] >= 'a' && str[i] <= 'z')
                name += str[i++];
            else
                cnt = cnt * 10 + str[i++] - '0';

        }
        fill(ans, name, pre, cnt);
        where = i;
        return ans;
    }

    static void fill(std::map<std::string, int> &ans, std::string &name, std::map<std::string, int> &pre, int cnt)
    {
        if (!name.empty() || !pre.empty())
        {
            cnt = cnt == 0 ? 1 : cnt;
            if (!name.empty())
                ans[name] += cnt;
            else
            {
                for (const auto &it : pre)
                    ans[it.first] += it.second * cnt;
            }
        }
    }

private:
    int where;
};
}

namespace nqueens {
// 52. N-Queens II
class Solution {
public:
    int totalNQueens_(int n) {
        if (n < 1)
            return 0;

        std::vector<int> path(n);
        return dfs_(0, path, n);
    }


    int totalNQueens(int n) {
        int limit = (1 << n) - 1;

        return dfs(limit, 0, 0, 0);
    }

    /**
     * @limit 当前是几皇后的问题
     * @col   之前皇后的列影响
     * @left  之前皇后的右上-》左下的影响
     * @right 之前皇后的左上-》右下的影响
     */
    int dfs(int limit, int col, int left, int right)
    {
        if (limit == col)
            return 1;

        int ban = col | left | right;
        int candi = limit & (~ban);
        // try place queen
        int place = 0;

        int ans = 0;
        while (candi)
        {
            place = candi & (-candi);
            candi ^= place;
            ans += dfs(limit, col | place, (left | place) << 1, (right | place) >> 1);
        }

        return ans;
    }

    int dfs_(int i, std::vector<int> &path, int n)
    {
        if (i == n)
            return 1;

        int res = 0;
        for (int j = 0; j < n; ++j)
        {
            if (check(path, i, j))
            {
                path[i] = j;
                res += dfs_(i + 1, path, n);
            }
        }
        return res;
    }

    static bool check(std::vector<int> &path, int i, int j)
    {
        for (int k = 0; k < i; ++k)
        {
            if (j == path[k] || std::abs(i - k) == std::abs(j - path[k]))
                return false;
        }
        return true;
    }

};

void test_queen()
{
    int n = 8;
    Solution so;
    auto st = std::chrono::system_clock::now();
    so.totalNQueens(n);
    auto et = std::chrono::system_clock::now();
    std::chrono::duration<double, std::milli > elasped{et - st};
    std::cout << "bitsqueen: it cost " << elasped.count() << " ms.\n";

    st = std::chrono::system_clock::now();
    so.totalNQueens_(n);
    et = std::chrono::system_clock::now();
    std::chrono::duration<double, std::milli > elasped0{et - st};
    std::cout << "arrqueen: it cost " << elasped0.count() << " ms.\n";
}

}

namespace leetcode_878 {
// 878. Nth Magical Number
class Solution {
public:
    int nthMagicalNumber(int n, int a, int b) {
        long ans = 0;
        long lcm = this->lcm(a, b);
        for (long l = 0, r = (long)std::min(a, b) * n; l <= r;)
        {
            long mid = (l + r) / 2;
            if (mid / a + mid / b - mid / lcm >= n)
            {
                ans = mid;
                r = mid - 1;
            }
            else
                l = mid + 1;
        }
        return ans % 1000'000'007;
    }

    long lcm(long a, long b)
    {
        return a / gcd(a, b) * b;
    }

    long gcd(long a, long b)
    {
        if (b == 0)
            return a;
        return gcd(b, a % b);
    }
};
}

namespace applebags {
/**
 * 有装下8个苹果的袋子、装下6个苹果的袋子，一定要保证买苹果时所有使用的袋子都装满
 * 对于无法装满所有袋子的方案不予考虑，给定n个苹果，返回至少要多少个袋子
 * 如果不存在每个袋子都装满的方案返回-1
 */
 int bag0(int apple);
 int simple_f(int rest);
 int bag1(int apple);

int bag0(int apple)
{
    int ans = simple_f(apple);
    if (ans == std::numeric_limits<int>::max())
        return -1;
    return ans;
}

int simple_f(int rest)
{
    if (rest < 0)
        return std::numeric_limits<int>::max();
    if (rest == 0)
        return 0;
    int s1 = simple_f(rest - 8);
    int s2 = simple_f(rest - 6);
    s1 += s1 == std::numeric_limits<int>::max() ? 0 : 1;
    s2 += s2 == std::numeric_limits<int>::max() ? 0 : 1;

    return std::min(s1, s2);
}

int bag1(int apple)
{
    if (apple & 1)
        return -1;

    if (apple == 6 || apple == 8)
        return 1;
    if (apple == 12 || apple == 14 || apple == 16)
        return 2;
    if (apple < 18)
        return -1;

    return ( apple - 18 ) / 8 + 3;
}

void test_apple_bags()
{
    for (int i = 1; i < 100; ++i)
    {
        auto ans = bag0(i);
        std::cout << std::format("行号：{} --- {}\n", i, ans == std::numeric_limits<int>::max() ? -1 : ans);
        std::cout << std::format("行号：{} --- {}\n", i, bag1(i));
    }
}
}

namespace whowineatinggrass {
/*
 * 草一共有n的重量，两只牛轮流吃草，A牛先吃，B牛后吃
 * 每只牛在自己的回合，吃草的重量必须是4的幂，1、4、16、4。。。
 * 谁在自己的回合正好把草吃完谁赢，根据输入的n，返回谁赢
 */
char whowin(int grassn);
char simple_f(int grassn, char cur);
char whowin_v(int grassn);

char whowin(int grassn)
{
    return simple_f(grassn, 'A');
}

char simple_f(int grassn, char cur)
{
    char enemy = cur == 'A' ? 'B' : 'A';
    if (grassn < 5)
        return ( grassn == 0 || grassn == 2 ) ? enemy : cur;

    int pick = 1;
    while (pick <= grassn)
    {
        if (simple_f(grassn - pick, enemy) == cur)
            return cur;

        pick *= 4;
    }

    return enemy;
}

char whowin_v(int grassn)
{
    if (((grassn % 5) & 1) == 0)
        return 'B';

    return 'A';
}

void test_who_win()
{
    for (int i = 0; i < 50; ++i)
    {
        std::cout << std::format("{}: {}\n", i, whowin(i));
        std::cout << std::format("{}: {}\n", i, whowin_v(i));

    }
}
}

namespace continuous_sum {
bool is_continuous_sum(int n)
{
    return n > 0 && n == (n & -n);
}

void test_continuous_sum()
{
    for (int i = 1; i < 100; ++i)
    {
        std::cout << std::format("{}: {}\n", i, is_continuous_sum(i) ? "T" : "F");
    }
}
}

namespace palindrome_string {
/*
 * 可以用r、e、d三种字符拼接字符串，如果拼出来的字符串中
 * 有且仅有1个长度>=2的回文子串，那么这个字符串定义为"好串”
 * 1 7 1/ I/ 1///
 * 返回长度为n的所有可能的字符串中，好串有多少个
 * 结果对1000000007取模，1<=n<=10^9 示例：n =1，输出0 n=2，输出3  n=3，输出18
 */
int count_better_str(int len)
{
    if (len == 1)
        return 0;
    if (len == 2)
        return 3;
    if (len == 3)
        return 18;

    return (long)(len + 1) * 6 % 1000'000'007;
}

void test_count_better_str()
{
    for (int i = 1; i < 100; ++i)
    {
        std::cout << std::format("{}: {}\n", i, count_better_str(i));
    }
}
}

namespace kill_monster {
/*
 * 现在有一个打怪类型的游戏，这个游戏是这样的，你有n个技能每一个技能会有一个伤害，
 * 同时若怪物小于等于一定的血量，则该技能可能造成双倍伤害
 * 每一个技能最多只能释放一次，已知怪物有m点血量
 * 现在想问你最少用几个技能能消灭掉他（血量小于等于0）
 * 技能的数量是n，怪物的血量是m
 * i号技能的伤害是x[i]，i号技能触发双倍伤害的血量最小值是y[i]
 * 1<=n<=10
 *  1 <= m、x[i]、y[i] <= 10^6
 * 测试链接：https：//www.nowcoder.com/practice/d88ef50f8dab4850be8cd4b95514bbbd 门
 * 请同学们务必参考如下代码中关于输入、输出的处理
 * 这是输入输出处理效率很高的写法
 * 提交以下的所有代码，并把主类名改成“Main”
 * 可以直接通过
 */
constexpr int N = 11;

int kill[N];
int blood[N];

void swap(int i, int j)
{
    std::swap(kill[i], kill[j]);
    std::swap(blood[i], blood[j]);
}

int dfs(int i, int n, int r)
{
    if (r <= 0)
        return i;
    if (i == n)
        return std::numeric_limits<int>::max();

    int ans = std::numeric_limits<int>::max();
    for (int j = i; j < n; ++j)
    {
        swap(i, j);
        ans = std::min(ans, dfs(i + 1, n, r - (r > blood[i] ? kill[i] : kill[i] * 2)));
        swap(i, j);
    }

    return ans;

}

void entry()
{
    int t, n, m;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d%d", &n, &m);
        for (int i = 0; i < n; ++i)
        {
            scanf("%d%d", &kill[i], &blood[i]);
        }
        int ans = dfs(0, n, m);
        printf("%d\n", ans == std::numeric_limits<int>::max() ? -1 : ans);
    }
}
}

namespace leetcode_906 {
class Solution {
public:
    int superpalindromesInRange(const std::string& left, const std::string& right) {
        long l = std::stol(left);
        long r = std::stol(right);
        long limit = (long)std::sqrt(r);
        long seed = 1;
        long num = 0;
        long ans = 0;
        while(num < limit) {
            num = even_enlarge(seed);
            if (num <= limit)
                if (check(num * num, l, r))
                    ++ans;
            num = odd_enlarge(seed);
            if (num <= limit)
                if (check(num * num, l, r))
                    ++ans;

            ++seed;
        }

        return ans;
    }

    static long odd_enlarge(long seed)
    {
        long num = seed;
        num /= 10;
        while (num)
        {
            seed = seed * 10 + num % 10;
            num /= 10;
        }
        return seed;
    }

    static long even_enlarge(long seed)
    {
        long num = seed;
        while (num > 0)
        {
            seed = seed * 10 + num % 10;
            num /= 10;
        }
        return seed;
    }

    static bool check(long x, long l, long r)
    {
        return x >= l && x <= r && is_palindrome(x);
    }

    static bool is_palindrome(long n)
    {
        if (n < 0)
            return false;
        long offset = 1;
        while (n / offset >= 10)
            offset *= 10;
        while (n)
        {
            if (n / offset != n % 10)
                return false;
            n = (n % offset) / 10;
            offset /= 100;
        }

        return true;
    }
};
}

namespace leetcode_9 {
class Solution {
public:
    static bool isPalindrome(int x) {
        int offset = 1;
        while (x / offset >= 10)
            offset *= 10;
        while (x)
        {
            if (x / offset != x % 10)
                return false;
            x = ( x % offset ) / 10;
            offset /= 100;
        }

        return true;
    }
};
}














int main()
{
    reverse_stack::test_reverse_stack();
    sort_stack::test_sort_stack();
    hanoi::test_hanoi();
    test_leetcode_772();

    nqueens::test_queen();
    applebags::test_apple_bags();
    whowineatinggrass::test_who_win();
    continuous_sum::test_continuous_sum();
    palindrome_string::test_count_better_str();

    long x = 3037007303L;
    long y = x * x;
    std::cout << y << std::endl;


    return 0;
}