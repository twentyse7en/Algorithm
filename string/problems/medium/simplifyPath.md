# 71. Simplify Path

[link](https://leetcode.com/problems/simplify-path/)

## Python

```python
class Solution:
    def simplifyPath(self, path: str) -> str:
        li = []
        for el in path.split('/'):
            if len(li) and el == "..":
                li.pop()
            if el not in ["", ".", ".."]:   
                li.append(el)
        return "/" + "/".join(li);
```

## C++

```cpp
class Solution {
public:
    string simplifyPath(string path) {
        
        string token;
        vector<string> s;
        stringstream ss(path);
        unordered_set<string> k = {"", ".", ".."};
        while(getline(ss, token, '/'))
        {
           if(s.size() && token == "..") 
               s.pop_back();
           else if(k.find(token) == k.end())    
               s.push_back(token);
        }
       string res = "";
       for(int i = 0; i < s.size(); ++i) 
       {
           res = res + '/' + s[i];
       }
        return res == ""?"/":res;
    }
};
```
