# Find the City With the Smallest Number of Neighbors at a Threshold Distance

[problem statement](https://leetcode.com/problems/find-the-city-with-the-smallest-number-of-neighbors-at-a-threshold-distance/)

Find the shortest distance from a vertex and repeat this for all vertex.
AKA *All Pair shortest path*.


## My solution

- Dijkstra for all vertex

```cpp
class Solution {
public:
    typedef pair<int, int> pii;
    int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold) {
       // do dijkstra for all the the vertex 
       vector<vector<pii>> adj(n, vector<pii>());   
       for(vector<int>& edge: edges)
       {
           adj[edge[0]].push_back({edge[1], edge[2]});
           adj[edge[1]].push_back({edge[0], edge[2]});
       }
        
       int res = 0;
       int count = INT_MAX;
       
       // dijkstra for all the vertex
       for(int i = 0; i < n; ++i)
       {
          priority_queue<pii, vector<pii>, greater<pii>> pq; 
          pq.push({i, 0});
          vector<int> dist(n, INT_MAX);
          dist[i] = 0; 
           
          while(pq.size())
          {
              pii curr = pq.top(); pq.pop();
              if(dist[curr.first] != curr.second)
                  continue;
              
              // relax the edges
              for(pii neigh: adj[curr.first])
              {
                  if(dist[neigh.first] > dist[curr.first] + neigh.second)
                  {
                      dist[neigh.first] = dist[curr.first] + neigh.second;
                      pq.push({neigh.first, dist[neigh.first]});
                  }
              }
          }
          // count the values
          int tmp = 0;
           for(int x: dist)
               if( x <= distanceThreshold)
                   tmp++;
           
           
           if(count >= tmp)
           {
               count = tmp;
               res = i;
           }
       }
        
        return res;
    }
};
```

*Time complexity* : O(n*(nlogn + mlogn))
*Space complexity* : O(n + m)

## Way simpler algorithm 

*Floyd Warshall* : This is a straight All pair shortest path question.

*Time Complexity* : O(V<sup>3</sup>)

```cpp
class Solution {
public:
    int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold) {
        
        // create the initial table
        vector<vector<int>> table(n, vector<int>(n, INT_MAX));
        for(int i = 0; i < n; i++) 
            table[i][i] = 0;
        for(vector<int>& edge: edges)
        {
            int u = edge[0];
            int v = edge[1];
            int c = edge[2];
            
            table[u][v] = c;
            table[v][u] = c;
        }
        
        // do floyd-warshall
        for(int k = 0; k < n; ++k)
            for(int u = 0; u < n; ++u)
                for(int v = 0; v < n; ++v)
                    if(table[u][k] != INT_MAX && table[k][v] != INT_MAX)
                        table[u][v] = min(table[u][v], table[u][k]+table[k][v]);
        
        int smallest = n;
        int res = 0;
        
        for(int i = 0; i < n; i++)
        {
            int count = 0;
            for(int x: table[i])
                if(x <= distanceThreshold)
                    count++;
            
            if(count <= smallest)
            {
                smallest = count;
                res = i;
            }
        }
        
        return res;
    }
};
```
