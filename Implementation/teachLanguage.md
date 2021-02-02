# 1733. Minimum Number of People to Teach

I was confused if this was a graph problem. I noticed it allows O(n^3), that is
a hint suggesting bruteforce, non-graph solution.



```cpp
class Solution {
public:
    int minimumTeachings(int n, vector<vector<int>>& l, vector<vector<int>>& f) {
        // constraint is 500
        // so we can try upto n^3
        // let's try all languages
        
        // for checking if a language exist
        unordered_map<int, unordered_set<int>> hm;
        for(int i = 0; i < l.size(); ++i)
        {
           hm[i+1] = unordered_set<int>();
           for(int x: l[i]) 
               hm[i+1].insert(x);
        }
        
        // if they can already communicate we don't 
        // need to teach new language
        vector<int> alreadyCan(f.size(), 0);
        for(int i = 0; i < f.size(); ++i)
            for(int j = 1; j <= n; ++j)
            {
                int first = f[i][0];
                int second = f[i][1];
                if(hm[first].find(j) != hm[first].end() && hm[second].find(j) != hm[second].end())
                    alreadyCan[i] = 1;
            }
        
        int res = INT_MAX;
        for(int i = 1; i <= n; ++i)
        {
            
            unordered_set<int> hs; 
            for(int j = 0; j < f.size(); ++j)
            {
                if(alreadyCan[j])
                    continue;
                // if language already exist then don't teach
                int first = f[j][0];
                int second = f[j][1];
                if(hm[first].find(i) == hm[first].end()) 
                    hs.insert(first); 
                
                if(hm[second].find(i) == hm[second].end()) 
                    hs.insert(second);
                    
            }
            if(hs.size() < res)
                res = hs.size();
        }
        
        return res;
    }
};
```
