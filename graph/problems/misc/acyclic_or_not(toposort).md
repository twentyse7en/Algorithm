# Acyclic or not (TOPOSORT)

```cpp
// TOPOLOGICAL SORT
// There is two methods 
// 1. dfs 
// 2. Iterative one

// ======================================
// Let's start with dfs
// do full dfs, reverse the order

// THIS IS FOR ACYCLIC GRAPH
// IF CONTAIN CYCLE TRY MODIFIED VERSION

#include<bits/stdc++.h>
using namespace std;


void dfs(vector<vector<int>>& adj, int curr_vertex, vector<int> visited, vector<int> topo_order)
{
    // mark as visited
    visited[curr_vertex] = 1;

    for(int u: adj[curr_vertex])
    {
        if(!visited[u]) dfs(adj, u, visited, topo_order);
    }
}

void solve(vector<vector<int>>& adj)
{
   int n = adj.size();
   vector<int> visited(n, 0);

   vector<int> topo_order;

   for(int i = 0; i < n; ++i)
   {
        if(!visited[i])
            dfs(adj, i, visited, topo_order);
   }

   reverse(topo_order.begin(), topo_order.end());

}


// HERE TOPOORDER IS Not saved but it check acyclic

class Solution {
public:
    bool dfs(vector<vector<int>>& adj, int curr_vertex, vector<int> &visited)
    {
        for(int u: adj[curr_vertex]) 
        {
           if(visited[u] == -1) 
           {
               return false;
           }
           if(visited[u] == 0)
           {
              visited[u] = -1; 
              
               // IMPORTANT, Here I always forget
               if(!dfs(adj, u, visited)) return false;
           }
        }
        
        // mark as complete
        visited[curr_vertex] = 1;   
        
        return true;
    }
    
    bool canFinish(int numCourses, vector<vector<int>>& pre) {
        
        // prerequesties ain't that useful so create a adj list
        vector<vector<int>> adj(numCourses, vector<int>());
        
        for(vector<int> pair: pre)
        {
           adj[pair[1]].push_back(pair[0]); 
        }
        
        // now we can start the dfs
        // 0 - not visited
        // -1 - currently processing
        // 1 - completed
        vector<int> visited(numCourses, 0);
        
        // do full dfs
        for(int i = 0; i < numCourses; ++i)
        {
           if(visited[i] == 0) 
           {
              visited[i] = -1;
               
              if(!dfs(adj, i, visited))
              {
                 return false; 
              }
           }
        }
        
        return true;
    }
};


// Iterative version
// LOGIC:
// the first one to be added should have indegree 0
// add that to topoorder list
// remove this from graph, reduce the indegree
// then repeat the finding the same process

class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        
        // create adjacent matrix
        // store indegree
        vector<int> indegree(numCourses, 0);
        vector<vector<int>> adj(numCourses, vector<int>());
        for(vector<int> pair: prerequisites)
        {
         adj[pair[1]].push_back(pair[0]);
         indegree[pair[0]]++;
        }
        
        queue<int> qvertex;
        for(int i = 0; i < numCourses; ++i)
            if(indegree[i] == 0) qvertex.push(i);
        
        while(qvertex.size())
        {
            int curr = qvertex.front(); qvertex.pop();
            numCourses--;
            
            // do visit a vertex twice ?
            // no, we visit when indegree == 0
            // if another we encounter it again
            // we will reduce the indegree then it will be
            // -ve, so we will n't visit this again.
            for(int u: adj[curr]){
                if(--indegree[u] == 0) qvertex.push(u);
            }
        }
        
        return numCourses == 0;
    }
};

```
