#include "../utilities.hpp"

namespace double_pointer {
//Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    explicit ListNode(int x) : val(x), next(nullptr) {}
};

namespace leetcode_141 {
// 141. Linked List Cycle
class Solution {
public:
    static bool hasCycle(ListNode *head) {
        if (head == nullptr || head->next == nullptr) {
            return false;
        }
        auto fast = head;
        auto slow = head;
        fast = fast->next->next;
        slow = slow->next;
        while (fast && fast->next && slow != fast) {
            fast = fast->next->next;
            slow = slow->next;
        }
        if (slow == fast && fast)
            return true;
        return false;
    }
};
}

namespace leetcode_142 {
// 142. Linked List Cycle II
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        if (head == nullptr || head->next == nullptr) {
            return nullptr;
        }
        auto fast = head;
        auto slow = head;
        fast = fast->next->next;
        slow = slow->next;
        while (fast && fast->next && fast != slow) {
            fast = fast->next->next;
            slow = slow->next;
        }
        if (fast == nullptr || fast->next == nullptr) {
            return nullptr;
        }
        fast = head;
        while (fast != slow) {
            fast = fast->next;
            slow = slow->next;
        }
        return fast;
    }
};
}

namespace leetcode_160 {
// 160. Intersection of Two Linked Lists
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        auto p1 = headA;
        auto p2 = headB;
        while (p1 != p2) {
            p1 = p1 ? p1->next : headB;
            p2 = p2 ? p2->next : headA;
        }
        return p1;
    }
};
}

namespace leetcode_19 {
// 19. Remove Nth Node From End of List
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        auto prev = head;
        auto next = head;
        for (int i = 0; i < n; ++i) {
            next = next->next;
        }
        if (next == nullptr) {
            auto p = head->next;
            delete head;
            return p;
        }
        while (next->next) {
            prev = prev->next;
            next = next->next;
        }
        auto p = prev->next;
        prev->next = p->next;
        delete p;
        return head;
    }
};
}

namespace leetcode_23 {
// 23. Merge k Sorted Lists
class Solution {
public:
    ListNode* mergeKLists(std::vector<ListNode*>& lists) {
        auto cmp = [](ListNode *a, ListNode *b) {
            return a->val > b->val;
        };
        std::priority_queue<ListNode *, std::vector<ListNode *>, decltype(cmp)> minheap(cmp);
        for (auto node : lists) {
            if (node) {
                minheap.push(node);
            }
        }
        auto head = new ListNode(0);
        auto p = head;
        while (!minheap.empty()) {
            auto node = minheap.top();
            minheap.pop();
            p->next = node;
            p = p->next;
            if (node->next) {
                minheap.push(node->next);
            }
        }
        return head->next;
    }
};
}

namespace leetcode_206 {
// 206. Reverse Linked List
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if (head == nullptr || head->next == nullptr) {
            return head;
        }
        ListNode *pre = nullptr;
        auto cur = head;
        while (cur) {
            auto next = cur->next;
            cur->next = pre;
            pre = cur;
            cur = next;
        }
        return pre;
    }

    ListNode* reverseList_recursive_v(ListNode* head) {
        if (head == nullptr || head->next == nullptr) {
            return head;
        }
        auto newhead = reverseList_recursive_v(head->next);
        head->next->next = head;
        head->next = nullptr;
        return newhead;
    }
};
}

namespace leetcode_25 {
// 25. Reverse Nodes in k-Group
class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        if (head == nullptr || head->next == nullptr || k < 2) {
            return head;
        }
        auto tail = head;
        for (int i = 0; i < k; ++i) {
            if (tail == nullptr) {
                return head;
            }
            tail = tail->next;
        }
        ListNode *pre{nullptr};
        auto cur = head;
        while (cur != tail) {
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

namespace leetcode_92 {
// 92. Reverse Linked List II
class Solution {
public:
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        if (head->next == nullptr || left == right)
            return head;
        auto dummy = new ListNode(-1);
        dummy->next = head;
        auto cur = dummy;
        int i;
        for (i = 0; i < left - 1; ++i) {
            cur = cur->next;
        }
        auto preleft = cur;
        auto tail = preleft->next;
        for (; i < right + 1; ++i) {
            cur = cur->next;
        }
        auto rightnext = cur;
        ListNode *pre{nullptr};
        cur = preleft->next;
        while (cur != rightnext) {
            auto next = cur->next;
            cur->next = pre;
            pre = cur;
            cur = next;
        }

        preleft->next = pre;
        tail->next = rightnext;
        return dummy->next;
    }
};
}
}






























