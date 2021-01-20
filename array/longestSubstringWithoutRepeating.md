#  Longest Substring Without Repeating Characters

*Key Ideas*  
- It's substring so it's could be done with the greedy appoarch
- use hashmap to identify if the value is repeating.
- Even it is present it should be inside the **currently considering
substring** This is a edge case I missed and I might again miss.

## Time complexity
space complexity : O(no. of characters)   
time complexity : O(N)

## Code

```cpp
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int res = 0;
        int start = -1;
        unordered_map<char, int> umap;
        for(int i = 0; i < s.size(); ++i)
        {
            char x = s[i];
            // umap[x] >= start don't miss this
            if(umap.find(x) != umap.end() && umap[x] >= start)
                start = umap[x];
            
            umap[x] = i;
            res = max(res, i - start);
        }
        return res;
    }
};
```

