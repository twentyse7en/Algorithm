# Longest Increasing subsequence

This is also a good problem. Used patience sort.

```cpp
\\ time: O(nlgn)
\\ space: O(n)



class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int size = nums.size();
        if(size == 0) return 0;
        
        vector<int> buffer;
        buffer.push_back(nums[0]);
        int max = nums[0];
        vector<int>::iterator k;
        
        for(int i = 1; i < size; i++)
        {
            if(nums[i] > max)
            {
                max = nums[i];
                buffer.push_back(max);
            }
            else{
                k =  lower_bound(buffer.begin(), buffer.end(), nums[i]);
                *k = nums[i];
                max = buffer[buffer.size() - 1];
            }
        }
        return buffer.size();
    }
};
```

There is dp solution which is less efficient

// todo
