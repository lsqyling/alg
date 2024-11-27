#include "../utilities.hpp"

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
        std::priority_queue<ListNode *, std::vector<ListNode *>, decltype(less)> queue;
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

namespace leetcode_160 {
class Solution {
public:
    static ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        auto p1 = headA;
        auto p2 = headB;
        int diff = 0;
        while (p1->next)
        {
            p1 = p1->next;
            ++diff;
        }
        while (p2->next)
        {
            p2 = p2->next;
            --diff;
        }
        if (p1 != p2)
            return nullptr;

        if (diff >= 0)
        {
            p1 = headA;
            p2 = headB;
        }
        else
        {
            p1 = headB;
            p2 = headA;
        }
        diff = std::abs(diff);
        while (diff--)
            p1 = p1->next;
        while (p1 != p2)
        {
            p1 = p1->next;
            p2 = p2->next;
        }
        return p1;
    }
};
}

namespace leetcode_25 {
//25. Reverse Nodes in k-Group
class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        if (head == nullptr || head->next == nullptr || k < 2)
            return head;

        auto tail = head;
        for (int i = 0; i < k; ++i)
        {
            if (tail == nullptr)
                return head;
            tail = tail->next;
        }
        ListNode *pre{nullptr};
        auto cur = head;
        while (cur != tail)
        {
            auto next = cur->next;
            cur->next = pre;
            pre = cur;
            cur = next;
        }

        head->next = reverseKGroup(tail, k);
        return pre;
    }
};
}

namespace leetcode_138 {
struct Node
{
  int val;
  Node *next;
  Node *random;
  explicit Node(int val_) : val(val_), next(nullptr), random(nullptr) {}
};

class Solution {
public:
    static Node* copyRandomList(Node* head) {
        if (head == nullptr)
            return nullptr;

        auto p = head;
        while (p)
        {
            auto node = new Node(p->val);
            node->next = p->next;
            p->next = node;
            p = node->next;
        }

        p = head;
        Node *p1;

        while (p)
        {
            auto next = p->next->next;
            p1 = p->next;

            p1->random = p->random ? p->random->next : nullptr;
            p = next;
        }

        auto newhead = head->next;
        p = head;

        while (p)
        {
            auto next = p->next->next;
            p1 = p->next;

            p->next = next;
            p1->next = next ? next->next : nullptr;

            p = next;
        }

        return newhead;
    }
};
}

namespace leetcode_234 {
//234. Palindrome Linked List
class Solution {
public:
    static bool isPalindrome(ListNode* head) {
        if (head == nullptr || head->next == nullptr)
            return true;

        auto slow = head;
        auto fast = head;
        while (fast->next && fast->next->next)
        {
            slow = slow->next;
            fast = fast->next->next;
        }

        auto pre = slow;
        auto cur = slow->next;
        pre->next = nullptr;
        while (cur)
        {
            auto next = cur->next;
            cur->next = pre;
            pre = cur;
            cur = next;
        }
//        head -> ... ->slow <-...<-pre
        auto left = head;
        auto right = pre;
        bool ans = true;
        while (left && right)
        {
            if (left->val != right->val)
            {
                ans = false;
                break;
            }
            left = left->next;
            right = right->next;
        }

        cur = pre->next;
        pre->next = nullptr;
        while (cur)
        {
            auto next = cur->next;
            cur->next = pre;
            pre = cur;
            cur = next;
        }

        return ans;
    }
};
}

namespace leetcode_142 {
//142. Linked List Cycle II
class Solution {
public:
    static ListNode *detectCycle(ListNode *head) {
        auto slow = head;
        auto fast = head;
        while (fast && fast->next)
        {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast)
                break;
        }
        if (fast == nullptr || fast->next == nullptr)
            return nullptr;
        slow = head;
        while (slow != fast)
        {
            slow = slow->next;
            fast = fast->next;
        }
        return slow;
    }
};
}

namespace leetcode_148 {
//148. Sort List
class Solution {
public:
    ListNode* sortList(ListNode* head) {
        return sort_list(head, nullptr);
    }

    ListNode *sort_list(ListNode *head, ListNode *tail)
    {
        if (head == nullptr)
            return head;
        if (head->next == tail)
        {
            head->next = nullptr;
            return head;
        }

        auto slow = head;
        auto fast = head;
        while (fast != tail && fast->next != tail)
        {
            slow = slow->next;
            fast = fast->next->next;
        }

        auto mid = slow;
        auto h1 = sort_list(head, mid);
        auto h2 = sort_list(mid, tail);

        return merge(h1, h2);
    }

    ListNode *merge(ListNode *h1, ListNode *h2)
    {
        ListNode dummyhead;
        auto cur = &dummyhead;
        auto cur1 = h1;
        auto cur2 = h2;

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
        else if (cur2)
            cur->next = cur2;

        return dummyhead.next;
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
