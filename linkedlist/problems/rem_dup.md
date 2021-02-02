#  Remove Duplicates from Sorted List II
[problem statement]()
It was difficult to come up with iterative solution, there were few 
edges cases that was difficult for me to cover on iterative case.
Recursive was easy for me.

## Recursive

```cpp
class Solution {
public:
    ListNode* removeDup(ListNode* head, int prev)
    {
       // base case 
       if(head == NULL) 
           return NULL;
        
       // val same as prev 
        if(head->val == prev)
            return removeDup(head->next, prev);
        
        if(head->next != NULL && head->next->val == head->val)
            return removeDup(head->next, head->val);
        
        // no need to remove val solve n-1
        head->next = removeDup(head->next, head->val);
        return head;
    }
    
    ListNode* deleteDuplicates(ListNode* head) {
        return removeDup(head, 101);
    }
};
```

## Iterative

```cpp
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        // sentinal node
        // purpose is to avoid edge case
        ListNode *sentinal = new ListNode(), *pred;
        sentinal->next = head;
        
        pred = sentinal; 
        while(head)
        {
            if(head->next && head->val == head->next->val)
            {
                while(head->next && head->val == head->next->val)
                    head = head->next;
                // we wil be on the last dup, skip that too
                pred->next = head->next;
            }
            else
                pred = pred->next;
            
            head = head->next;
        }
        return sentinal->next;
    }
};
```
