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
    int minimumTime(int n, std::vector<std::vector<int>>& relations, std::vector<int>& time) {

    }
};
}























int main()
{
    return 0;
}