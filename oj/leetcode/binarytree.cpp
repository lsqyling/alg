#include "../utilities.hpp"

// Definition for a binary tree node.
 struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    explicit TreeNode(int x = 0) : val(x), left(nullptr), right(nullptr) {}
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

namespace leetcode_102 {
//102. Binary Tree Level Order Traversal
class Solution {
public:
    std::vector<std::vector<int>> levelOrder(TreeNode* root) {
        if (root == nullptr)
            return {};

        l = r = 0;
        queue[r++] = root;
        std::vector<std::vector<int>> ans;
        while (l < r)
        {
            int size = r - l;
            std::vector<int> layer;
            for (int i = 0; i < size; ++i)
            {
                auto node = queue[l++];
                layer.push_back(node->val);
                if (node->left)
                    queue[r++] = node->left;
                if (node->right)
                    queue[r++] = node->right;
            }
            ans.push_back(layer);
        }
        return ans;
    }

private:
    TreeNode *queue[2001];
    int l, r;
};
}

namespace leetcode_103 {
//103. Binary Tree Zigzag Level Order Traversal
class Solution {
public:
    std::vector<std::vector<int>> zigzagLevelOrder(TreeNode* root)
    {
        if (root == nullptr)
            return {};

        l = r = 0;
        queue[r++] = root;
        std::vector<std::vector<int>> ans;
        bool left = true;
        while (l < r)
        {
            std::vector<int> layer;
            int size = r - l;
            if (left)
            {
                for (int i = l; i < r; ++i)
                    layer.push_back(queue[i]->val);
            }
            else
            {
                for (int i = r-1; i >= l; --i)
                    layer.push_back(queue[i]->val);
            }
            left = !left;
            for (int i = 0; i < size; ++i)
            {
                auto node = queue[l++];
                if (node->left)
                    queue[r++] = node->left;
                if (node->right)
                    queue[r++] = node->right;
            }
            ans.push_back(layer);
        }

        return ans;
    }


private:
    TreeNode *queue[2001];
    int l, r;
};
}

namespace leetcode_662 {
//662. Maximum Width of Binary Tree
class Solution {
public:
    int widthOfBinaryTree(TreeNode* root) {
        int ans = 1;
        l = r = 0;
        queue[r] = root;
        nums[r++] = 1;
        while (l < r)
        {
            int size = r - l;
            ans = std::max(ans, nums[r-1] - nums[l] + 1);

            for (int i = 0; i < size; ++i)
            {
                auto node = queue[l];
                auto id = nums[l++];
                if (node->left)
                {
                    queue[r] = node->left;
                    nums[r++] = 2 * id;
                }
                if (node->right)
                {
                    queue[r] = node->right;
                    nums[r++] = 2 * id + 1;
                }
            }
        }
        return ans;
    }

private:
    TreeNode *queue[3001];
    int nums[3001];
    int l, r;
};
}

namespace leetcode_104 {
//104. Maximum Depth of Binary Tree
class Solution {
public:
    int maxDepth(TreeNode* root) {
        if (root == nullptr)
            return 0;
        return std::max(maxDepth(root->left), maxDepth(root->right)) + 1;
    }
};
}

namespace leetcode_111 {
//111. Minimum Depth of Binary Tree
class Solution {
public:
    int minDepth(TreeNode* root) {
        if (root == nullptr)
            return 0;
        if (root->left == nullptr && root->right == nullptr)
            return 1;

        int lmin = std::numeric_limits<int>::max();
        int rmin = std::numeric_limits<int>::max();

        if (root->left)
            lmin = minDepth(root->left);
        if (root->right)
            rmin = minDepth(root->right);

        return std::min(lmin, rmin) + 1;
    }
};
}

namespace leetcode_297 {
//297. Serialize and Deserialize Binary Tree
class Codec {
public:

    // Encodes a tree to a single string.
    std::string serialize(TreeNode* root) {
        std::string ans;
        serialize_s(root, ans);
        return ans;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(std::string data) {
        auto vals = split(data, ',');
        int i = 0;
        return deserialize_s(vals, i);
    }



//private:
    void serialize_s(TreeNode *root, std::string &s)
    {
        if (root == nullptr)
        {
            s += "#,";
            return ;
        }
        s += std::to_string(root->val) + ",";
        serialize_s(root->left, s);
        serialize_s(root->right, s);
    }


    TreeNode *deserialize_s(std::vector<std::string> &vals, int &i)
    {
        auto &cur = vals[i++];
        if (cur == "#")
            return nullptr;

        auto root = new TreeNode(std::stoi(cur));
        root->left = deserialize_s(vals, i);
        root->right = deserialize_s(vals, i);

        return root;
    }



    static std::vector<std::string> split(std::string_view str, char delimiter)
    {
        std::vector<std::string> ans;
        size_t b = 0;
        size_t e = str.find(delimiter);

        while (e != std::string_view::npos)
        {
            if (e != b)
                ans.emplace_back(str.substr(b, e-b));
            b = e + 1;
            e = str.find(delimiter, b);
        }
        if (b != str.size())
            ans.emplace_back(str.substr(b, e));
        return ans;
    }

};
}

namespace leetcode_449 {
//449. Serialize and Deserialize BST
class Codec {
public:

    // Encodes a tree to a single string.
    std::string serialize(TreeNode* root) {
        std::string ans;
        if (root == nullptr)
            return ans;

        int i = 0;
        l = r = 0;
        queue[r++] = root;
        ans += std::to_string(root->val) + ",";
        while (l < r)
        {
            auto size = r - l;
            for (int j = 0; j < size; ++j)
            {
                auto node = queue[l++];
                if (node->left)
                {
                    ans += std::to_string(node->left->val) + ",";
                    queue[r++] = node->left;
                }
                else
                    ans += "#,";
                if (node->right)
                {
                    ans += std::to_string(node->right->val) + ",";
                    queue[r++] = node->right;
                }
                else
                    ans += "#,";
            }
        }
        return ans;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(std::string data) {
        auto vals = split(data, ',');
        if (vals.empty())
            return nullptr;

        int i = 0;
        l = r = 0;
        auto root = new TreeNode(std::stoi(vals[i++]));
        queue[r++] = root;

        while (l < r)
        {
            auto size = r - l;
            for (int j = 0; j < size; ++j)
            {
                auto node = queue[l++];
                node->left = generate_node(vals[i++]);
                if (node->left)
                    queue[r++] = node->left;
                node->right = generate_node(vals[i++]);
                if (node->right)
                    queue[r++] = node->right;
            }
        }
        return root;
    }

private:
    static TreeNode *generate_node(std::string str)
    {
        return str == "#" ? nullptr : new TreeNode(std::stoi(str));
    }

    static std::vector<std::string> split(std::string_view str, char delimiter)
    {
        std::vector<std::string> ans;
        size_t b = 0;
        size_t e = str.find(delimiter);
        while (e != std::string_view::npos)
        {
            if (e != b)
                ans.emplace_back(str.substr(b, e-b));
            b = e + 1;
            e = str.find(delimiter, b);
        }
        if (b != str.size())
            ans.emplace_back(str.substr(b, e));
        return ans;
    }

    TreeNode *queue[10001];
    int l, r;
};
}

namespace leetcode_105 {
//105. Construct Binary Tree from Preorder and Inorder Traversal
class Solution {
public:
    TreeNode* buildTree(std::vector<int>& preorder, std::vector<int>& inorder) {
        pre = &preorder;
        in = &inorder;
        for (int i = 0; i < inorder.size(); ++i)
            in2i[inorder[i]] = i;
        return generate_tree(0, int(preorder.size())-1, 0, int(inorder.size())-1);
    }


    TreeNode *generate_tree(int preL, int preR, int inL, int inR)
    {
        if (inL > inR)
            return nullptr;

        auto root = new TreeNode((*pre)[preL]);
        int k = in2i[(*pre)[preL]];
        int numleft = in2i[(*pre)[preL]] - inL;

        root->left = generate_tree(preL+1, preL+numleft, inL, k-1);
        root->right = generate_tree(preL+numleft+1, preR, k+1, inR);

        return root;
    }


private:
    std::unordered_map<int, int> in2i;
    std::vector<int> *pre;
    std::vector<int> *in;
};
}

namespace leetcode_958 {
//958. Check Completeness of a Binary Tree
class Solution {
public:
    bool isCompleteTree(TreeNode* root) {
        if (root == nullptr)
            return true;

        l = r = 0;
        queue[r++] = root;
        bool leaf = false;
        while (l < r)
        {
            auto size = r - l;
            for (int i = 0; i < size; ++i)
            {
                auto node = queue[l++];
                if (node->left == nullptr && node->right)
                    return false;
                if (leaf && (node->left || node->right))
                    return false;

                if (node->left)
                    queue[r++] = node->left;
                if (node->right)
                    queue[r++] = node->right;

                if (node->left == nullptr || node->right == nullptr)
                    leaf = true;
            }
        }
        return true;
    }


private:
    TreeNode *queue[1001];
    int l, r;
};
}

namespace leetcode_222 {
//222. Count Complete Tree Nodes
class Solution {
public:
    static int countNodes(TreeNode* root) {
        if (root == nullptr)
            return 0;

        int level = 0;
        auto node = root;
        while (node->left)
        {
            node = node->left;
            ++level;
        }

        int low = 1 << level;
        int high = (1 << (level+1)) - 1;
        while (low < high)
        {
            int mid = (high - low + 1) / 2 + low;
            if (exists(root, level, mid))
                low = mid;
            else
                high = mid - 1;
        }
        return low;
    }

    static bool exists(TreeNode *root, int level, int k)
    {
        int bits = 1 << (level-1);
        auto node = root;
        while (node && bits)
        {
            if ((k & bits) == 0)
                node = node->left;
            else
                node = node->right;
            bits >>= 1;
        }
        return node != nullptr;
    }
};
}

namespace leetcode_236 {
//236. Lowest Common Ancestor of a Binary Tree
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (root == nullptr || root == p || root == q)
            return root;

        auto l = lowestCommonAncestor(root->left, p, q);
        auto r = lowestCommonAncestor(root->right, p, q);
        if (l && r)
            return root;
        if (l == nullptr && r == nullptr)
            return nullptr;
        return l ? l : r;
    }
};
}

namespace leetcode_235 {
//235. Lowest Common Ancestor of a Binary Search Tree
class Solution {
public:
    static TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        auto node = root;
        while (true)
        {
            if (p->val < node->val && q->val < node->val)
                node = node->left;
            else if (p->val > node->val && q->val > node->val)
                node = node->right;
            else
                break;
        }
        return node;
    }
};
}

namespace leetcode_113 {
//113. Path Sum II
class Solution {
public:
    std::vector<std::vector<int>> pathSum(TreeNode* root, int targetSum) {
        if (root == nullptr)
            return {};

        dfs(root, 0, targetSum);
        return ans;
    }

    void dfs(TreeNode *node, int sum, int targetsum)
    {
        if (node->left == nullptr && node->right == nullptr)
        {
            if (sum + node->val == targetsum)
            {
                path.push_back(node->val);
                ans.push_back(path);
                path.pop_back();
                return ;
            }
        }
        else
        {
            path.push_back(node->val);
            if (node->left)
                dfs(node->left, sum + node->val, targetsum);
            if (node->right)
                dfs(node->right, sum + node->val, targetsum);

            path.pop_back();
        }
    }


private:
    std::vector<std::vector<int>> ans;
    std::vector<int> path;

};
}

namespace leetcode_110 {
//110. Balanced Binary Tree
class Solution {
public:
    bool isBalanced(TreeNode* root) {
        if (root == nullptr)
            return true;
        return std::abs(height(root->left) - height(root->right)) <= 1
        && isBalanced(root->left)
        && isBalanced(root->right);
    }

    int height(TreeNode *root)
    {
        if (root == nullptr)
            return 0;
        return std::max(height(root->left), height(root->right)) + 1;
    }
};
}

namespace leetcode_98 {
//98. Validate Binary Search Tree
class Solution {
public:
    bool isValidBST(TreeNode* root) {
        return valid(root, std::numeric_limits<int64_t>::min(), std::numeric_limits<int64_t>::max());
    }

    bool valid(TreeNode *root, int64_t lower, int64_t upper)
    {
        if (root == nullptr)
            return true;
        if (root->val <= lower || root->val >= upper)
            return false;

        return valid(root->left, lower, root->val) && valid(root->right, root->val, upper);
    }
};
}

namespace leetcode_669 {
//669. Trim a Binary Search Tree
class Solution {
public:
    TreeNode* trimBST(TreeNode* root, int low, int high) {
        if (root == nullptr)
            return nullptr;

        if (root->val < low)
            return trimBST(root->right, low, high);
        if (root->val > high)
            return trimBST(root->left, low, high);

        root->left = trimBST(root->left, low, high);
        root->right = trimBST(root->right, low, high);

        return root;
    }
};
}

namespace leetcode_337 {
//337. House Robber III
class Solution {
public:
    int rob(TreeNode* root) {
        auto rootstatus = dfs(root);
        return std::max(rootstatus.selected, rootstatus.notselected);
    }


private:
    struct subtree_status
    {
        int selected;
        int notselected;
    };

    subtree_status dfs(TreeNode *root)
    {
        if (root == nullptr)
            return {0, 0};

        auto l = dfs(root->left);
        auto r = dfs(root->right);

        int selected = root->val + l.notselected + r.notselected;
        int notselected = std::max(l.notselected, l.selected) + std::max(r.notselected, r.selected);

        return {selected, notselected};
    }
};
}











































int main()
{
    std::string str{"#,#,#,abc,e,,ef,e,#,"};
    auto ans = leetcode_297::Codec::split(str, ',');
    for (auto &s : ans)
        std::cout << s << std::endl;
    std::cout << ans.size() << std::endl;



    return 0;
}