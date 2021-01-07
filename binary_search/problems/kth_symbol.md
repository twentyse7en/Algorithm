#  K-th Symbol in Grammar
[problem statement](https://leetcode.com/problems/k-th-symbol-in-grammar/)

If you think about such questions, this is very similar to pascal's triangle.
Important take way time complexity.   
If base case was `N==0` then definetly we have to traverse O(N), but if we look
at the K, it's reducing by half in each step. But when we reach `K==1` we know
that only possible value is `0` but still we check untill `N = 0`, so update
the base `k==1` then we can reduce the TC to `O(logK)`

## Implementation

```cpp
class Solution {
public:
    int findKthPositive(vector<int>& arr, int k) {
        int l = 0;
        int r = arr.size() - 1;
        
        if(arr.size() == 0)
            return k;
       int m; 
        while(l <= r)
        {
           m = (l + r) / 2;
           // find the missing point till this point
           if(arr[m] - m - 1 < k)
           {
               // this could be valid solution
               // but look for even better solution
               l = m + 1;
           }
           else{
               // look on left side
               r = m - 1;
           }
        }
        
        // know we have the lower bound
        // till m there are a[m] - i - 1 missing points
        // a[m] + k - (a[m] - m - 1)
        // k + m + 1 
        // k + l 
        return k + l;
    }
};
```
