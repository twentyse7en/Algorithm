# Palindrome

[Problem statement](https://leetcode.com/problems/palindrome-linked-list/submissions/)


Intution for O(N) space we could traverse and put all values to stack. Then 
check, stack reverses the values. For O(1) space we have to reverse the first 
half of the linked list and start comparing. But take care of odd or even length.


## Stack
```cpp
class Solution {
public:
    bool isPalindrome(ListNode* head) {
        stack<int> s;
        ListNode* tmp  = head;
        while(tmp)
        {
            s.push(tmp->val);
            tmp = tmp->next;
        }
        
        tmp = head;
        while(tmp)
        {
            if(tmp->val != s.top())
                return false;
            tmp = tmp->next;
            s.pop();
        }
        return true;
    }
};
```

## Reverse the first half
```cpp
class Solution {
public:
    bool isPalindrome(ListNode* head) {
        //  fast = 2*slow
        ListNode *slow, *fast, *prev = NULL, *temp;
        slow = fast = head;
        
        while(fast && fast->next)
        {
            // find the end, move 2X speed
            // so we can reverse the half the elements
            fast = fast->next->next;
            
            temp = slow->next;
            slow->next = prev;
            prev = slow;
            slow = temp;
        }
        
        // if the length is odd
        // slow will be in the middle element
        // we don't care about the middle element in palindrome
        // so move one step further
        if(fast)
            slow = slow->next;
        
        // now the slow will be at second half
        // prev will be start of reversed list
        while(prev && prev->val == slow->val)
        {
            prev = prev->next;
            slow = slow->next;
        }
        
        // if prev is NULL it reached the end successfully
        if(!prev)
            return true;
        else
            return false;
    }
};
```
