# Is graph bipartite

<br/>
full dfs or full bfs anything work fine, take special care when returning the bool
```cpp
class Solution {
    
public:
    unordered_map<int, bool> visited;
    
    bool dfs(vector<vector<int>>& graph, int curr_vertex)
    {

        // go through all the adj vector
        for(int x: graph[curr_vertex])
        {
            // if not visited visit
            if(visited.find(x) == visited.end())
            {
               // printf("visiting : %d\n", x);
                // mark opposite
                visited[x] = !visited[curr_vertex];
                
                // NOTE: take care of this
                if(!dfs(graph, x)){
                    return false;
                }
            }
            else
            {
                // already visited so the color should be oppossite
                if(visited[x] == visited[curr_vertex])
                {
                    return false;
                }
            }
        }
        return true;
    }


    bool isBipartite(vector<vector<int>>& graph) {
        // let's do a full dfs
        int no_vertex = graph.size();
        bool status;
        
        for(int i = 0; i < no_vertex; ++i)
        {
            // not visited visit
            if(visited.find(i) == visited.end())
            {
                visited[i] = true;
                status = dfs(graph, i);
                if(!status)
                {
                    break;
                }
            }
        }
        
        return status;
    }
};
```
