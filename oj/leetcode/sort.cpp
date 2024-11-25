#include "../utilities.hpp"

namespace leetcode_912 {
class Solution {
public:
    std::vector<int> sortArray(std::vector<int>& nums) {
        merge_sort(nums, 0, (int)nums.size() - 1);
        merge_sort_iterative(nums);
        quick_3way_sort(nums, 0, (int)nums.size()-1);
        quick_sort(nums, 0, (int)nums.size()-1);
        heap_sort(nums);
        radix_sort_s(nums);
        return nums;
    }


    static void build_heap(std::vector<int> &arr, int n)
    {
        for (int i = (n - 1) / 2; i >= 0; --i)
        {
            adjust_down(arr, n-1, i);
        }
    }

    static void adjust_down(std::vector<int> &arr, int high, int index)
    {
        int i = index, j = 2 * i + 1;
        while (j <= high)
        {
            if (j + 1 <= high && arr[j] < arr[j+1])
                ++j;
            if (arr[j] > arr[i])
            {
                std::swap(arr[j], arr[i]);
                i = j;
                j = 2 * i + 1;
            }
            else
                break;
        }
    }

    static void heap_sort(std::vector<int> &arr)
    {
        int n = static_cast<int>(arr.size());
        build_heap(arr, n);

        for (int i = n - 1; i > 0; --i)
        {
            std::swap(arr[0], arr[i]);
            adjust_down(arr, i-1, 0);
        }
    }

    static int random_index(int left, int right)
    {
        std::random_device rd;
        std::mt19937 e{rd()};
        std::uniform_int_distribution<int> dist(left, right);
        return dist(e);
    }

    static void quick_3way_sort(std::vector<int> &arr, int left, int right)
    {
        if (left >= right)
            return ;

        int i = left, lt = left;
        int gt = right;

        int pivot = arr[random_index(left, right)];
        while (i <= gt)
        {
            if (arr[i] < pivot)
                std::swap(arr[i++], arr[lt++]);
            else if (arr[i] > pivot)
                std::swap(arr[i], arr[gt--]);
            else
                ++i;
        }

        quick_3way_sort(arr, left, lt - 1);
        quick_3way_sort(arr, gt + 1, right);
    }

    void quick_sort(std::vector<int> &arr, int left, int right)
    {
        if (CutOff < right - left)
        {
            int pivot = median3(arr, left, right);

            int i = left, j = right - 1;
            for (; ; )
            {
                while (arr[++i] < pivot);
                while (arr[--j] > pivot);
                if (i < j)
                    std::swap(arr[i], arr[j]);
                else
                    break;
            }
            std::swap(arr[right-1], arr[i]);

            quick_sort(arr, left, i - 1);
            quick_sort(arr, i + 1, right);
        }
        else
        {
            insert_sort(arr, left, right);
        }
    }

    static void insert_sort(std::vector<int> &arr, int l, int r)
    {
        for (int i = l + 1; i <= r; ++i)
        {
            int j, tmp = arr[i];
            for (j = i - 1; j >= l && arr[j] > tmp; --j)
                arr[j+1] = arr[j];
            arr[j+1] = tmp;
        }
    }


    static int median3(std::vector<int> &arr, int left, int right)
    {
        int mid = (left + right) / 2;
        if (arr[left] > arr[mid])
            std::swap(arr[left], arr[mid]);
        if (arr[left] > arr[right])
            std::swap(arr[left], arr[right]);
        if (arr[mid] > arr[right])
            std::swap(arr[mid], arr[right]);
        std::swap(arr[mid], arr[right-1]);
        return arr[right-1];
    }


    void merge_sort(std::vector<int> &arr, int left, int right)
    {
        if (left == right)
            return ;

        int mid = left + (right-left)/2;
        merge_sort(arr, left, mid);
        merge_sort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }

    static void merge_sort_iterative(std::vector<int> &arr)
    {
        int n = static_cast<int>(arr.size());
        for (int step = 1; step < n; step <<= 1)
        {
            for (int i = 0; i < n - step; i += 2 * step)
            {
                merge(arr, i, i + step - 1, std::min(i + 2 * step - 1, n - 1));
            }
        }
    }



    static void merge(std::vector<int> &arr, int left, int mid, int right)
    {
        int i = left, j = mid + 1;
        int k = left;

        while (i <= mid && j <= right)
        {
            if (arr[i] <= arr[j])
                aux[k++] = arr[i++];
            else
                aux[k++] = arr[j++];
        }

        while (i <= mid)
            aux[k++] = arr[i++];
        while (j <= right)
            aux[k++] = arr[j++];

        for (int t = left; t <= right; ++t)
        {
            arr[t] = aux[t];
        }
    }

    int bits_of(int num, int base)
    {
        int ans = 0;
        do
        {
            num /= base;
            ++ans;
        } while (num);
        return ans;
    }

    void radix_sort_s(std::vector<int> &arr)
    {
        int n = (int)arr.size();
        int min = arr[0];
        for (int i = 1; i < n; ++i)
        {
            if (arr[i] < min)
                min = arr[i];
        }
        int max = 0;
        for (int i = 0; i < n; ++i)
        {
            arr[i] -= min;
            max = std::max(max, arr[i]);
        }
        radix_sort(arr, n, bits_of(max, BASE));
        for (int i = 0; i < n; ++i)
        {
            arr[i] += min;
        }
    }


    void radix_sort(std::vector<int> &arr, int n, int bits)
    {
        for (int offset = 1; bits > 0; offset *= BASE, --bits)
        {
            std::fill(cnt, cnt + BASE, 0);
            for (int i = 0; i < n; ++i)
            {
                ++cnt[(arr[i]/offset)%BASE];
            }
            for (int i = 1; i < BASE; ++i)
            {
                cnt[i] += cnt[i-1];
            }
            for (int i = n-1; i >= 0; --i)
            {
                heap[--cnt[(arr[i]/offset)%BASE]] = arr[i];
            }
            for (int i = 0; i < n; ++i)
            {
                arr[i] = heap[i];
            }
        }
    }


private:
    static constexpr int LEN = 5 * 10'000;
    static constexpr int MIN = -5 * 10'000;
    static constexpr int MAX = 5 * 10'000;
    static constexpr int BASE = 10;
    static inline int cnt[BASE]{};
    static inline int heap[LEN]{};


    static constexpr int N = 50'005;
    static constexpr int CutOff = 100;
    inline static int aux[N];

};

}

namespace leetcode_493 {
class Solution {
public:
    int reversePairs(std::vector<int>& nums) {
        return merge_count(nums, 0, (int)nums.size() - 1);
    }

    int merge_count(std::vector<int> &arr, int l, int r)
    {
        if (l == r)
            return 0;

        int m = (l + r) >> 1;
        return merge_count(arr, l, m) + merge_count(arr, m+1, r) + merge(arr, l, m, r);
    }

    static int merge(std::vector<int> &arr, int l, int m, int r)
    {
        int ans = 0;
        for (int i = l, j = m+1; i <= m; ++i)
        {
            while (j <= r && (long)arr[i] > (long)2*arr[j])
                j++;

            ans += j - m - 1;
        }

        int i = l, j = m + 1, k = l;
        while (i <= m && j <= r)
        {
            if (arr[i] <= arr[j])
                aux[k++] = arr[i++];
            else
                aux[k++] = arr[j++];
        }
        while (i <= m)
            aux[k++] = arr[i++];
        while (j <= r)
            aux[k++] = arr[j++];

        for (int t = l; t <= r; ++t)
        {
            arr[t] = aux[t];
        }

        return ans;
    }


    static constexpr int N = 100'005;
    inline static int aux[N];
};
}

namespace leetcode_215 {
//215. Kth Largest Element in an Array
class Solution {
public:
    static int findKthLargest(std::vector<int>& nums, int k) {
        return randomized_select(nums, 0, (int)nums.size()-1, (int)nums.size()-k);
    }

    static int random_index(int left, int right)
    {
        std::random_device rd;
        std::mt19937 e{rd()};
        std::uniform_int_distribution<int> dist(left, right);
        return dist(e);
    }



    static int randomized_select(std::vector<int> &arr, int left, int right, int index)
    {
        int ans = 0;
        for (int l = left, r = right; l <= r; )
        {
            int pivot_pos = random_index(l, r);
            auto range = partition(arr, l, r, arr[pivot_pos]);
            int lt = range.first, gt = range.second;

            if (index < lt)
                r = lt - 1;
            else if (index > gt)
                l = gt + 1;
            else
            {
                ans = arr[index];
                break;
            }
        }
        return ans;
    }

    static std::pair<int, int> partition(std::vector<int> &arr, int left, int right, int x)
    {
        int lt = left, gt = right;
        int i = left;
        while (i <= gt)
        {
            if (arr[i] < x)
                std::swap(arr[i++], arr[lt++]);
            else if (arr[i] > x)
                std::swap(arr[gt--], arr[i]);
            else
                ++i;
        }

        return {lt, gt};
    }
};


}










int main()
{
    return 0;
}