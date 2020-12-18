# Increasing Triplet Subsequence

This is a good problems, for solving this efficiently we need a new tool in
out box.

<p>
We keep track of the lower bound and upper bound. This is good way to think 
because we can do hashing, may be this is two pointer.
</p>

```cpp

// commenting by bruteforce solution
// feels like O(n) for bruteforce


class Solution {
public:
    bool increasingTriplet(vector<int>& nums) {
//         int size = nums.size();
//         if(size < 3) return false;
        
//         for(int i = 0; i < size - 2; ++i)
//         {
//             for(int j = i+1; j < size - 1; ++j)
//             if(nums[i] < nums[j])
//             {
//                 for(int k = j + 1; k < size; ++k)
//                     if(nums[j] < nums[k])
//                 {
//                     return true;
//                 }
//             }
//         }
//         return false;


// O(n) solution


        int first = INT_MAX, second = INT_MAX;
        
        for(int n: nums)
        {
            if(n <= first) first = n;
            else if(n <= second) second = n;
            else return true;
        }
        return false;
    }
};
```

This post explains how to think about this [solution](https://leetcode.com/problems/increasing-triplet-subsequence/discuss/79053/My-way-to-approach-such-a-problem.-How-to-think-about-it-Explanation-of-my-think-flow.).
