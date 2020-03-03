#### LC 142 linked list cycle

---

简单的一道检查链表成环的问题

这道题额外的要求了返回成环处的地址：

对于成环的检查问题， 我们用快慢指针可以解决

如何返回成环处的地址呢

Eg:

对于下面的链表， 成环处在 2 处， 使用快慢指针的话， 快慢指针会相交在 4 的位置

由于快指针每次走 2， 慢指针每次走 1

因此在此时：

1. 快指针比满指针多走了 **一个环的距离**
2. 快指针走的距离是慢指针的一倍

可以得出： 

一个环的长度 = 起始点到成环点的长度 + 成环点到相遇点的长度

本身有：

一个环的长度 = 相遇点到成环点的长度 + 成环点到相遇点的长度

可以得出： 

相遇点到成环点的长度 = 起始点到成环点的长度 

那再开一个慢指针在此时从头开始跑， 两个慢指针再相遇， 就是成环点了

6  ->  3  ->  ***2***  -> 0  ->  **4**

​						\		/

​							1



了解了流程之后， 代码很好写了：

```c++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        ListNode* fast = head, *slow = head;
        while(fast && fast->next){
            fast = fast->next->next;
            slow = slow->next;
            if(fast == slow) break;
        }
        if(!fast || !fast->next) return nullptr;
        slow = head;
        while(slow != fast){
            fast = fast->next;
            slow = slow->next;
        }
        return slow;
    }
};
```

