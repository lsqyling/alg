//
// Created by 10580.
//
#include "../utilities.hpp"

class hash_table
{
public:

    void put(int k, int v)
    {
        if (data.contains(k))
        {
            data[k].value = v;
            data[k].time_stamp = ++cnt;
        }
        else
        {
            data.insert({k, {v, ++cnt}});
        }
    }

    void setAll(int v)
    {
        set_all_value = v;
        set_all_time = ++cnt;
    }

    [[nodiscard]]
    int get(int k) const
    {
        if (!data.contains(k))
            return -1;

        auto tmp = data.at(k);
        if (tmp.time_stamp > set_all_time)
            return tmp.value;
        else
            return set_all_value;
    }
private:
    struct node
    {
        int value;
        int time_stamp;
    };

    std::unordered_map<int, node> data;
    int set_all_value{0};
    int set_all_time{0};
    int cnt{0};
};

void entry()
{
    int n, op, key, val;
    scanf("%d", &n);
    hash_table kv;
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &op);
        switch (op)
        {
            case 1:
                scanf("%d%d", &key, &val);
                kv.put(key, val);
                break;
            case 2:
                scanf("%d", &key);
                printf("%d\n", kv.get(key));
                break;
            case 3:
                scanf("%d", &val);
                kv.setAll(val);
                break;
            default:;
        }
    }
}









int main()
{
    entry();
    return 0;
}