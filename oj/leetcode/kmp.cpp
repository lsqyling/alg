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

namespace leetcode_572 {
//572. 另一棵树的子树
/**
 * Definition for a binary tree node.
 */
 struct TreeNode {
     int val{0};
     TreeNode *left{nullptr};
     TreeNode *right{nullptr};
 };
class Solution {
public:
    bool isSubtree(TreeNode* root, TreeNode* subRoot) {
        if (root && subRoot)
            return same(root, subRoot) || isSubtree(root->left, subRoot) || isSubtree(root->right, subRoot);
        return subRoot == nullptr;
    }
    bool same(TreeNode *t1, TreeNode *t2)
    {
        if (t1 == nullptr && t2 == nullptr)
            return true;
        if (t1 && t2)
        {
            return t1->val == t2->val && same(t1->left, t2->left) && same(t1->right, t2->right);
        }
        return false;
    }
};
}














int main()
{
    std::list<int> li;
    std::vector<int> vec;
    return 0;
}