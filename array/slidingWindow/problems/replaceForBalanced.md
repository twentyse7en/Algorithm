# 1234. Replace the Substring for Balanced String
[problem statement](https://leetcode.com/problems/replace-the-substring-for-balanced-string/)

```cpp
class Solution {
public:
    int balancedString(string s) {
        unordered_map<char, int> hm;
        for(char c: s)
            hm[c]++;
        
        int n = s.size();
        int k = n/4;
        int res = n;
        
        // the condition
        // we have to reduce the value > n/4
        // so it can be replaced with values with
        // smaller count
        for(int i = 0, j = 0; i < n; ++i)
        {
            hm[s[i]]--;
            
            while(j < n && hm['Q'] <= k && hm['W'] <= k&& hm['E'] <= k&& hm['R'] <= k)
            {
                res = min(res, i - j + 1);
                hm[s[j]]++;
                j++;
            }
        }
        return res;
    }
};
```
