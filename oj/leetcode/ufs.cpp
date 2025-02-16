#include "../utilities.hpp"

namespace leetcode_765 {
// 765. Couples Holding Hands
class Solution {
public:
    int minSwapsCouples(std::vector<int>& row) {
        int n = static_cast<int>(row.size());
        build(n/2);
        for (int i = 0; i < n; i += 2)
        {
            union_(row[i]/2, row[i+1]/2);
        }

        return n/2 - sets;
    }
    void build(int m)
    {
        father.resize(m);
        for (int i = 0; i < m; ++i)
        {
            father[i] = i;
        }
        sets = m;
    }
    int find(int x)
    {
        int a = x;
        while (x != father[x])
        {
            x = father[x];
        }
        while (a != father[a])
        {
            int z = a;
            a = father[a];
            father[z] = x;
        }
        return x;
    }
    void union_(int x, int y)
    {
        int fx = find(x);
        int fy = find(y);
        if (fx != fy)
        {
            father[fx] = fy;
            --sets;
        }
    }
private:
    std::vector<int> father;
    int sets{0};

};
}

namespace leetcode_839 {
// 839. Similar String Groups
class Solution {
public:
    int numSimilarGroups(std::vector<std::string>& strs) {
        int n = static_cast<int>(strs.size());
        int m = static_cast<int>(strs[0].size());
        build(n);
        for (int i = 0; i < n; ++i)
        {
            for (int j = i + 1; j < n; ++j)
            {
                if (find(i) != find(j))
                {
                    int diff = 0;
                    for (int k = 0; k < m && diff < 3; ++k)
                    {
                        if (strs[i][k] != strs[j][k])
                            ++diff;
                    }
                    if (diff == 0 || diff == 2)
                        union_(i, j);
                }
            }
        }
        return sets;
    }

    void build(int m)
    {
        father.resize(m);
        for (int i = 0; i < m; ++i)
        {
            father[i] = i;
        }
        sets = m;
    }
    int find(int x)
    {
        int a = x;
        while (x != father[x])
        {
            x = father[x];
        }
        while (a != father[a])
        {
            int z = a;
            a = father[a];
            father[z] = x;
        }
        return x;
    }
    void union_(int a, int b)
    {
        int fa = find(a);
        int fb = find(b);
        if (fa != fb)
        {
            father[fa] = fb;
            --sets;
        }
    }
private:
    std::vector<int> father;
    int sets{0};
};
}

namespace leetcode_200 {
// 200. Number of Islands
class Solution {
public:
    int numIslands(std::vector<std::vector<char>>& grid) {
        int n = static_cast<int>(grid.size());
        int m = static_cast<int>(grid[0].size());
        build(n, m, grid);
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; ++j)
            {
                if (grid[i][j] == '1')
                {
                    if (j > 0 && grid[i][j-1] == '1')
                        union_(i, j, i, j-1);
                    if (i > 0 && grid[i-1][j] == '1')
                        union_(i, j, i-1, j);
                }
            }
        }
        return sets;
    }
    void build(int n, int m, std::vector<std::vector<char>> &grid)
    {
        col = m;
        father.resize(n * m);
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; ++j)
            {
                if (grid[i][j] == '1')
                {
                    father[i*col + j] = i * col + j;
                    ++sets;
                }
            }
        }
    }
    int find(int x)
    {
        int a = x;
        while (x != father[x])
        {
            x = father[x];
        }
        while (a != father[a])
        {
            int z = a;
            a = father[a];
            father[z] = x;
        }
        return x;
    }
    void union_(int i, int j, int s, int t)
    {
        int fa = find(i * col + j);
        int fb = find(s * col + t);
        if (fa != fb)
        {
            father[fa] = fb;
            --sets;
        }
    }
private:
    std::vector<int> father;
    int sets{0};
    int col{0};
};
}

namespace leetcode_947 {
// 947. Most Stones Removed with Same Row or Column
class Solution {
public:
    int removeStones(std::vector<std::vector<int>>& stones) {
        int n = static_cast<int>(stones.size());
        build(n);
        for (int i = 0; i < n; ++i)
        {
            int row = stones[i][0];
            int col = stones[i][1];
            if (row2n[row] == -1)
            {
                row2n[row] = i;
            }
            else
            {
                union_(i, row2n[row]);
            }
            if (col2n[col] == -1)
            {
                col2n[col] = i;
            }
            else
            {
                union_(i, col2n[col]);
            }
        }
        return n - sets;
    }
    void build(int n)
    {
        for (int i = 0; i < 10005; ++i)
        {
            row2n[i] = -1;
            col2n[i] = -1;
        }
        for (int i = 0; i < n; ++i)
        {
            father[i] = i;
        }
        sets = n;
    }
    int find(int x)
    {
        int a = x;
        while (x != father[x])
        {
            x = father[x];
        }
        while (a != father[a])
        {
            int z = a;
            a = father[a];
            father[z] = x;
        }
        return x;
    }
    void union_(int a, int b)
    {
        int fa = find(a);
        int fb = find(b);
        if (fa != fb)
        {
            father[fa] = fb;
            --sets;
        }
    }
private:
    int row2n[10005]{-1};
    int col2n[10005]{-1};
    int father[1001]{0};
    int sets{0};
};
}

namespace leetcode_2092 {
// 2092. Find All People With Secret
class Solution {
public:
    std::vector<int> findAllPeople(int n, std::vector<std::vector<int>>& meetings, int firstPerson) {
        build(n, firstPerson);
        auto cmp = [](auto &m1, auto &m2) {
            return m1[2] < m2[2];
        };
        std::sort(meetings.begin(), meetings.end(), cmp);
        int m = static_cast<int>(meetings.size());
        for (int i = 0, j; i < m; )
        {
            j = i;
            while (j + 1 < m && meetings[i][2] == meetings[j+1][2])
                ++j;
            for (int k = i; k <= j; ++k)
            {
                union_(meetings[k][0], meetings[k][1]);
            }
            for (int k = i; k <= j; ++k)
            {
                int a = meetings[k][0];
                int b = meetings[k][1];
                if (!secret[find(a)])
                    father[a] = a;
                if (!secret[find(b)])
                    father[b] = b;
            }
            i = j + 1;
        }
        std::vector<int> ans;
        for (int i = 0; i < n; ++i)
        {
            if (secret[find(i)])
                ans.push_back(i);
        }
        return ans;
    }
    void build(int n, int first)
    {
        father.resize(n);
        secret.resize(n);
        for (int i = 0; i < n; ++i)
        {
            father[i] = i;
            secret[i] = false;
        }
        father[first] = 0;
        secret[0] = true;
    }
    int find(int x)
    {
        int a = x;
        while (x != father[x])
        {
            x = father[x];
        }
        while (a != father[a])
        {
            int z = a;
            a = father[a];
            father[z] = x;
        }
        return x;
    }
    void union_(int a, int b)
    {
        int fa = find(a);
        int fb = find(b);
        if (fa != fb)
        {
            father[fa] = fb;
            secret[fb] = (secret[fb] | secret[fa]);
        }
    }
private:
    std::vector<int> father;
    std::vector<bool> secret;
};

void test()
{
    std::vector<std::vector<int>> inputs{{1, 2, 5}, {2, 3, 8}, {1, 5, 10}};
    Solution so;
    auto ans = so.findAllPeople(6, inputs, 1);
    for ( auto i: ans)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}
}

namespace leetcode_2421 {
// 2421. Number of Good Paths
class Solution {
public:
    int numberOfGoodPaths(std::vector<int>& vals, std::vector<std::vector<int>>& edges) {
        int n = static_cast<int>(vals.size());
        build(n);
        int ans = n;
        auto cmp = [&vals](auto &e1, auto &e2) {
            return std::max(vals[e1[0]], vals[e1[1]]) < std::max(vals[e2[0]], vals[e2[1]]);
        };
        std::sort(edges.begin(), edges.end(), cmp);
        for (auto &edge : edges)
        {
            ans += union_(edge[0], edge[1], vals);
        }
        return ans;
    }

    void build(int n)
    {
        father.resize(n);
        maxcnts.resize(n);
        for (int i = 0; i < n; ++i)
        {
            father[i] = i;
            maxcnts[i] = 1;
        }
    }
    int find(int x)
    {
        int a = x;
        while (x != father[x])
        {
            x = father[x];
        }
        while (a != father[a])
        {
            int z = a;
            a = father[a];
            father[z] = x;
        }
        return x;
    }
    int union_(int x, int y, std::vector<int> &val)
    {
        int fx = find(x);
        int fy = find(y);
        int path = 0;
        if (val[fx] > val[fy])
            father[fy] = fx;
        else if (val[fy] > val[fx])
            father[fx] = fy;
        else
        {
            path = maxcnts[fx] * maxcnts[fy];
            father[fy] = fx;
            maxcnts[fx] += maxcnts[fy];
        }
        return path;
    }

private:
    std::vector<int> father;
    std::vector<int> maxcnts;
};
}

namespace leetcode_200_v {
// 200. Number of Islands
// 洪水填充 grid(n * m)
// O(n * m)
class Solution {
public:
    int numIslands(std::vector<std::vector<char>>& grid) {
        int islands = 0;
        for (int i = 0; i < grid.size(); ++i)
        {
            for (int j = 0; j < grid[0].size(); ++j)
            {
                if (grid[i][j] == '1')
                {
                    ++islands;
                    dfs(i, j, grid);
                }
            }
        }
        return islands;
    }
    void dfs(int i, int j, std::vector<std::vector<char>> &grid)
    {
        if (i < 0 || i == grid.size() || j < 0 || j == grid[0].size() || grid[i][j] != '1')
            return ;
        grid[i][j] = '2';
        dfs(i - 1, j, grid);
        dfs(i + 1, j, grid);
        dfs(i, j - 1, grid);
        dfs(i, j + 1, grid);
    }
};
}

namespace leetcode_130 {
// 130. Surrounded Regions
class Solution {
public:
    void solve(std::vector<std::vector<char>>& board) {
        int n = static_cast<int>(board.size());
        int m = static_cast<int>(board[0].size());
        for (int j = 0; j < m; ++j)
        {
            if (board[0][j] == 'O')
                dfs(board, n, m, 0, j);
            if (board[n-1][j] == 'O')
                dfs(board, n, m, n - 1, j);
        }
        for (int i = 1; i < n - 1; ++i)
        {
            if (board[i][0] == 'O')
                dfs(board, n, m, i, 0);
            if (board[i][m-1] == 'O')
                dfs(board, n, m, i, m - 1);
        }
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; ++j)
            {
                if (board[i][j] == 'O')
                    board[i][j] = 'X';
                if (board[i][j] == 'F')
                    board[i][j] = 'O';
            }
        }
    }
    void dfs(std::vector<std::vector<char>> &board, int n, int m, int i, int j)
    {
        if (i < 0 || i == n || j < 0 || j == m || board[i][j] != 'O')
            return ;
        board[i][j] = 'F';
        dfs(board, n, m, i - 1, j);
        dfs(board, n, m, i + 1, j);
        dfs(board, n, m, i, j - 1);
        dfs(board, n, m, i, j + 1);
    }
};
}

namespace leetcode_827 {
// 827. Making A Large Island
class Solution {
public:
    int largestIsland(std::vector<std::vector<int>>& grid) {
        int n  = static_cast<int>(grid.size());
        int m  = static_cast<int>(grid[0].size());
        int id = 2;
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; ++j)
            {
                if (grid[i][j] == 1)
                    dfs(grid, n, m, i, j, id++);
            }
        }
        std::vector<int> sizes(id);
        int ans = 0;
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; ++j)
            {
                if (grid[i][j] > 1)
                    ans = std::max(ans, ++sizes[grid[i][j]]);
            }
        }
        // 讨论所以的0， 变1，能带来的最大岛的数量
        std::vector<bool> visited(id);
        int up, down, left, right, merge;
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; ++j)
            {
                if (grid[i][j] == 0)
                {
                    up = i > 0 ? grid[i-1][j] : 0;
                    down = i + 1 < n ? grid[i+1][j] : 0;
                    left = j > 0 ? grid[i][j-1] : 0;
                    right = j + 1 < m ? grid[i][j+1] : 0;
                    visited[up] = true;
                    merge = 1 + sizes[up];
                    if (!visited[down])
                    {
                        merge += sizes[down];
                        visited[down] = true;
                    }
                    if (!visited[left])
                    {
                        merge += sizes[left];
                        visited[left] = true;
                    }
                    if (!visited[right])
                    {
                        merge += sizes[right];
                        visited[right] = true;
                    }
                    ans = std::max(ans, merge);
                    visited[up] = false;
                    visited[down] = false;
                    visited[left] = false;
                    visited[right] = false;
                }
            }
        }
        return ans;
    }
    void dfs(std::vector<std::vector<int>> &grid, int n, int m, int i, int j, int id)
    {
        if (i < 0 || i == n || j < 0 || j == m || grid[i][j] != 1)
            return ;
        grid[i][j] = id;
        dfs(grid, n, m, i - 1, j, id);
        dfs(grid, n, m, i + 1, j, id);
        dfs(grid, n, m, i, j - 1, id);
        dfs(grid, n, m, i, j + 1, id);
    }
};
}

namespace leetcode_803 {
// 803. Bricks Falling When Hit
class Solution {
public:
    std::vector<int> hitBricks(std::vector<std::vector<int>>& grid, std::vector<std::vector<int>>& hits) {
        int n = static_cast<int>(grid.size());
        int m = static_cast<int>(grid[0].size());
        std::vector<int> ans(hits.size());
        if (n == 1)
            return ans;
        // 炮弹位置减1
        for (auto &h : hits)
        {
            --grid[h[0]][h[1]];
        }
        // 天花板洪水填充
        for (int i = 0; i < m; ++i)
        {
            dfs(grid, n, m, 0, i);
        }
        // 时光倒流处理
        for (int i = hits.size() - 1, row, col; i >= 0; --i)
        {
            row = hits[i][0];
            col = hits[i][1];
            ++grid[row][col];
            if (worth(grid, n, m, row, col))
            {
                ans[i] = dfs(grid, n, m, row, col) - 1;
            }
        }
        return ans;
    }
    static bool worth(std::vector<std::vector<int>> &grid, int n, int m, int i, int j)
    {
        return (i == 0
                       || (i > 0 && grid[i-1][j] == 2)
                       || (i < n - 1 && grid[i+1][j] == 2)
                       || (j > 0 && grid[i][j-1] == 2)
                       || (j < m - 1 && grid[i][j+1] == 2))
               && grid[i][j] == 1;
    }
    // 从（i，j）格子出发，遇到1就感染成2
    // 统计新增了几个2！
    int dfs(std::vector<std::vector<int>> &grid, int n, int m, int i, int j)
    {
        if (i < 0 || i == n || j < 0 || j == m || grid[i][j] != 1)
            return 0;
        grid[i][j] = 2;
        return 1 + dfs(grid, n, m, i - 1, j)
                 + dfs(grid, n, m, i + 1, j)
                 + dfs(grid, n, m, i, j - 1)
                 + dfs(grid, n, m, i, j + 1);
    }
};
}



int main()
{
    leetcode_2092::test();
    return 0;
}