# Add Two Number

Well this feels so easy but don't hurry take the time.
There are edge cases, few notes are don't forget to 
update the pointer you will endup in infinite loop.

*Time Complexity* : O(Max(M+N))  
*Space Complexity* : O(Max(M+N)+1)   

## Solution

```cpp
 class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        // create a new LL
        ListNode* head = new ListNode();
        ListNode* curr = head;
        int rem = 0;
        while(l1 != NULL || l2 != NULL || rem)
        {
            curr->next = new ListNode();
            curr = curr->next;
            
            if(l1)
            {
                curr->val += l1->val;
                l1 = l1->next;
            }
            
            if(l2)
            {
                curr->val += l2->val;
                l2 = l2->next;
            }
            
            curr->val += rem;
            rem = curr->val / 10;
            curr->val = curr->val % 10;
        }
        
        return head->next;
    }
}; 
```
