# 1657. Determine if Two Strings Are Close

[problem statement](https://leetcode.com/problems/determine-if-two-strings-are-close/)

## Approach 1

*time complexity* : It might look `nlogn` but the maximum length of vector is 
26. So it can be treated as a constant. So `O(n)`

class Solution {
public:
    bool closeStrings(string word1, string word2) {
        if(word1.size() != word2.size())
            return false;
        
        int n = word1.size();
        
        vector<int> freq1, freq2;
        vector<char> f1, f2;
        unordered_map<char, int> hm1, hm2;
        for(int i = 0; i < n; ++i)
        {
            hm1[word1[i]]++;
            hm2[word2[i]]++;
        }
        
        for(auto& x: hm1)
        {
            f1.push_back(x.first); 
            freq1.push_back(x.second);
        }
        
        for(auto& x: hm2)
        {
            f2.push_back(x.first);
            freq2.push_back(x.second);
        }
        
        sort(freq1.begin(), freq1.end());
        sort(freq2.begin(), freq2.end());
        sort(f1.begin(), f1.end());
        sort(f2.begin(), f2.end());
        
        for(int i = 0; i < freq1.size(); ++i)
            if(freq1[i] != freq2[i] || f1[i] != f2[i])
                return false;
                
        return true;
    }

## Approach 2

We aren't improving the time complexity, but reduce the amount  of lines

```cpp
class Solution {
public:
    bool closeStrings(string word1, string word2) {
        if(word1.size() != word2.size())
            return false;
        // for freq
        // check exist
        vector<int> freq1(26, 0), freq2(26, 0), arr1(26, 0), arr2(26, 0);
        for(char c: word1) 
        {
            freq1[c-'a']++;
            arr1[c-'a'] = 1;
        }
        
        for(char c: word2)
        {
            freq2[c-'a']++;
            arr2[c-'a'] = 1;
        }
        
        sort(freq1.begin(), freq1.end());
        sort(freq2.begin(), freq2.end());
         
        // check if they have the same chars
        for(int i = 0; i < 26; ++i)
            if(freq1[i] != freq2[i] || arr1[i] != arr2[i])
                return false;
        
       return true;     
    }
};
```
