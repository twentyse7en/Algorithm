# 13. Roman to Interger

[link](https://leetcode.com/problems/roman-to-integer/)

## Approach

```cpp
class Solution {
public:
    int romanToInt(string s) {
        // easy but I would take more time
        int res = 0;
        reverse(s.begin(), s.end());
        for(char c: s)
        {
            switch(c)
            {
                case 'I': res += (res>=5?-1:1); break;
                case 'V': res += 5; break; 
                case 'X': res += (res >= 50?-10:10); break;
                case 'L': res += 50; break;
                case 'C': res += (res >= 500?-100:100); break;
                case 'D': res += 500; break;
                case 'M': res += 1000; break;
            }
        }
        return res;
    }
};
```
