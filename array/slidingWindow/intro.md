# Sliding Window

## How to identify
Problems such as finding longest substring or shortest substring with some contraints are mostly based on sliding window.  

EX: Given an array A of 0s and 1s, we may change up to K values from 0 to 1.
Return the length of the longest (contiguous) subarray that contains only 1s.

Here it is contigous subarray with some constrains, the constrain is that 
we are allowed to have 3 0's, if more than that comes shrink to maintain
the constrain.

```cpp
class Solution {
public:
    int longestOnes(vector<int>& A, int K) {
        // sliding window
        // we expand window for the given condition
        // shrinks when condition is broken
        int count = 0, right, left;
        int res = INT_MIN;
        
        for(right = 0, left = 0; right < A.size(); ++right)
        {
            if(A[right] == 0)
                count++;
            
            // shrink if violates
            while(count > K && left < A.size())
            {
                if(A[left] == 0)
                    count--;
                left++;
            }
            // this could be a valid ans
            res = max(res, right - left + 1);
        }
        
        return res;
    }
};
```

*Bit Hard* This is bit hard to understand.   
**Number of Substrings Containing All Three Characters**
<img src="https://user-images.githubusercontent.com/59721339/104806577-a23abc00-57fe-11eb-97a5-c69116fbbf55.png" />
```cpp
class Solution {
public:
    int numberOfSubstrings(string s) {
        int n = s.size();
        
        vector<int> count(3, 0);
        int res = 0,  ans = 0;
        
        for(int i =0, j=0; i < n; ++i)
        {
            count[s[i] - 'a']++;
            
            // This loop is to find the minimum subarray
            // which satisfy the condition
            // that could be prefix for the previous values
            // ex: "aaabc"
            // "abc", "aabc", "aaabc"
            while(j < n && count[0]&&count[1]&&count[2])
            {
                ans++;
                count[s[j]-'a']--;
                j++;
            }
            
            // ans is never reset
            // ans is updated if min-subarray is found
            // else previous ans
            res += ans;
        }
        return res;
    }
};
```
