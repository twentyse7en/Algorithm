# 1734. Decode XORed Permutation

[problem statement](https://leetcode.com/problems/decode-xored-permutation/)

## Soltution.
[thread](https://leetcode.com/problems/decode-xored-permutation/discuss/1031069/Clean-Python-3-O(N))    
Get start element by xor all pairs we can obtained in encoded list, and xor from 1 to len(encoded) + 1.

For example, original [2, 4, 1, 5, 3]:
After iterating encoded list, we have 2 ^ 4, 2 ^ 1, 2 ^ 5, 2 ^ 3 in hand.
And we can get 1 ^ 2 ^ 3 ^ 4 ^ 5 by problem definition.
So (2 ^ 4) ^ (2 ^ 1) ^ (2 ^ 5) ^ (2 ^ 3) ^ (1 ^ 2 ^ 3 ^ 4 ^ 5) = 2, which is the start element.

Time: O(N)
Space: O(N) for output

```cpp
class Solution {
public:
    vector<int> decode(vector<int>& encoded) {
        // should practice xor more
        // it's actually not that bad
        // another key point is that it's odd no.
        // That's actually a good hint
        
        // #NOTE: You can't understand anything by looking
        // at the code, just read the solution by @lenchen1112

        for(int i = 1; i < encoded.size(); ++i)
            encoded[i] ^= encoded[i-1];
        
        int k = 0;
        for(int x: encoded)
            k ^= x;
        
        int all = 0;
        for(int i = 1; i <= encoded.size()+1; ++i)
            all ^= i; 
        
        vector<int> res;
        int first = all ^ k;
        res.push_back(first);
        for(int x: encoded)
            res.push_back(x^first);
        return res;
    }
};
```
