# Maximum erasure value

[leetcode](https://leetcode.com/problems/maximum-erasure-value/)

## Two pointer

Here we keep track of the beginning of the current subarray and if we encounter
a duplicare we delete including the occurence of duplicate of current element 
from start of lhs.

<br />
O(n) as we move only two pointers.


```cpp
class Solution {
public:
    int maximumUniqueSubarray(vector<int>& nums) {
        
        if(nums.size() == 1) return nums[0];
        
        unordered_map<int, int> freq;
        int buffer = 0;
        int res = 0;
        int lhs = 0;
        
        for(int num: nums)
        {
            buffer += num;
            freq[num]++;
            
            // This was my approach

            // if(freq[num] > 1)
            // {
            //     while(nums[lhs] != num)
            //     {
            //         buffer -= nums[lhs];
            //         freq[nums[lhs]]--;
            //         lhs++;
            //     }
            //     buffer -= nums[lhs];
            //     freq[nums[lhs]]--;
            //     lhs++;
            // }
            

            // this kinda a cool
            // delete until the we delete the duplicate

            while(freq[num] > 1)
            {
                buffer -= nums[lhs];
                freq[nums[lhs++]]--;
            }
            
            res = max(res, buffer);
            // cout << buffer << endl;
        }
        return res;
    }
};
```

But this was slow with aroung 500ms while some other solution had 280 ms

## Better approach

I was trying to store num and sum till that, so that we find the a duplicate
we can substruct the current sum and previous sum and continue and I erase the
previous start from map, but we have also store some other elements which are
also inside the map, which isn't right, lemme illustrate

```
[3, 4, 5, 4, 3]

here we can go like this

[3, 4, 5] // when encounter 4 {3: 3, 4:7, 5: 12} state of map;

can we erase only 4, now {3: 3, 5:12} we don't need 3 inside the map

```

Instead we can store prefix array, which can give us the subarray sum O(n) to 
build and O(1) to query and we can store the index for each elements and the
start of the current subarray, we can ignore the duplicate if it's value is
less than the start (because that isn't included in the current subarray)

<br/>

__NOTE: Take special care about initialization__

```cpp
class Solution {
public:
    int maximumUniqueSubarray(vector<int>& nums) {
        // calculate the prefix sum
        vector<int> pre(nums.size()+1, 0);
        for(int i = 0; i < nums.size(); ++i)
            pre[i+1] = pre[i] + nums[i];
        
        // How to use prefix
        // pre[j+1] - pre[i] => for subarray including i to includeing j
        
        // unordered_map<int, int> freq;
        // shifting from map to vector reduced 200ms
        // Don't forget to intialize the array
        vector<int> freq(100001, -1);
        
        // special consideration for start
        // start -1 changes to 0 in first loop
        // every thing else works as expected
        // it took my 1 hrs so take special care
        int start = -1;
        int res = 0;
        for(int i = 0; i < nums.size(); ++i)
        {
            
            if(freq[nums[i]] >= start)
                start = freq[nums[i]] + 1;

            freq[nums[i]] = i;
            res = max(res, pre[i+1] - pre[start]); 
        }
        return res;
    }
};
```
