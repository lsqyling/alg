#include "utilities.hpp"

namespace single_list {
//Definition for singly-linked list.
struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    explicit ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

namespace leetcode_62 {
//206. Reverse Linked List
class Solution
{
public:
    static ListNode *reverseList(ListNode *head)
    {
        ListNode *cur = head, *prev = nullptr;
        while (cur)
        {
            auto tmp = cur->next;
            cur->next = prev;

            prev = cur;
            cur = tmp;
        }
        return prev;
    }
};
}

namespace leetcode_21 {
//21. Merge Two Sorted Lists
class Solution
{
public:
    static ListNode *mergeTwoLists(ListNode *list1, ListNode *list2)
    {
        if (list1 == nullptr && list2 == nullptr)
            return nullptr;
        if (list1 == nullptr && list2)
            return list2;
        if (list1 && list2 == nullptr)
            return list1;

        ListNode *list, *cur, *cur1, *next1, *cur2, *next2;
        cur1 = list1;
        cur2 = list2;

        list = cur1->val <= cur2->val ? cur1 : cur2;
        list == cur1 ? (cur1 = cur1->next) : (cur2 = cur2->next);
        cur = list;

        while (cur1 && cur2)
        {
            if (cur1->val <= cur2->val)
            {
                cur->next = cur1;
                cur1 = cur1->next;
            }
            else
            {
                cur->next = cur2;
                cur2 = cur2->next;
            }
            cur = cur->next;
        }
        if (cur1)
            cur->next = cur1;
        if (cur2)
            cur->next = cur2;

        return list;
    }
};
}

namespace leetcode_2 {
//2. Add Two Numbers
class Solution
{
public:
    static ListNode *addTwoNumbers(ListNode *l1, ListNode *l2)
    {
        ListNode *list{nullptr}, *cur;
        ListNode *cur1 = l1, *cur2 = l2;

        int carry = 0, sum;
        while (cur1 || cur2)
        {
            sum = (cur1 ? cur1->val : 0) + (cur2 ? cur2->val : 0) + carry;

            int val = sum % 10;
            carry = sum / 10;

            if (list)
            {
                cur->next = new ListNode(val);
                cur = cur->next;
            }
            else
            {
                list = new ListNode(val);
                cur = list;
            }
            if (cur1)
                cur1 = cur1->next;
            if (cur2)
                cur2 = cur2->next;
        }
        if (carry)
            cur->next = new ListNode(carry);
        return list;
    }

};
}

namespace leetcode_86 {
//86. Partition List
class Solution
{
public:
    static ListNode *partition(ListNode *head, int x)
    {
        if (head == nullptr)
            return head;

        ListNode *lh{nullptr}, *lt, *rh{nullptr}, *rt{nullptr};
        ListNode *cur = head;

        while (cur)
        {
            if (cur->val < x)
            {
                if(lh)
                {
                    lt->next = cur;
                    lt = lt->next;
                }
                else
                {
                    lh = cur;
                    lt = lh;
                }
            }
            else
            {
                if (rh)
                {
                    rt->next = cur;
                    rt = rt->next;
                }
                else
                {
                    rh = cur;
                    rt = rh;
                }
            }
            cur = cur->next;
        }
        if (lh == nullptr)
            return rh;

        lt->next = rh;
        if(rh)
            rt->next = nullptr;

        return lh;
    }
};
}
}


namespace leetcode_225 {
class MyStack
{
public:
    MyStack() = default;

    void push(int x)
    {
        q1.push(x);
    }

    int pop()
    {
        int n = (int)q1.size() - 1;
        for (int i = 0; i < n; ++i)
        {
            q2.push(q1.front());
            q1.pop();
        }
        int x = q1.front();
        q1.pop();
        std::swap(q1, q2);
        return x;

    }

    int top()
    {
        return q1.back();

    }

    bool empty()
    {
        return q1.empty() && q2.empty();
    }


private:
    std::queue<int> q1, q2;

};
}

namespace leetcode_232 {
class MyQueue
{
public:
    MyQueue() = default;

    void push(int x)
    {
        s1.push(x);
    }

    int pop()
    {
        if (s2.empty())
        {
            while (!s1.empty())
            {
                s2.push(s1.top());
                s1.pop();
            }
        }
        int top = s2.top();
        s2.pop();
        return top;
    }

    int peek()
    {
        if (s2.empty())
        {
            while (!s1.empty())
            {
                s2.push(s1.top());
                s1.pop();
            }
        }
        int top = s2.top();
        return top;
    }

    bool empty()
    {
        return s1.empty() && s2.empty();
    }

private:
    std::stack<int> s1, s2;
};
}

namespace leetcode_155 {
class MinStack
{
public:
    MinStack() = default;

    void push(int val)
    {
        data.push(val);
        if (min.empty())
            min.push(val);
        else
        {
            if (val <= min.top())
                min.push(val);
            else
                min.push(min.top());
        }
    }

    void pop()
    {
        data.pop();
        min.pop();
    }

    int top()
    {
        return data.top();
    }

    int getMin()
    {
        return min.top();
    }

private:
    std::stack<int> data, min;
};
}

namespace leetcode_641 {
class MyCircularDeque
{
public:
    explicit MyCircularDeque(int k) : capacity(k), size(0), arr(k, 0), front(k/2), rear(k/2) {}
    bool insertFront(int value)
    {
        if (isFull())
            return false;
        if (isEmpty())
        {
            front = rear = 0;
            arr[0] = value;
        }
        else
        {
            front = (front - 1 + capacity) % capacity;
            arr[front] = value;
        }
        ++size;
        return true;
    }

    bool insertLast(int value)
    {
        if (isFull())
            return false;
        if (isEmpty())
        {
            front = rear = 0;
            arr[0] = value;
        }
        else
        {
            rear = (rear + 1) % capacity;
            arr[rear] = value;
        }
        ++size;
        return true;
    }

    bool deleteFront()
    {
        if (isEmpty())
            return false;
        front = (front + 1) % capacity;
        --size;
        return true;
    }

    bool deleteLast()
    {
        if (isEmpty())
            return false;
        rear = (rear - 1 + capacity) % capacity;
        --size;
        return true;
    }

    int getFront()
    {
        if (isEmpty())
            return -1;
        return arr[front];

    }

    int getRear()
    {
        if (isEmpty())
            return -1;
        return arr[rear];
    }
    [[nodiscard]]
    bool isEmpty() const
    {
        return size == 0;
    }

    [[nodiscard]]
    bool isFull() const
    {
        return size == capacity;
    }
private:
    int capacity;
    int size;
    std::vector<int> arr;
    int front, rear;

};
}

using single_list::ListNode;

namespace leetcode_23 {
/*
 * 23. Merge k Sorted Lists
 *
 * You are given an array of k linked-lists lists, each linked-list is sorted in ascending order.
 *
 * Merge all the linked-lists into one sorted linked-list and return it.
 */
class Solution {
public:
    static ListNode* mergeKLists(std::vector<ListNode*>& lists) {
        auto less = [](ListNode *lhs, ListNode *rhs) {
            return lhs->val > rhs->val;
        };
        std::priority_queue<ListNode *, std::vector<ListNode *>, decltype(less)> queue(less);
        for (auto item: lists)
        {
            if (item)
                queue.push(item);
        }
        if (queue.empty())
            return nullptr;
        ListNode *head{queue.top()};
        auto cur = head;
        queue.pop();

        while (!queue.empty())
        {
            if (cur->next)
                queue.push(cur->next);

            cur->next = queue.top();
            queue.pop();

            cur = cur->next;
        }

        return head;
    }
};
}



int main()
{
    int i = 768, j = 12288, k = -1280;
    print_binary(i);
    print_binary(j);
    print_binary(k);





    return 0;
}
