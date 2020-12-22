# Smallest Range 2

[problem statement](https://leetcode.com/problems/smallest-range-ii/)


## How to approach

Bruteforce will be to generate all possible combination.

But as this is array problem we could apply a lot of filter, you might
get a hint that you should increase the smallest values and increase the largest
values, but still have no idea to how to approach.

<br/>
I got this from stack overflow this the core of the  implementation.

- If we are going to increase a value then we should also increase all values on left.
- If we are going to decrease a value then we should also decrease all values on right.

With this obseration we increaes A[i] values and decrease A[i+1] values end check if 
this is optimal. For this we have to know __max__ and __min__.

max : the value recently increased or the big value - k (This could be so large, even after decrese this could be still max)
ex: [2, 4, 90] k = 2
min : opposite to max

now everything is easy.

## Implementation

```cpp
class Solution {
public:
    int smallestRangeII(vector<int>& A, int k) {
        
        sort(A.begin(), A.end());
        int n = A.size();
        
        // if we increase all the values
        int res = A[n - 1] - A[0];
        int diff; 
        
        for(int i = 0 ; i < n - 1; ++i)
        {
            // strategy we increase the first value
            // decrease the second value
            // may be this is the optimal point to that
            
            int a = max(A[i] + k, A[n-1] - k);
            int b = min(A[i+1] - k, A[0] + k);
            res = min(res, a - b) ;
        }
        
        return res;
    }
};
```

## Complexity

time : O(nlgn) // becaue of sorting
space : depends on sorting 
