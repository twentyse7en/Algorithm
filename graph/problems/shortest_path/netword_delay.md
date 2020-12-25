# NETWORK DELAY

[Problem statement](https://leetcode.com/problems/network-delay-time/solution/)

## IMPLEMENTATION

```cpp
class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int N, int K) {
        if(N == 1)
            return 0;
        
        // data is in form of edgelist convert it to adjacency
        using pii = pair<int, int>;
        vector<vector<pii>> adj_list(N+1, vector<pii>());
        for(vector<int> time: times)
            adj_list[time[0]].push_back({time[1], time[2]});
        
        vector<int> dist(N+1, INT_MAX);
        priority_queue<pii, vector<pii>, greater<pii>> pq;
        
        pq.push({K, 0});
        dist[K] = 0;
        
        while(!pq.empty())
        {
            int curr_vertex = pq.top().first;
            int dist_vertex = pq.top().second;
            pq.pop();
            
            // check if duplicate
            if(dist[curr_vertex] != dist_vertex)
                continue;
            
            // relax the neighbours
            for(pii neigh: adj_list[curr_vertex])
            {
                int to = neigh.first;
                int conn_dist = neigh.second;
                if(dist[to] > dist_vertex + conn_dist)
                {
                    // update
                    dist[to] = dist_vertex + conn_dist;
                    // add to queue
                    pq.push({to, dist[to]});
                }
            }
                
        }
        
     int res = -1;
        
     for(int i = 1; i < N+1; ++i)
     {
         if(dist[i] == INT_MAX)
             return -1;
         res = max(res, dist[i]);
     }
        
     return res;   
    }
};
```

```cpp
class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int N, int K) {
        //  It's edge list for Bellman-ford we don't need to change it
        // anyway it is given weights are positive stil completely implement
        // Bellman-Ford
        vector<int> dist(N+1, INT_MAX);
        // 1 - indexing
        // # Note: don't forget this for 1-indexing
        dist[0] = 0;
        dist[K] = 0;
        int res = 0;
        
        int flag;
        // for n-1 times relax
        // on Nth we check if there is any change
        // #NOTE: dont forget we looping N times
        for(int i = 0; i < N; ++i)
        {
            flag = 0;
            // relax all the edges
            for(vector<int> edge: times)
            {
                int  from = edge[0];
                int to = edge[1];
                int w = edge[2];
                if(dist[from] != INT_MAX && dist[to] > dist[from] + w)
                {
                    dist[to] = dist[from] + w;
                    flag = 1;
                }
            }
            
            // no update
            if(!flag)
                break;
        }
        
        // this unnecessary in this problem
        if(flag)
            return -1;
        
         for(int x: dist) 
              res = max(res, x);
            
         return res == INT_MAX? -1: res;
    }
};
```
## COMPLEXITY

Dijkstra: PQ used so O((V + E)\*log V)

