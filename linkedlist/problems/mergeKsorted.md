# 23. Merge k Sorted Lists
[problem statement](https://leetcode.com/problems/merge-k-sorted-lists/)

It is marked as `hard` but I think it deserve only medium. Because it shows
same fingerprint of the merge sort, but even easier.

*time complexity* : O(nlogk)
*space complexity* : O(1) // recursion stack not included

```cpp
class Solution {
public:
    ListNode* helper(vector<ListNode*>& li, int start, int end)
    {
        if(start == end)
            return li[start];
        
        // if there is more than two list split
        int mid = (start + end)/2;
        ListNode* left = helper(li, start, mid);
        ListNode* right = helper(li, mid+1, end);
        
        // now we have two nodes merge and return
        ListNode* temp = new ListNode();
        ListNode* sentinal = temp;
        while(left && right)
        {
            if(left->val < right->val)
            {
                temp->next = left;
                temp = temp->next;
                left = left->next;
            }
            else{
                temp->next = right;
                temp = temp->next;
                right = right->next;
            }
        }
        
        while(left)
        {
            temp->next = left;
            left = left->next;
            temp = temp->next;
        }
        while(right)
        {
            temp->next = right;  
            right = right->next;
            temp = temp->next;
        }
        return sentinal->next;
    }
    
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        // divide and conquer
        int n  = lists.size(); 
        if(n == 0)
            return NULL;
        ListNode* sentinal = new ListNode();
        return helper(lists, 0, n-1); 
    }
};
```

