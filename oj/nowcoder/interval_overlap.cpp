//
// Created by 10580.
//
#include "../utilities.hpp"

namespace lso {
/*
 * 链接：https://www.nowcoder.com/questionTerminal/1ae8d0b6bb4e4bcdbf64ec491f63fc37?
 * 来源：牛客网
 *
 * 每一个线段都有start和end两个数据项，表示这条线段在X轴上从start位置开始到end位置结束。
 * 给定一批线段，求所有重合区域中最多重合了几个线段，首尾相接的线段不算重合。
 * 例如：线段[1,2]和线段[2.3]不重合。
 * 线段[1,3]和线段[2,3]重合
 */

constexpr int N = 10'005;

struct node
{
    int start;
    int end;
};

node line[N];

auto cmp = [](node a, node b) {
    return a.start < b.start;
};

void entry()
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
    {
        scanf("%d%d", &line[i].start, &line[i].end);
    }

    std::sort(line, line + n, cmp);


    std::priority_queue<int, std::vector<int>, std::greater<>> queue;
    int max = 0;

    for (int i = 0; i < n; ++i)
    {
        while (!queue.empty())
        {
            auto tmp = queue.top();
            if (tmp > line[i].start)
                break;
            queue.pop();
        }
        queue.push(line[i].end);
        if (max < queue.size())
            max = (int)queue.size();
    }

    std::cout << max;
}
}







int main()
{
    lso::entry();
    return 0;
}

