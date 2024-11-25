//
// Created by 10580.
//
#include "../utilities.hpp"

namespace xor_ {

/*
 * swap two nums.
 */
void swap_integers(int &a, int &b)
{
    b = a ^ b;
    a = a ^ b;
    b = a ^ b;
}

void test_swap_integers()
{
    int a = 3, b = 4;
    printf("a = %d, b = %d\n", a, b);
    swap_integers(a, b);
    printf("a = %d, b = %d\n", a, b);
}

int flip(int n)
{
    return n ^ 1;
}

int sign(int n)
{
    int bit = ((1 << 31) & n) == 0 ? 0 : 1;
    return flip(bit);
}
/*
 * This function has overflow risk.
 */
int max_v0(int a, int b)
{
    int c = a - b;
    int ra = sign(c);
    int rb = flip(ra);
    return a * ra + b * rb;
}
/*
 * better
 */
int max_v1(int a, int b)
{
    int c = a - b;
    int sa = sign(a);
    int sb = sign(b);
    int sc = sign(c);

    int diffab = sa ^ sb;
    int sameab = flip(diffab);

    int ra = diffab * sa + sameab * sc;
    int rb = flip(ra);

    return ra * a + rb * b;
}




void test_max()
{
    printf("max_v0(3, 4) = %d\n", max_v0(3, 4));
    printf("max_v0(3, -4) = %d\n", max_v0(3, -4));
    printf("max_v0(int.max, int.min) = %d\n", max_v0(std::numeric_limits<int>::max(), std::numeric_limits<int>::min()));
    printf("max_v1(int.max, int.min) = %d\n", max_v1(std::numeric_limits<int>::max(), std::numeric_limits<int>::min()));
}

namespace leetcode_268 {
//268. Missing Number
class Solution {
public:
    static int missingNumber(std::vector<int>& nums) {
        int xor_all = 0;
        int xor_has = 0;
        for (int i = 0; i < nums.size(); ++i)
        {
            xor_all = xor_all ^ i;
            xor_has = xor_has ^ nums[i];
        }
        xor_all = xor_all ^ (int)nums.size();
        return xor_all ^ xor_has;
    }
};
}

namespace leetcode_136 {
//136. Single Number
class Solution {
public:
    static int singleNumber(std::vector<int>& nums) {
        int x = 0;
        for (auto e : nums)
            x ^= e;
        return x;
    }
};
}

namespace leetcode_260 {
//260. Single Number III
class Solution {
public:
    static std::vector<int> singleNumber(std::vector<int>& nums) {
        int eor0 = 0;
        for (auto e : nums)
            eor0 ^= e;
        int right_one = eor0 & (~eor0 + 1);
        int eor1 = 0;
        for (auto e : nums)
        {
            if ((right_one & e) == 0)
                eor1 ^= e;
        }

        return {eor1, eor1 ^ eor0};
    }
};
}

namespace leetcode_137 {
//137. Single Number II
class Solution {
public:
    static int singleNumber(std::vector<int>& nums) {
        int cnt[32]{};
        for (auto num : nums)
        {
            for (int i = 0; i < 32; ++i)
                cnt[i] += (num >> i) & 1;
        }
        int ans = 0;
        for (int i = 0; i < 32; ++i)
        {
            if (cnt[i] % 3)
                ans |= 1 << i;
        }
        return ans;
    }
};
}
}


namespace bits {
namespace leetcode_231 {
//231. Power of Two
class Solution {
public:
    static bool isPowerOfTwo(int n) {

        return n > 0 && n == (n & -n);
    }
};
}

namespace leetcode_326 {
//326. Power of Three
// 3 ^ 19 = 1162261467
class Solution {
public:
    static bool isPowerOfThree(int n) {
        return n > 0 && (int)std::pow(3, 19) % n == 0;
    }
};
}

int latest2pow(int n)
{
    if (n <= 1)
        return 1;
    --n;

    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    return n + 1;
}

void test_latest2pow()
{
    printf("63 latest 2 pow:  = %d\n", latest2pow(63));
    printf("1125 latest 2 pow:  = %d\n", latest2pow(1125));
    printf("1162261467 latest 2 pow:  = %d\n", latest2pow(1162261467));
    printf("2147483647 latest 2 pow:  = %d\n", latest2pow(2147483647));
}


namespace leetcode_201 {
//201. Bitwise AND of Numbers Range
class Solution {
public:
    static int rangeBitwiseAnd(int left, int right) {
        while (left < right)
        {
            right -= right & -right;
        }

        return right;
    }
};
}

namespace leetcode_190 {
//190. Reverse Bits
class Solution {
public:
    static uint32_t reverseBits(uint32_t n) {
        n =  ((n & 0xaaaa'aaaa) >> 1) | ((n & 0x5555'5555) << 1);
        n =  ((n & 0xcccc'cccc) >> 2) | ((n & 0x3333'3333) << 2);
        n =  ((n & 0xf0f0'f0f0) >> 4) | ((n & 0x0f0f'0f0f) << 4);
        n =  ((n & 0xff00'ff00) >> 8) | ((n & 0x00ff'00ff) << 8);
        n = (n >> 16) | (n << 16);
        return n;
    }
};
}

namespace leetcode_461 {
//461. Hamming Distance
class Solution {
public:
    static int hammingDistance(int x, int y) {
        return counting_ones(x ^ y);
    }

    static int counting_ones(uint32_t n)
    {
        n = (n & 0x5555'5555) + ((n >> 1) & 0x5555'5555);
        n = (n & 0x3333'3333) + ((n >> 2) & 0x3333'3333);
        n = (n & 0x0f0f'0f0f) + ((n >> 4) & 0x0f0f'0f0f);
        n = (n & 0x00ff'00ff) + ((n >> 8) & 0x00ff'00ff);
        n = (n & 0x0000'ffff) + ((n >> 16) & 0x0000'ffff);
        return int(n);
    }
};
}

namespace leetcode_2166 {
//2166. Design Bitset
class Bitset {
public:
    explicit Bitset(int n) : data(new uint8_t[(n+7)/8]{}),size(n), zeroes(n), ones(0), has_reversed(false) {}
    ~Bitset()
    {
        delete[] data;
        data = nullptr;
    }

    void fix(int idx) {
        int index = idx >> 3;
        int offset = idx & 0x07;

        if (!has_reversed)
        {
            if ((data[index] & (1 << offset)) == 0)
            {
                data[index] |= (1 << offset);
                --zeroes;
                ++ones;
            }
        }
        else
        {
            if ((data[index] & (1 << offset)) != 0)
            {
                data[index] ^= (1 << offset);
                --zeroes;
                ++ones;
            }
        }
    }

    void unfix(int idx) {
        int index = idx >> 3;
        int offset = idx & 0x07;

        if (!has_reversed)
        {
            if ((data[index] & (1 << offset)) != 0)
            {
                data[index] ^= (1 << offset);
                ++zeroes;
                --ones;
            }
        }
        else
        {
            if ((data[index] & (1 << offset)) == 0)
            {
                data[index] |= (1 << offset);
                ++zeroes;
                --ones;
            }
        }
    }

    void flip() {
        has_reversed = !has_reversed;
        std::swap(ones, zeroes);
    }

    [[nodiscard]]
    bool all() const {
        return ones == size;
    }

    [[nodiscard]]
    bool one() const {
        return ones > 0;
    }

    [[nodiscard]]
    int count() const {
        return ones;
    }

    [[nodiscard]]
    std::string toString() const {
        std::string ans;
        for (int i = 0, k = 0, state; i < size; ++k)
        {
            auto byte = data[k];
            for (int j = 0; j < 8 && i < size; ++j, ++i)
            {
                state = (byte >> j) & 1;
                state ^= (has_reversed ? 1 : 0);
                ans.push_back(state ? '1' : '0');
            }
        }
        return ans;
    }

private:
    uint8_t *data;
    const int size;
    int zeroes;
    int ones;
    bool has_reversed;
};
}


namespace leetcode_29 {
//29. Divide Two Integers
}

/*
 * Implement four arithmetic operations of addition, subtraction, multiplication,
 * and division using bitwise operations.
 */
int add(int a, int b)
{
    int ans = a;
    while (b)
    {
        ans = a ^ b;
        b = (a & b) << 1;
        a = ans;
    }
    return ans;
}

int negative(int a)
{
    return add(~a, 1);
}

int minus(int a, int b)
{
    return add(a, negative(b));
}

int multiply(int a, int b)
{
    int ans = 0;
    unsigned bu = b;
    while (bu)
    {
        if ((bu & 1))
            ans = add(ans, a);

        bu >>= 1;
        a <<= 1;
    }
    return ans;
}


// a != Integer.min, b != Integer.min
int div(int a, int b)
{
    int x = a < 0 ? negative(a) : a;
    int y = b < 0 ? negative(b) : b;

    int ans = 0;
    for (int i = 30; i >= 0; i = minus(i, 1))
    {
        if ((x >> i) >= y)
        {
            ans |= (1 << i);
            x = minus(x, y << i);
        }
    }
    return a < 0 ^ b < 0 ? negative(ans) : ans;
}


int divide(int a, int b)
{
    auto MIN = std::numeric_limits<int>::min();
    auto MAX = std::numeric_limits<int>::max();
    if (a == MIN && b == MIN)
        return 1;
    if (a != MIN && b != MIN)
        return div(a, b);
    if (b == MIN)
        return 0;
    if (b == negative(1))
        return MAX;

    a = add(a, b < 0 ? negative(b) : b);
    int ans = div(a, b);
    int offset = b > 0 ? negative(1) : 1;
    return add(ans, offset);
}
}





int main()
{
    xor_::test_swap_integers();
    xor_::test_max();
    bits::test_latest2pow();

    std::cout << (unsigned (-6) >> 1) << std::endl;
    std::cout << bits::multiply(2, -1) << std::endl;




    return 0;
}