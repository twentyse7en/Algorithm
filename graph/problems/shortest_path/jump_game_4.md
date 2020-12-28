# JUMP GAME 4

[problem statement](https://leetcode.com/problems/jump-game-iv/solution/)

So we have a array and we have to reach the end, there are possible 
transition given. At first I had no idea if this is a graph problem. Without that
It is kinda hard to get started. I got that idea from the hint :p I did
made the graph from the array and tried bfs for shortest path, but it was 
giving me `TLE`, now I  have no choice other than to look at the discussion

How to Identify the such problem as graph, It is asking for the shortest path (If we blindly guess there could be
DP/Greedy and Graph) and I think we couldn't only predict accuratly after 
doing a lot of problem.

## Implelmentation

<details>
<summary> This got me a `TLE` </summary>

```cpp
class Solution {
public:
    int minJumps(vector<int>& arr) {
        
        int n = arr.size();
        vector<vector<int>> adj_list(n, vector<int>());
        
        unordered_map<int, vector<int>> umap;
        
        for(int i = 0; i < n - 1; ++i)
        {
            adj_list[i].push_back(i+1);
            adj_list[i+1].push_back(i);
        }
        
        for(int i = 0; i < n; ++i)
            umap[arr[i]].push_back(i);
        
        for(auto x: umap)
        {
        // connect
            int size = x.second.size();
            for(int i = 0; i < size -1; ++i)
            {
                for(int j = i + 1; j < size; ++j)
                {
                    adj_list[x.second[i]].push_back(x.second[j]);
                    adj_list[x.second[j]].push_back(x.second[i]);
                }
            }
        }
        
        // now we can do bfs
        vector<int> dist(n, INT_MAX);
        dist[0] = 0;
        queue<int> q;
        q.push(0);
        vector<int> visited(n, 0);
        visited[0] = 0;
        
        while(q.size())
        {
            int size = q.size();
            while(size--)
            {
                int curr = q.front(); q.pop();
                // all adjacents
                for(int neigh: adj_list[curr])
                {
                   if(!visited[neigh]) 
                   {
                       visited[neigh] = 1;
                       q.push(neigh);
                       dist[neigh] = 1 + dist[curr];
                       if(neigh == n - 1)
                           return dist[neigh];
                   }
                }
            }
        }
        
        return dist[n - 1];
    }
};
```

</details>

Let's tweak, Say I first stumble upon traversing the matrix, here to we can
apply a tweak, we can visit the two adjacent neighbours without the adjacency
matrix also for the `arr[i] == arr[j]` we could directly jump using the index
we stored in the vector for each `arr[i]` but It doesn't help us with `TLE`
let's investigate why
and come up with a better solution.

<details>
<summary> Here we improved the representation, no need to create the adjacency matrix,
But we failed at the same testcase as before, why?
</summary>

```cpp
class Solution {
public:
    int minJumps(vector<int>& arr) {
        
        int n = arr.size();
        // store the levels to jump
        unordered_map<int, vector<int>> umap;
        for(int i = 0; i < arr.size(); ++i)    
            umap[arr[i]].push_back(i);
        
        // now we are ready to bfs
        queue<int> q;
        vector<int> visited(n, 0);
        vector<int> dist(n, 0);
        
        q.push(0);
        dist[0] = 0;
        int dir[2] = {-1, 1};
        
        while(q.size())
        {
            int size = q.size(); 
            
            while(size--)
            {
                int curr = q.front(); q.pop();
                visited[curr] = 1;
                printf("node : %d/%d distance : %d\n", curr, arr[curr], dist[curr]);
                
                // visit
                // the adjacent neighbours and then level 
               for(int x: dir) 
               {
                  if(curr + x >= 0 && curr + x < arr.size() && !visited[curr + x]) 
                  {
                      visited[curr + x] = 1;
                      q.push(curr + x);
                      dist[curr + x] = 1 + dist[curr];
                      
                      if(curr + x == arr.size()  - 1)
                          return dist[curr + x];
                  }
               }
                
                // visit the level
                for(int x: umap[arr[curr]])
                {
                    if(!visited[x])
                    {
                       visited[x] = 1; 
                        q.push(x);
                        dist[x] = 1 + dist[curr];
                        
                        if(x == arr.size() - 1)
                            return dist[x];
                    }
                }
                    
            }
            
        }
        
        return dist[arr.size() - 1];
    }
};
```

</details>

If we look into the time complexity of `bfs` it is O(V + E) here `V` = `arr.size()` what about `E` ?
In the test case `[7, 7, 7, 7, 7, 7, 7, 7]` Here the No. of edges are O(V<sup>2</sup>). Thus 
make our bfs O(N<sup>2</sup>), The small tweak we can do is if we visit the 
value 7 for first time, we will put all the values in the queue and mark as 
visited, when we extract other 7 we put into the queue we will loop through
the `umap[7]` this takes O(N) but all the values are already visited, so 
the whole attempt is waste of time. So In order to avoid this we can clear
the `vector` in `umap[7]` after we visit it for first time. Which makes this
O(N) this is very crucial point.

<details> 
<summary> This is the final solution, simple tweak to reduce the code </summary>

```cpp
class Solution {
public:
    int minJumps(vector<int>& arr) {
        
        int n = arr.size();
        // store the levels to jump
        unordered_map<int, vector<int>> umap;
        for(int i = 0; i < arr.size(); ++i)    
            umap[arr[i]].push_back(i);
        
        // now we are ready to bfs
        queue<int> q;
        vector<int> visited(n, 0);
        vector<int> dist(n, 0);
        
        q.push(0);
        dist[0] = 0;
        
        while(q.size())
        {
            int size = q.size(); 
            
            while(size--)
            {
                int curr = q.front(); q.pop();
                visited[curr] = 1;
                
                // visit
                // the adjacent neighbours and then level 
                umap[arr[curr]].push_back(curr + 1);
                umap[arr[curr]].push_back(curr - 1);
                
               for(int x: umap[arr[curr]]) 
               {
                  if(x >= 0 && x < arr.size() && !visited[x]) 
                  {
                      q.push(x);
                      dist[x] = 1 + dist[curr];
                      visited[x] = 1;
                      
                      if(x == arr.size()  - 1)
                          return dist[x];
                  }
               }
                
                // remove the elements
                // crucial part to make this O(N)
                umap[arr[curr]] = {};
                    
            }
            
        }
        
        return dist[arr.size() - 1];
    }
};

```

</details>
