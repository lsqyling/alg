#include "../utilities.hpp"

namespace leetcode_210 {
// 210. Course Schedule II
class Solution {
public:
    std::vector<int> findOrder(int numCourses, std::vector<std::vector<int>>& prerequisites) {
        // 建图
        std::vector<std::vector<int>> graph(numCourses);
        // 入度表
        std::vector<int> indegree(numCourses);
        for (auto &e : prerequisites)
        {
            graph[e[1]].push_back(e[0]);
            ++indegree[e[0]];
        }
        std::vector<int> queue(numCourses);
        int l = 0, r = 0;
        for (int i = 0; i < numCourses; ++i)
        {
            if (indegree[i] == 0)
                queue[r++] = i;
        }
        int cnt = 0;
        while (l < r)
        {
            int cur = queue[l++];
            ++cnt;
            for (int next : graph[cur])
            {
                if ( --indegree[next] == 0 )
                    queue[r++] = next;
            }
        }
        return cnt == numCourses ? queue : std::vector<int>{};
    }
};
}

namespace leetcode_936 {
// 936. Stamping The Sequence
class Solution {
public:
    static std::vector<int> movesToStamp(std::string stamp, std::string target) {
        int m = static_cast<int>(stamp.size());
        int n = static_cast<int>(target.size());
        // 入度表
        std::vector<int> indegree(n - m + 1, m);
        // 建图
        std::vector<std::vector<int>> graph(n);
        std::vector<int> queue(n - m + 1);
        int l = 0, r = 0;
        for (int i = 0; i <= n - m; ++i)
        {
            // i 开头... （m个）
            // i+0 i+1 ... i+m-1
            for (int j = 0; j < m; ++j)
            {
                if (stamp[j] == target[i+j])
                {
                    if (--indegree[i] == 0)
                        queue[r++] = i;
                }
                else
                {
                    // i+j 错误位置 -> i开头
                    graph[i+j].push_back(i);
                }
            }
        }
        // 同一个位置取消错误不要重复统计
        std::vector<bool> visited(n);
        std::vector<int> path(n + m - 1);
        int size = 0;
        while (l < r)
        {
            int cur = queue[l++];
            path[size++] = cur;
            for (int i = 0; i < m; ++i)
            {
                // cur : 开头位置
                // cur+0 cur+1 ... cur+m-1
                if (!visited[cur+i])
                {
                    visited[cur+i] = true;
                    for (auto next : graph[cur+i])
                    {
                        if (--indegree[next] == 0)
                            queue[r++] = next;
                    }
                }
            }
        }
        if (size != n - m + 1)
            return {};
        // path reverse
        std::reverse(path.begin(), path.end());
        return path;
    }
};
}

namespace leetcode_851 {
// 851. Loud and Rich
class Solution {
public:
    static std::vector<int> loudAndRich(std::vector<std::vector<int>>& richer, std::vector<int>& quiet) {
        int n = static_cast<int>(quiet.size());
        // 建图
        std::vector<std::vector<int>> graph(n);
        // 入度表
        std::vector<int> indegree(n);
        for (auto &e : richer)
        {
            graph[e[0]].push_back(e[1]);
            ++indegree[e[1]];
        }
        std::vector<int> queue(n);
        int l = 0, r = 0;
        for (int i = 0; i < n; ++i)
        {
            if (indegree[i] == 0)
                queue[r++] = i;
        }
        std::vector<int> ans(n);
        for (int i = 0; i < n; ++i)
        {
            ans[i] = i;
        }
        while (l < r)
        {
            int cur = queue[l++];
            for (auto next : graph[cur])
            {
                if (quiet[ans[cur]] < quiet[ans[next]])
                    ans[next] = ans[cur];
                if (--indegree[next] == 0)
                    queue[r++] = next;
            }
        }
        return ans;
    }
};
}

namespace leetcode_2050 {
// 2050. Parallel Courses III
class Solution {
public:
    static int minimumTime(int n, std::vector<std::vector<int>>& relations, std::vector<int>& time) {
        // 建表
        std::vector<std::vector<int>> graph(n + 1);
        // 入读表
        std::vector<int> degree(n + 1);
        for (auto &e : relations)
        {
            graph[e[0]].push_back(e[1]);
            ++degree[e[1]];
        }
        std::vector<int> queue(n);
        int l = 0, r = 0;
        for (int i = 1; i <= n; ++i)
        {
            if (degree[i] == 0)
                queue[r++] = i;
        }
        std::vector<int> cost(n + 1);
        int ans = 0;
        while (l < r)
        {
            int cur = queue[l++];
            cost[cur] += time[cur-1];
            ans = std::max(ans, cost[cur]);
            for (int next: graph[cur])
            {
                cost[next] = std::max(cost[next], cost[cur]);
                if (--degree[next] == 0)
                    queue[r++] = next;
            }
        }

        return ans;
    }
};
}

namespace leetcode_2127 {
// 2127. Maximum Employees to Be Invited to a Meeting
class Solution {
public:
    static int maximumInvitations(std::vector<int>& favorite) {
        // 图 favorite[a] = b : a -> b
        int n = static_cast<int>(favorite.size());
        std::vector<int> indegree(n);
        for (int i = 0; i < n; ++i)
        {
            ++indegree[favorite[i]];
        }
        std::vector<int> queue(n);
        int l = 0, r = 0;
        for (int i = 0; i < n; ++i)
        {
            if (indegree[i] == 0)
                queue[r++] = i;
        }
        // deep[i] : 不包括i在内，i之前的最长链的长度
        std::vector<int> deep(n);
        while (l < r)
        {
            int cur = queue[l++];
            int next = favorite[cur];
            deep[next] = std::max(deep[next], deep[cur] + 1);
            if (--indegree[next] == 0)
                queue[r++] = next;
        }
        // 目前图中的点，不在环上的点，都删除了, indegree[i] ==0
        // 可能性1：所有小环（中心个数==2），算上中心点+延伸点，总个数
        int sum_small_rings = 0;
        // 可能性2：所有大环（中心个数>2），只算中心点，最大环的中心点个数
        int big_rings = 0;
        for (int i = 0; i < n; ++i)
        {
            // 只关心环
            if (indegree[i] > 0)
            {
                int ringsize = 1;
                indegree[i] = 0;
                for (int j = favorite[i]; i != j; j = favorite[j])
                {
                    ringsize++;
                    indegree[j] = 0;
                }
                if (ringsize == 2)
                    sum_small_rings += 2 + deep[i] + deep[favorite[i]];
                else
                    big_rings = std::max(big_rings, ringsize);
            }
        }

        return std::max(sum_small_rings, big_rings);
    }
};
}

namespace leetcode_1162 {
// 1162. As Far from Land as Possible
class Solution {
public:
    static int maxDistance(std::vector<std::vector<int>>& grid) {
        int n = static_cast<int>(grid.size());
        int m = static_cast<int>(grid[0].size());
        // 标记访问表
        std::vector<std::vector<bool>> visited(n, std::vector<bool>(m, false));
        // bfs 队列
        std::vector<cell> queue(n * m);
        int l = 0, r = 0;
        int seas = 0;
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; ++j)
            {
                if (grid[i][j] == 1)
                {
                    visited[i][j] = true;
                    queue[r++] = {i, j};
                }
                else
                {
                    ++seas;
                }
            }
        }
        if (seas == 0 || seas == n * m)
            return -1;
        int level = 0;
        while (l < r)
        {
            ++level;
            int size = r - l;
            // 整层处理
            for (int k = 0; k < size; ++k)
            {
                auto x_ = queue[l].x;
                auto y_ = queue[l].y;
                ++l;
                for (int i = 0; i < 4; ++i)
                {
                    auto xx = x_ + X[i];
                    auto yy = y_ + Y[i];
                    if (0 <= xx && xx < n && 0 <= yy && yy < m && !visited[xx][yy])
                    {
                        visited[xx][yy] = true;
                        queue[r++] = {xx, yy};
                    }
                }
            }
        }

        return level - 1;
    }
private:
    // constexpr c++17 具有内联属性
    static constexpr int X[4]{1, -1, 0, 0};
    static constexpr int Y[4]{0, 0, -1, 1};

    struct cell
    {
        int x, y;
    };
};
}

namespace leetcode_691 {
// 691. Stickers to Spell Word
class Solution {
public:
    int minStickers(std::vector<std::string>& stickers, std::string target) {
        std::vector<std::vector<std::string>> graph(26);
        for (auto &str : stickers)
        {
            std::sort(str.begin(), str.end());
            for (int i = 0; i < str.size(); ++i)
            {
                if (i == 0 || str[i] != str[i-1])
                    graph[str[i]-'a'].emplace_back(str);
            }
        }
        std::sort(target.begin(), target.end());
        visited.insert(target);
        int l = 0, r = 0;
        queue[r++] = target;
        int level = 1;
        while (l < r)
        {
            auto size = r - l;
            for (int k = 0; k < size; ++k)
            {
                auto cur = queue[l++];
                for (auto &s : graph[cur[0]-'a'])
                {
                    auto next = cutoff(cur, s);
                    if (next.empty())
                        return level;
                    else if (visited.find(next) == visited.end())
                    {
                        visited.insert(next);
                        queue[r++] = next;
                    }
                }
            }
            ++level;
        }

        return -1;
    }
    static std::string cutoff(const std::string &src, const std::string &str)
    {
        std::string ans;
        for (int i = 0, j = 0; i < src.size();)
        {
            if (j == str.size())
                ans += src[i++];
            else
            {
                if (src[i] < str[j])
                    ans += src[i++];
                else if (src[i] > str[j])
                    j++;
                else
                {
                    i++;
                    j++;
                }
            }
        }
        return ans;
    }
private:
    static constexpr int N = 500;
    std::vector<std::string> queue{N};
    std::unordered_set<std::string> visited;
};
}

















int main()
{
    return 0;
}