# DISJOINT SET UNION

This is **very important datastructure** to have in the toolkit, when we solve
a lot of problem we can feel the difference, and it is easy to implement.

## Index

- [Usage]()
- [Api]()

## Usage

- Combine two set.
- Tell which set a element belong to.

## Api
- `make_set(v)` - creates a new set consisting of the new element v
- `union_sets(a, b)` - merges the two specified sets (the set in which the element a is located, and the set in which the element b is located) 
- `find_set(v)` - returns the representative (also called leader) of the set that contains the element v. This representative is an element of its corresponding set. It is selected in each set by the data structure itself (and can change over time, namely after union_sets calls). This representative can be used to check if two elements are part of the same set or not. a and b are exactly in the same set, if find_set(a) == find_set(b). Otherwise they are in different sets.

## Intution

We will store the sets in the form of trees: each tree will correspond to one set. And the root of the tree will be the representative/leader of the set.

<img src="https://raw.githubusercontent.com/e-maxx-eng/e-maxx-eng/master/img/DSU_example.png" align="center" />

## Implementation

### Naive approach

```cpp
void make_set(int v) {
    parent[v] = v;
}

int find_set(int v) {
    if (v == parent[v])
        return v;
    return find_set(parent[v]);
}

void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b)
        parent[b] = a;
}
```

However this implementation is inefficient. It is easy to construct an example, so that the trees degenerate into long chains. In that case each call find_set(v) can take O(n) time. If `find_set()` takes O(n) 
`union` also takes O(n) time. Can we do better ?

**Path Compression** : This optimization is designed for speeding up `find_set`.
If we call `find_set(v)` for some vertex `v`, we actually find the representative `p` for all vertices that we visit on the path between `v` and the actual representative `p`. The trick is to make the paths for all those nodes shorter, by setting the parent of each visited vertex directly to `p`.

<img src="https://raw.githubusercontent.com/e-maxx-eng/e-maxx-eng/master/img/DSU_path_compression.png" align="center" />

```cpp
int find_set(int v) {
    if (v == parent[v])
        return v;
    return parent[v] = find_set(parent[v]);
}
```

**Union by rank** : When combining to sets, make the big set root of the other.
For this we have to keep rank (no. of elements)

```cpp
void make_set(int v) {
    parent[v] = v;
    size[v] = 1;
}

void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        if (size[a] < size[b])
            swap(a, b);
        parent[b] = a;
        size[a] += size[b];
    }
}
```

If we are doing *union by rank*, without path compression its takes **O(lgn)** 

## Complexity

O(α(N)) approx **O(1)**
*α(N)* : Inverse ackerman function which grows very slowly. Doesn't exceed
4 for all  reasonable N (N < 10<sup>600</sup>)

## Template

```cpp
class Solution {
public:

    // make this global
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
        
        // resize
        parent.resize(size+1, -1);
        size_comp.resize(size+1, 1);
        
        // makeset
        for(int i = 0; i < size+1; ++i) 
            parent[i] = i;
        
        vector<int> res(2);
        
        for(vector<int> &edge: edges)
        {
           int x = find(edge[0]);
           int y = find(edge[1]);
            
            // NOTE: This is specific to problem.
            // =================================
            if(x == y)
            {
                res = edge;
                break;
            }
            // =================================
            
            // rank
            if(size_comp[x] < size_comp[y])
                swap(x, y);
            
            parent[y] = x;
            size_comp[x] += size_comp[y];
        }
        
        return res;
        
    }
};
```

## Todo
- detailed difference b/w dfs and bfs
