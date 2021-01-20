# QUICK NOTES

## Intro

- Don't provide direct access - `O(N)`
- Adding and removing from front of list is - `O(N)`
- There are actually a lot of edge cases, but we can use some tricks
to solve them easily.

## Structure
```cpp
struct Node{
    Node *next;
    int data;

    Node(int x)
    :data(x), next(NULL)
    {}
}
```

## Check List

- Update the pointers inside the `while` loop
- Do we need sentinal node
- 
## Sentinal node

Some times we need a dummy node at start to avoid edge casee, especially in
all delete operation.
For ex: remove all duplicate  `1->1->1->1` Here we need to remove
all elements and return a null pointer. For convience we add a
extra node at beginning `s->1->1->1->1` and return `s.next` as answer.

## Traversal
```cpp
Node* tmp = head;
while(tmp)
{
    // do what you want

    // update
    tmp = tmp->next;
}
```

## Basic Problems
- [Delete duplicates from unsorted LL](https://practice.geeksforgeeks.org/problems/remove-duplicates-from-an-unsorted-linked-list/1#)
- [Design a linked list](https://leetcode.com/problems/design-linked-list/)
- 

## Patterns
*Two pointer* : There are lot of problems take advantage of this. 
- Keeps a constant distance : [delete kth last element](https://leetcode.com/problems/remove-nth-node-from-end-of-list/)
```cpp
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
       if(head == NULL) 
           return NULL;
       
       ListNode* dummy = new ListNode();
       dummy->next = head;
       // if we need to delete the first one use sentinal
       ListNode* slow = dummy;    
       ListNode* fast = dummy;
       for(int i = 0; i < n; ++i)
       {
           if(fast->next == NULL)
               return head;
           fast = fast->next;
       }
        
       while(fast->next)
       {
           fast = fast->next;
           slow = slow->next;
       }
       slow->next = slow->next->next;
        
        return dummy->next;
    }
};
```

- 2X speed :    
[Palindrome](https://leetcode.com/problems/palindrome-linked-list/submissions/)  Good problem   
[Cycle detection]()
```cpp
class Solution {
public:
    bool hasCycle(ListNode *head) {
        if(head == NULL)
            return false;
        ListNode* slow = head;
        ListNode* fast = head->next;
        while(slow != fast)
        {
            if(fast == NULL || fast->next == NULL)
                return false;
            slow = slow->next;
            fast = fast->next->next;
        }
        return true;
    }
};
```

Finding the middle value/node

```cpp
class Solution {
public:
    bool isPalindrome(ListNode* head) {
        
        // use sentinal
        ListNode* sentinal = new ListNode();
        sentinal->next = head;
        head = sentinal;
       
        //  fast = 2*slow
        ListNode *slow, *fast;
        slow = fast = head;
        while(fast && fast->next)
        {
            printf("slow:%d fast:%d\n", slow->val, fast->val);
            fast = fast->next->next;
            slow = slow->next;
        }
        printf("slow: %d\n", slow->val);
        return false;
    }
};
```

