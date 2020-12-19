# Redundunt connection

There should not be no circles.

## Approach

In a vertex both edges should not be in the same set

## Solution

```cpp
class Solution {
public:
    vector<int> parent;
    vector<int> size_comp;
    
    int find(int v)
    {
       if(parent[v] == v)
           return v;
        parent[v] = find(parent[v]);
        return parent[v];
    }
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        int size = edges.size();
        parent.resize(size+1, -1);
        size_comp.resize(size+1, 1);
        
        // makeset
        for(int i = 0; i < size+1; ++i) parent[i] = i;
        
        vector<int> res(2);
        
        for(vector<int> &edge: edges)
        {
           int x = find(edge[0]);
           int y = find(edge[1]);
            
            if(x == y)
            {
                res = edge;
                break;
            }
            
            // rank
            if(size_comp[x] < size_comp[y]) swap(x, y);
            
            parent[y] = x;
            size_comp[x] += size_comp[y];
        }
        
        return res;
        
    }
};
```

## Complexity

time : O(N * alpha(N)) which is nearly equal to O(N); // for more details see DSU
space: O(N)
