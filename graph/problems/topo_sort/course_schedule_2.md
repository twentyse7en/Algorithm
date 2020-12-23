# Course Schedule ii

[problem statement](https://leetcode.com/problems/course-schedule-ii/submissions/)
Staight forward toposort with loop detection

## Implementation

```cpp
class Solution {
public:
    bool dfs(vector<vector<int>>& graph, int curr_vertex, vector<int>& visited, vector<int>& order)
    {
        
        if(visited[curr_vertex] == -1)
            return false;
        
        if(visited[curr_vertex] == 1)
            return true;
        
        // visiting for first time, put on processing
        visited[curr_vertex] = -1;
        
        // visited all the neighbors
        for(int x: graph[curr_vertex])
            if(!dfs(graph, x, visited, order))
               return false;
        
        // mark as processed
        visited[curr_vertex] = 1;
        order.push_back(curr_vertex);
        return true;
            
    }
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        // there should not be any cycle
        // we can use the inverse of full dfs as toposort
        
        vector<vector<int>> graph(numCourses, vector<int>());
        vector<int> visited(numCourses, 0);
        vector<int> order;
        
        // create the graph
        for(vector<int> edge: prerequisites)
            graph[edge[1]].push_back(edge[0]);
        
        // do full dfs
        for(int i = 0; i < numCourses; ++i)
            if(!dfs(graph, i, visited, order))
                return vector<int>();
        
        // reverse the order
        reverse(order.begin(), order.end());
        return order;
        
    }
};
```
