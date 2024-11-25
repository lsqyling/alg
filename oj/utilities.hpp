//
// Created by 10580.
//

#ifndef CPP_COMPLEX_OJ_LEETCODE_UTILITIES_HPP
#define CPP_COMPLEX_OJ_LEETCODE_UTILITIES_HPP
#include <iostream>
#include <utility>
#include <algorithm>
#include <random>
#include <format>
#include <queue>
#include <stack>
#include <limits>
#include <cstdio>

#ifdef _MSC_VER
#define scanf(fmt, ...) scanf_s(fmt, __VA_ARGS__)
#else
#define scanf(fmt, ...) scanf(fmt, ##__VA_ARGS__)
#endif

inline int gen_random(int min, int max)
{
    std::random_device rd;
    std::mt19937 engine{rd()};
    std::uniform_int_distribution<int> dist(min, max);

    return dist(engine);
}

inline std::vector<int> gen_rd_array(int n, int min, int max)
{
    std::vector<int> arr(n);
    for (int i = 0; i < n; ++i)
    {
        arr[i] = gen_random(min, max);
    }

    return arr;
}

inline bool is_sorted(const std::vector<int> &arr)
{
    int n = static_cast<int>(arr.size());
    for (int i = 0; i < n - 1; ++i)
    {
        if (arr[i] > arr[i+1])
            return false;
    }
    return true;
}

template<typename T>
inline void print_binary(T n)
{
    int s = sizeof(T) * 8;
    for (int i = s - 1; i >= 0; --i)
    {
        if ((n & (1 << i)) == 0)
            std::cout << "0";
        else
            std::cout << "1";
    }
    std::cout << "\n";
}


#endif //CPP_COMPLEX_OJ_LEETCODE_UTILITIES_HPP
