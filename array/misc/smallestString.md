# 1663. Smallest String With A Given Numeric Value

Actually this sounds easy, and it is but I took
a few minutes to get the code done, which is real 
shame.

# My Approach

*Time Complexity* : O(n)

```cpp
class Solution {
public:
    void helper(string& s, int n, int k)
    {
        if(n == 0)
            return;
        // project the worst case
        int max = n*26;
        if(k < max)
        {
           // we can have value less than 'z' 
           if(max - k >= 26)
           {
               s.push_back('a');
               n--;
               k -= 1;
               helper(s, n, k);
           }
           else{
               int val = k - (n-1)*26;
               s.push_back('a'+val-1);
               n--;
               k -= val;
               helper(s, n, k);
           } 
        }
        else{
            s.push_back('z');
            n--;
            k-=26;
            helper(s, n, k);
        }
        
    }
    
    string getSmallestString(int n, int k) {
       string s;
       helper(s, n, k);
       return s; 
    }
};
```

# A beutiful Approach

* Check how `min` handles the edge case beutifully

```cpp
class Solution {
public:
    string getSmallestString(int n, int k) {
        // fill all 'a'
        // if we have values left
        // partitian largest value from rear part
        string res(n,'a');
        // now the targetSum reduced
        k -= n;
        for(int i = n-1; i >= 0 && k > 0; --i)
        {
            int diff = min(25, k);
            res[i] += diff;
            k -= diff;
        }
        return res;
    }
};
```

# There is a math post
[link](https://leetcode.com/problems/smallest-string-with-a-given-numeric-value/discuss/1038740/Python-O(n)-math-solution-explained)
But that doesn't improve time complexity;
