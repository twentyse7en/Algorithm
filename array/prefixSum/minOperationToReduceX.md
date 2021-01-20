#  Minimum Operations to Reduce X to Zero

## Intution
- Bruteforce : Use Recursion
- DP : Yep, I tried using 3D dp
- Greedy using prefixSum : this is some kind of subarray sum problem.
So naturaly I should have thought about using prefixSum.

## Approach 1

Cache prefixSum for reverse of array.   
*Time & Space* : O(N)
```cpp
class Solution {
public:
    int minOperations(vector<int>& nums, int x) {
        unordered_map<int, int> umap;
        int n = nums.size();
        int tmp = 0;
        for(int i = n-1; i >= 0; --i)
        {
            tmp+=nums[i];
            umap[tmp] = i;
        }
        tmp = 0; 
        int res = INT_MAX;
        
        if(umap.find(x) != umap.end())
            res = min(res, n - umap[x]);
        
        for(int i = 0; i < n; ++i)
        {
            tmp += nums[i];
            // check if left alone is needed
            if(tmp == x)
                res = min(res, i+1);
            //  else we need subarray from right
            else if(umap.find(x - tmp) != umap.end()) 
            {
                int right = umap[x-tmp];
                if(right > i)
                    res = min(res, i+1+ n - right);
            }
        }
        return res == INT_MAX ? -1 : res;    
    }
};
```

## Approach 2
This Approach felt way powerful, this combaines prefixSumArray + hashtable for
faster seach of window size.   
[ref1](https://leetcode.com/problems/minimum-operations-to-reduce-x-to-zero/discuss/935935/Java-Detailed-Explanation-O(N)-Prefix-SumMap-Longest-Target-Sub-Array)   
[ref2](https://leetcode.com/problems/minimum-operations-to-reduce-x-to-zero/discuss/1016199/Python-O(n)-solution-using-cumulative-sums)


```cpp 
class Solution {
public:
    int minOperations(vector<int>& nums, int target) {
        // another prespective 
        // instead of left and right
        // find the largest array with TotalSum - x sum
        // Just the complement
        unordered_map<int, int> umap;
        int n = nums.size();
        umap[0] = 0;
        int sum = 0;
        for(int i = 1; i <= n; ++i)
        {
            sum += nums[i-1]; 
            umap[sum] = i;
        }
        
        int remSum = sum - target;
        
        if(remSum < 0) return -1;
        
        sum = 0;
        int res = INT_MIN;
        for(int i = 0; i < n; ++i)
        {
           if(umap.find(sum+remSum) != umap.end()) 
               res = max(res, umap[sum+remSum] - i);
            
           sum += nums[i];
        }
        return res == INT_MIN ? -1 :n - res;
    }
};
```
