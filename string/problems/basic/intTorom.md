# 12. Integer to Roman

[link](https://leetcode.com/problems/integer-to-roman/)

## Solution

```cpp
class Solution {
public:
    string intToRoman(int num) {
        if(num < 1 || num > 3999)
            return ""; 
        int arr[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
        vector<string> val = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
        
        int i = 0;
        string s;
        while(num > 0)
        {
            while(num >= arr[i])
            {
                s.append(val[i]);
                num -= arr[i];
            }
            i++;
        }
        return s;
    }
};
```
