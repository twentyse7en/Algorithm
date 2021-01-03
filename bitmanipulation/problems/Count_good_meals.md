# Count good meals

If sum of the no.s is power of 2, it becomes a pair. Naturally we traverse through
whole array to find the next valid pair for all elements. But this is O(N^2). If we
look at the constraints the i/p size is 10^5 so we need somethink less than O(N^2).

I didn't comeup with the solution. We have to use, the constrains to get the idea.
The max val in arr is 2^20 so max sum will 2^21. So we check all possible pair of
D[i], this could take O(22) for n items, this O(22N) but it requires some pruning
to pass in the test case.


I liked the way the possible candidate pair are identified.
```cpp
class Solution {
public:
    int countPairs(vector<int>& D) {
        
        // Similar to Twos sum 
        // But is to check pair in O(1)
        
        unordered_map<int, int> umap;
        int mod = 1e9 + 7;
        sort(D.begin(), D.end());
        int count = 0;
        int m = 0;
        for(int x: D)
        {
           // check all possible pair 
           // highest D[i] is 2^20
           // so highest sum can be 2^21
           for(int i = 0; i <= 21; ++i)
           {
               int k = 1 << i;
            
               // pruning 
               if(k - x > m)
                   break;
            
               count += umap[k - x];
               count %= mod; 
           }
            umap[x]++;
            m = max(m, x);
        }
        return count;
    }
};
```

Extended Solution, I liked the approach, this is exactly what I wanted to implement.

```cpp
class Solution {
public:
    int countPairs(vector<int>& D) {
        
       unordered_map<int, int> umap; 
       long long int res = 0;
       int mod = 1e9 + 7;
        
        for(int x: D)
            umap[x]++;
        
        for(const auto& [k, v] : umap)
        {
            // Like in the prev implementation try all possible pair
            for(int i = 0;  i <= 21; ++i)
            {
                int pair = (1 << i) - k;
                
                // This is very cool
                // This avoid (1, 3) , (3, 1) grouping
                // Only once grouped
                if(pair < k)
                    continue;
               
                if(pair == k)
                {
                   res += ((long long)v*(v-1)/2)%mod;
                    
                }
                else if(umap.find(pair) != umap.end())
                {
                    res += (umap[pair] * (long long)v)%mod;
                }
            }
        }
        
        return res%mod;
    }
};
```
