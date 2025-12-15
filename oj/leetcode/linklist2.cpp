#include "../utilities.hpp"

/**
 * 链表（Linked List）是计算机科学中最基础、最重要的线性数据结构之一，
 * 与数组并列，但在内存布局和操作特性上有显著不同。
 */


// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    explicit ListNode(int x = 0) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

namespace leetcode_61 {
// 61. 旋转链表
class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {
        if (!head || !head->next || k == 0) {
            return head;
        }

        // 第一步：计算链表长度 n，并找到尾节点
        int n = 1;
        auto tail = head;
        while (tail->next) {
            tail = tail->next;
            ++n;
        }

        // 第二步：实际需要旋转的步数
        int realk = k % n;
        if (realk == 0) {
            return head;
        }
        // 第三步：连接尾和头，形成环
        tail->next = head;

        // 第四步：找到新的尾节点（从 head 走 n - realk - 1 步）
        auto newtail = head;
        for (int i = 0; i < n - realk - 1; ++i) {
            newtail = newtail->next;
        }

        // 第五步：新头是 newTail->next，断开环
        auto newhead = newtail->next;
        newtail->next = nullptr;

        return newhead;
    }
};
}





































int main() {
    return 0;
}
