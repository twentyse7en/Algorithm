# Next Greater element

Another problem which can be solved elegently with
monotonically increasing stack.

# Approach 1

According to constrains O(n^2) was fine.

```cpp
class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        unordered_map<int, int> hm;
        
        for(int i = 0; i < nums2.size(); ++i)
            hm[nums2[i]] = i;
        
        vector<int> res;
        for(int x: nums1)
        {
            int pos = hm[x];
            int tmp = -1;
            for(int i = pos+1; i < nums2.size(); ++i)
            {
                if(nums2[i] > x)
                {
                    tmp = nums2[i];
                    break;
                }
            }
            res.push_back(tmp);
        }
        return res;
    }
};
```

# Approach 2

Way cooler answer. 

Key observation:
Suppose we have a decreasing sequence followed by a greater number
For example [5, 4, 3, 2, 1, 6] then the greater number 6 is the next greater
element for all previous numbers in the sequence

We use a stack to keep a decreasing sub-sequence, whenever we see a number x
greater than stack.peek() we pop all elements less than x and for all the popped ones,
their next greater element is x

For example [9, 8, 7, 3, 2, 1, 6]
The stack will first contain [9, 8, 7, 3, 2, 1] and then we see 6 which is greater
than 1 so we pop 1 2 3 whose next greater element should be 6

*time & space* : O(N)

```cpp
class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        unordered_map<int, int> hm;
        stack<int> s;
        for(int x: nums2)
        {
            while(s.size() && s.top() < x)
            {
                hm[s.top()] = x;
                s.pop();
            }
            s.push(x);
        }
        
        vector<int> res;
        for(int x: nums1)
        {
            if(hm.find(x) != hm.end())
                res.push_back(hm[x]);
            else
                res.push_back(-1);
        }
        
        return res;
    }
};
```
