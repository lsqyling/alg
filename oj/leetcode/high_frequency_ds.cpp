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
        counts[val]++;
        table[counts[val]].push_back(val);
        max_times = std::max(max_times, counts[val]);
    }

    int pop() {
        int ret = table[max_times].back();
        table[max_times].pop_back();
        if (table[max_times].empty())
        {
            table.erase(max_times);
            --max_times;
        }
        --counts[ret];
        if (counts[ret] == 0)
            counts.erase(ret);

        return ret;
    }

private:
    int max_times{0};
    std::unordered_map<int, std::vector<int>> table;
    std::unordered_map<int, int> counts;
};

class AllOne {
public:
    AllOne() : head(new bucket), tail(new bucket(std::numeric_limits<int>::max()))
    {
        head->next = tail;
        tail->prev = head;
    }

    ~AllOne()
    {
        auto p = head;
        while (p)
        {
            auto tmp = p->next;
            delete p;
            p = tmp;
        }
    }

    void inc(std::string key) {
        if (map.find(key) == map.end())
        {
            if (head->next->count == 1)
            {
                head->next->set.insert(key);
                map[key] = head->next;
            }
            else
            {
                auto newb = new bucket(1);
                newb->set.insert(key);
                map[key] = newb;
                add_next(head, newb);
            }
        }
        else
        {
            auto b = map[key];
            if (b->next->count == b->count + 1)
            {
                b->next->set.insert(key);
                map[key] = b->next;

            }
            else
            {
                auto newb = new bucket(b->count + 1);
                newb->set.insert(key);
                map[key] = newb;
                add_next(b, newb);
            }
            b->set.erase(key);
            if (b->set.empty())
            {
                remove_bucket(b);
            }
        }
    }

    void dec(std::string key) {
        auto b = map[key];
        if (b->count == 1)
            map.erase(key);
        else
        {
            if (b->count - 1 == b->prev->count)
            {
                map[key] = b->prev;
                b->prev->set.insert(key);
            }
            else
            {
                auto newb = new bucket(b->count - 1);
                newb->set.insert(key);
                map[key] = newb;
                add_prev(b, newb);
            }
        }
        b->set.erase(key);
        if (b->set.empty())
            remove_bucket(b);
    }

    std::string getMaxKey() {
        if (tail->prev == head)
            return {};
        return *tail->prev->set.begin();
    }

    std::string getMinKey() {
        if (head->next == tail)
            return {};
        return *head->next->set.begin();
    }

private:
    struct bucket
    {
        int count;
        std::unordered_set<std::string> set;
        bucket *prev;
        bucket *next;
        explicit bucket(int freq = 0) : count(freq), prev(nullptr), next(nullptr) {}
    };

    bucket *head;
    bucket *tail;
    std::unordered_map<std::string, bucket *> map;

    void remove_bucket(bucket *b)
    {
        b->prev->next = b->next;
        b->next->prev = b->prev;
        delete b;
    }

    void add_next(bucket *b, bucket *x)
    {
        x->next = b->next;
        b->next->prev = x;

        b->next = x;
        x->prev = b;
    }

    void add_prev(bucket *b, bucket *x)
    {
        b->prev->next = x;
        x->prev = b->prev;

        x->next = b;
        b->prev = x;
    }


};








int main()
{
    return 0;
}

