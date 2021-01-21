# Stack Problem patterns

## Monotonically increasing stack
[problem statement](https://leetcode.com/problems/find-the-most-competitive-subsequence/submissions/)    
[credits](https://leetcode.com/problems/find-the-most-competitive-subsequence/discuss/952786/JavaC%2B%2BPython-One-Pass-Stack-Solution)

```cpp
class Solution {
public:
    vector<int> mostCompetitive(vector<int>& nums, int k) {
        // I didn't comeup with the solution.
        // Should have given a bit more time
        // but on a rush
        // ----------------------------------
        //  Monotonically increasing stack
        //-----------------------------------
        vector<int> stack;
        for(int i = 0; i < nums.size(); ++i)
        {
            while(!stack.empty() && stack.back() > nums[i] && (stack.size()-1)+(nums.size()-i)>=k)
                stack.pop_back();
            if(stack.size() < k)
                stack.push_back(nums[i]);
        }
        return stack;
    }
};
```

You can find similar problem at the end of these posts  
[similar problems i](https://leetcode.com/problems/find-the-most-competitive-subsequence/discuss/952786/JavaC%2B%2BPython-One-Pass-Stack-Solution) |
[similar problems ii](https://leetcode.com/problems/find-the-most-competitive-subsequence/discuss/952794/JavaPython-3-1-pass-Monotonic-Stack-w-14-SIMILAR-problems-brief-explanation-and-analysis.)
