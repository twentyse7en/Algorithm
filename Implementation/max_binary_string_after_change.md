# Max binary string after change

[problem statement](https://leetcode.com/problems/maximum-binary-string-after-change/submissions/)

## My attempt

My direction of thinking was correct but missed a crucial point.
- I came up with the idea of shifting the values to left side then convert
- but couldn't account for `11100`, above idea couldn't work on this.

The key observation is we don't need to touch the initial 1's. `111` they are
good. Only part to take care is the next part `00`.

*Algorithm*
-----------
- After the consecutive 1's move all the 0 to left side.
- we can convert all the 0's expect the last `0`.
- So in conclusion there will be always one `0`, it's position
can be measured using the above method

```cpp
class Solution {
public:
    string maximumBinaryString(string binary) {
        int n = binary.size();
        string res(n, '1');
        
        int count = 0;
        for(char x: binary)
            if(x == '0')
                count++;
        
        // find the position of first zero
        int pos = 0;
        while(pos < n && binary[pos] == '1')
            pos++;
        
        if(pos < n)
            res[pos+count-1] = '0';
        return res;
    }
};
```

## Complexity
Time : O(n)
space : O(n)
