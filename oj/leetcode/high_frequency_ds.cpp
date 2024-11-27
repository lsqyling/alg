//
// Created by 10580.
//
#include "../utilities.hpp"


class LRUCache {
public:
    explicit LRUCache(int cap) : capacity(cap) {}

    int get(int key) {
        if (map.find(key) == map.end())
            return -1;
        make_recently(key);
        return map.at(key)->val;
    }

    void put(int key, int value) {
        if (map.find(key) != map.end())
        {
            delete_key(key);
            add_recently(key, value);
            return ;
        }
        if (capacity == cache.size_of())
        {
            remove_least_recently();
        }
        add_recently(key, value);
    }



private:

    void make_recently(int key)
    {
        auto x = map.at(key);
        cache.remove(x);
        cache.add_last(x);
    }

    void add_recently(int key, int val)
    {
        auto x = new node(key, val);
        cache.add_last(x);
        map.insert({key, x});
    }

    void delete_key(int key)
    {
        auto x = map.at(key);
        cache.remove(x);
        map.erase(key);
    }

    void remove_least_recently()
    {
        auto x = cache.remove_first();
        map.erase(x->key);
    }


    struct node
    {
        explicit node(int k = 0, int v = 0) : key(k), val(v) {}
        int key, val;
        node *next{nullptr};
        node *prev{nullptr};
    };

    struct list
    {
        list() : head(new node), tail(new node), size(0)
        {
            head->next = tail;
            tail->prev = head;
        }

        void add_last(node *x)
        {
            tail->prev->next = x;
            x->prev = tail->prev;
            x->next = tail;
            tail->prev = x;
            ++size;
        }

        void remove(node *x)
        {
            x->prev->next = x->next;
            x->next->prev = x->prev;
            --size;
        }

        node *remove_first()
        {
            if (head->next == tail)
                return nullptr;
            auto first = head->next;
            remove(first);
            return first;
        }

        [[nodiscard]]
        int size_of() const { return size;}

    private:
        node *head;
        node *tail;
        int size;
    };

    const int capacity;
    list cache;
    std::unordered_map<int, node *> map;
};

class RandomizedSet {
public:
    RandomizedSet() = default;

    bool insert(int val) {
        if (table.find(val) != table.end())
            return false;

        arr.push_back(val);
        table.insert({val, arr.size()-1});
        return true;
    }

    bool remove(int val) {
        std::unordered_map<int, int>::iterator it;
        if ((it = table.find(val)) == table.end())
            return false;

        auto index = it->second;
        auto last = arr.back();
        arr[index] = last;
        arr.pop_back();

        table[last] = index;
        table.erase(it);
        return true;
    }

    int getRandom() {
        static std::random_device rd;
        static std::mt19937 e{rd()};
        std::uniform_int_distribution<int> dist(0, int(arr.size())-1);
        return arr[dist(e)];
    }


private:
    std::vector<int> arr;
    std::unordered_map<int, int> table;
};

class RandomizedCollection {
public:
    RandomizedCollection() = default;

    bool insert(int val) {
        arr.emplace_back(val);
        table[val].insert((int)arr.size()-1);
        return table[val].size() == 1;
    }

    bool remove(int val) {
        if (table.find(val) == table.end())
            return false;

        int i = *table[val].begin();
        arr[i] = arr.back();

        table[val].erase(i);
        table[arr[i]].erase((int)arr.size()-1);

        if (i < arr.size() - 1)
            table[arr[i]].insert(i);

        if (table[val].empty())
            table.erase(val);

        arr.pop_back();
        return true;
    }

    int getRandom() {
        static std::random_device rd;
        static std::mt19937 e{rd()};
        std::uniform_int_distribution<int> d(0, (int)arr.size()-1);
        return arr[d(e)];
    }


private:
    std::vector<int> arr;
    std::unordered_map<int, std::unordered_set<int>> table;
};

class MedianFinder {
public:
    MedianFinder() = default;

    void addNum(int num) {
        if (max_heap.empty() || num <= max_heap.top())
            max_heap.push(num);
        else
            min_heap.push(num);

        balance();
    }

    double findMedian() {
        if (max_heap.size() == min_heap.size())
            return double(max_heap.top() + min_heap.top()) / 2;
        else
            return max_heap.size() > min_heap.size() ? max_heap.top() : min_heap.top();
    }

private:
    void balance()
    {
        if (std::abs((int)max_heap.size() - (int)min_heap.size()) == 2)
        {
            if (max_heap.size() > min_heap.size())
            {
                min_heap.push(max_heap.top());
                max_heap.pop();
            }
            else
            {
                max_heap.push(min_heap.top());
                min_heap.pop();
            }
        }
    }

    std::priority_queue<int> max_heap;
    std::priority_queue<int, std::vector<int>, std::greater<>> min_heap;
};

class FreqStack {
public:
    FreqStack() = default;

    void push(int val) {
        s.push(val);
    }

    int pop() {

        auto r = s.top();
        return r;
    }

    std::stack<int> s;
};










int main()
{
    return 0;
}

