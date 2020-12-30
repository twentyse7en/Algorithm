# Most stones removed with same Row or Column

[problem statement]()

## Desciption

Key observation is that if the stones are connected, we can remove all the
element except one. So we need to find the total no. of connected components

## My Approach 

Each element is represented as (row, col) so it is bit difficult to 
represent the no. to a single integer. But It is already given as a list
so they have a unique index. We can represent them with `index` in the input.

Next how to merge, I grouped them based on the row then column. Union them
accordingly.

*Time complexity* : O(n)
*space complexity* : O(n)

```cpp
class Solution {
public:
    vector<int> parent; 
    vector<int> size_comp;
    
    int find(int x)
    {
        if(x == parent[x]) return x;
        
        parent[x] = find(parent[x]);
        return parent[x];
    }
    
    void unionk(int x, int y)
    {
        x = find(x);     
        y = find(y);
        
        if(x != y)
        {
            if(size_comp[x] < size_comp[y])
                swap(x, y);
            
            parent[y] = x;
            size_comp[x] += size_comp[y];
        }
        
    }
    
    int removeStones(vector<vector<int>>& stones) {
        // asking for no. of disjoint sets
        int size = stones.size();
        parent.resize(size, 0);
        size_comp.resize(size, 1);
        
        for(int i = 0; i < size; ++i)
            parent[i] = i;
        
        unordered_map<int, vector<int>> x_axis, y_axis; 
        
        for(int i = 0; i < size; ++i)
        {
           int x = stones[i][0]; 
           int y = stones[i][1];
           x_axis[x].push_back(i);
           y_axis[y].push_back(i);
        }
        
        // union x axis
        for(auto& x: x_axis)
        {
            for(int i = 0; i < x.second.size() - 1; ++i)
            {
                int k1 = x.second[i];
                int k2 = x.second[i+1];
                
                unionk(k1, k2);
            }
        }
        
        cout<< "x axis completed" << endl;
        
        for(auto& y: y_axis)
        {
            for(int i = 0; i < y.second.size() - 1; ++i)
            {
                int k1 = y.second[i];
                int k2 = y.second[i+1];
                
                unionk(k1, k2);
            }
        }
        
        // push the parent to unordered set and return size
        unordered_set<int> s;
        for(int i = 0; i < size; ++i)
            s.insert(find(i));
        
        return size - s.size();
    }
};
```

## Second Approach

I was curious how people represent their code. So what official solution
does is to use a offset `10000` to distinguish between (x, y). Each (x, y)
will  be 2 entity connected. We can simply union them and check for no. of
parents. But here the space consumed will be much larger.

```cpp
class Solution {
public:
    
    unordered_map<int, int> umap;
    
    int find(int x)
    {
        // make_set compressed
        if(umap.find(x) == umap.end())
            umap[x] = x;
        
        if(umap[x] == x)
            return x;
        
        umap[x] = find(umap[x]);
        return umap[x];
    }
    
    void dsu_union(int x, int y)
    {
        x = find(x);     
        y = find(y);
        
        if(x != y)
            umap[x] = y;
    }
    
    int removeStones(vector<vector<int>>& stones) {
        // offset 10000
        for(vector<int>& stone: stones)
            dsu_union(stone[0], stone[1] + 1e5);
        
        // find no. of connected components
        unordered_set<int> s;
        for(vector<int>& stone: stones)
            s.insert(find(stone[0]));
        
        return stones.size() - s.size();
    }
};
```
