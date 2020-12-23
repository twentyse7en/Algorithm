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

## COMPLEXITY

PQ used so O((V + E)\*log V)
