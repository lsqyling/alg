#include "../utilities.hpp"

namespace kmp_t {
std::vector<int> get_next_array(std::string_view s2);
int find_kmp(std::string_view s1, std::string_view s2)
{
    size_t n = s1.size();
    size_t m = s2.size();
    std::vector<int> next = get_next_array(s2);
    int i = 0;
    int j = 0;
    while (i < n && j < m)
    {
        if (s1[i] == s2[j])
        {
            ++i;
            ++j;
        }
        else if (j == 0)
        {
            ++i;
        }
        else
        {
            j = next[j];
        }
    }
    return j == m ? i - j : -1;
}
std::vector<int> get_next_array(std::string_view s2)
{
    size_t m  = s2.size();
    if (m == 1)
        return {-1};

    std::vector<int> next(m);
    next[0] = -1;
    next[1] = 0;
    int i = 2;
    int j = 0;
    while (i < m)
    {
        if (s2[i-1] == s2[j])
            next[i++] = ++j;
        else if (j > 0)
            j = next[j];
        else
            next[i++] = 0;
    }
    return next;
}
}

namespace leetcoce_28 {
// 28. 找出字符串中第一个匹配项的下标
class Solution {
public:
    static std::vector<int> get_next_array(std::string_view s2)
    {
        size_t m  = s2.size();
        if (m == 1)
            return {-1};

        std::vector<int> next(m);
        next[0] = -1;
        next[1] = 0;
        int i = 2;
        int j = 0;
        while (i < m)
        {
            if (s2[i-1] == s2[j])
                next[i++] = ++j;
            else if (j > 0)
                j = next[j];
            else
                next[i++] = 0;
        }
        return next;
    }
    static int strStr(const std::string &s1, const std::string &s2) {
        size_t n = s1.size();
        size_t m = s2.size();
        std::vector<int> next = get_next_array(s2);
        int i = 0;
        int j = 0;
        while (i < n && j < m)
        {
            if (s1[i] == s2[j])
            {
                ++i;
                ++j;
            }
            else if (j == 0)
            {
                ++i;
            }
            else
            {
                j = next[j];
            }
        }
        return j == m ? i - j : -1;

    }
};
}
















int main()
{
    return 0;
}