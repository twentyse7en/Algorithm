# Fruits to baskets

Question is bit weird, but it is to find the 
longest array with only two distinct no.s   

[problem statement](https://leetcode.com/problems/fruit-into-baskets/)

```cpp
class Solution {
public:
    int totalFruit(vector<int>& tree) {
        // longest continues sub-array with
        // only two character
        
        unordered_map<int, int> hm;
        int res = 0;
        int n = tree.size(); 
        unordered_set<int> s;
        for(int left = 0, right = 0; right < n; ++right)
        {
           s.insert(tree[right]);
           hm[tree[right]]++;
           if(s.size() > 2 && left <n) 
           {
               // there is an extra value
               hm[tree[left]]--;
               if(hm[tree[left]] == 0)
                   s.erase(tree[left]);
                   
               left++;
           }
           res = max(res, right - left + 1);
        }
        return res;
    }
};
```
