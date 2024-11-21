#include "utilities.hpp"

// Definition for a binary tree node.
 struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    explicit TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

namespace leetcode_144 {
//144. Binary Tree Preorder Traversal
class Solution
{
public:
    static std::vector<int> preorderTraversal(TreeNode *root)
    {
        if (root == nullptr)
            return {};
        std::vector<int> result;
        std::stack<TreeNode *> s;
        s.push(root);
        while (!s.empty())
        {
            auto node = s.top();
            result.push_back(node->val);
            s.pop();
            if (node->right)
                s.push(node->right);
            if (node->left)
                s.push(node->left);
        }
        return result;
    }
};
}

namespace leetcode_94 {
//144. Binary Tree Inorder Traversal
class Solution
{
public:
    static std::vector<int> inorderTraversal(TreeNode *root)
    {
        if (root == nullptr)
            return {};
        std::vector<int> ans;
        std::stack<TreeNode *> st;
        auto node = root;
        while (!st.empty() || node)
        {
            if (node)
            {
                st.push(node);
                node = node->left;
            }
            else
            {
                node = st.top();
                ans.push_back(node->val);
                st.pop();
                node = node->right;
            }
        }
        return ans;
    }
};
}

namespace leetcode_145 {
//145. Binary Tree Postorder Traversal
class Solution
{
public:
    static std::vector<int> postorderTraversal(TreeNode *root)
    {
        if (root == nullptr)
            return {};
        std::stack<TreeNode *> st;
        std::vector<int> ans;
        auto node = root;
        TreeNode *r{nullptr};
        while (!st.empty() || node)
        {
            if (node)
            {
                st.push(node);
                node = node->left;
            }
            else
            {
                node = st.top();
                if (node->right && node->right != r)
                {
                    node = node->right;
                }
                else
                {
                    st.pop();
                    ans.push_back(node->val);
                    r = node;
                    node = nullptr;
                }
            }
        }
        return ans;
    }
};

}


int main()
{


    return 0;
}