# Remove val from LL

[problem statement](https://leetcode.com/problems/remove-linked-list-elements/)
```cpp
class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
        ListNode* dummy = new ListNode();
        dummy->next = head;
        ListNode* curr = dummy->next;
        ListNode* prev = dummy;
        
        while(curr)
        {
            if(curr->val == val)
            {
                prev->next = curr->next;
                curr = curr->next; 
            }
            else
            {
                prev = curr;
                curr = curr->next;
            }
        }
        return dummy->next;
    }
};
```
