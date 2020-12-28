# Cheapest flights within K stops

[problem statement](https://leetcode.com/problems/cheapest-flights-within-k-stops/)

This is really good question.

## My Approach

- There should be K+1 edges, so we assumed that we should relax K+1 edges.
so I ran the `Bellman-Ford` but it miserably failed for the example test case.
`[[0,1,100],[1,2,100],[0,2,500]] src = 0, dst = 2, k = 0`
This is because `Bellman-Ford` gurantees by n-1 times (n = #vertex) that 
shortes path will be found, but this could be found even early.

- I tried bfs, were I won't update the nodes in same level but that ain't 
working because we have to sometimes.(ex:`vertex: 3
edgelist: [[0,1,100],[1,2,100],[0,2,500]]
src: 0
dst: 2
K: 1`)
This getting more interesting.

- I tried dfs, which is actually straight forward simultaion, But I got `TLE`,
So that was my final attempt let's study from the discussion.

## Actual Solution

Turns out there are lot of ways to solve the problems.

- **dfs with pruning**: I extra line to my solution passed the test. If the 
cost is greater the our best solution, don't proceed further. That is basically
what pruning means. But I didn't personally like this solution. How can we
explain the reduced time complexity. But pruning is good to have in our solution.
<details>
<summary> code </summary>

```cpp
class Solution {
public:
    typedef pair<int, int> pii;
    int res = INT_MAX; 
    int dest;
    
    void dfs(vector<vector<pii>>& adj_list, int curr, int depth, int dist, vector<int> visited)
    {
        if(visited[curr] == 1)
            return;
        
        visited[curr] = 1;
        
        if(depth == -1)
            return;
        
        for(pii x: adj_list[curr])
        {
                int new_dist = dist + x.second;
               // printf("node : %d dist: %d dest: %d\n", x.first, new_dist, dest);    
                if(x.first == dest) 
                {
                    res = min(res, new_dist);
                //    printf("New dist: %d | %d\n", dist, new_dist);
                }
                if(res > new_dist)
                    dfs(adj_list, x.first, depth - 1, new_dist, visited);
        }
        
    }
    
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int K) {
        // let's try out dfs
        // we need adjacency list
        dest = dst;
        vector<int> visited(n, 0);
        
        vector<vector<pii>> adj_list(n, vector<pii>());
        for(vector<int> edge: flights)
           adj_list[edge[0]].push_back({edge[1], edge[2]});
        
        dfs(adj_list, src, K, 0, visited);
        
        return res == INT_MAX ? -1 : res;
    }
};
```

</details>

- BFS : The problem in previous bfs and other algorithms were 1 edge relaxtion
might cause inconsistency. If we relax one vertex then path obviously increased.
Sometimes this path may be longer and won't reaches to solution. But there 
was a more costy path with less step. But it couldn't update because the longer
path (with less cost) alreay updated. We didn't encountered this issue in
dfs becaues when we exploring we keep track of the steps and cost at each 
level. No centeralised way to store it. Both BFS and modified Dijkstra 
follows this approach. (That makes it hard to come up with the complexity)

<details>
<summary> I was expecting same time of execution as dfs, but this is much 
faster. dfs: 112ms bfs: 24 ms.
</summary>

```cpp
class Solution {
public:
    typedef pair<int, int> pii;
    
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int K) {
        // BFS 
        // ----------------------------------
        
        // construct the adj_list
        //-----------------------------------
        vector<vector<pii>> adj_list(n, vector<pii>());
        for(auto edge: flights)
            adj_list[edge[0]].push_back({edge[1], edge[2]});
        
        int min_cost = INT_MAX;
        
        // NOTE: Here we need to track of the node and cost
        // steps can be explicitly tracked by the bfs
        queue<pii> q; q.push({src, 0});
        
        int steps = 0;
        while(q.size())
        {
            int size = q.size();
            while(size--)
            {
                pii curr = q.front(); q.pop();
                if(curr.first == dst)
                    min_cost = min(min_cost, curr.second);
                
                // It's not relaxing as we have no central 
                // distance maintaining stuff, we just update
                // if the steps aren't exceed, also the cost
                // less the `min_cost`
                for(pii neigh: adj_list[curr.first])
                {
                    // pruning
                    if(curr.second + neigh.second < min_cost)
                        q.push({neigh.first, neigh.second + curr.second}); // This how we keep multiple distance for same node
                }
            }
            if(steps++ > K) // we need 1 extra loop get the result, if k = 0, first loop it will relax and second loop if extract result.
                break;
        }
        return min_cost == INT_MAX ? -1 : min_cost;
    }
};

```
</details>

Complexity : Popular opinion is this is O(V<sup>2</sup>) (Reason: he Worst case of k is V, since you loop till you reach k steps during visiting each vertex, then the complexity is O(V*K) which is O(V^2).)


- Dijkstra : It is promising as it is a greedy method.

<details>
<summary> It took 60ms </summary>

```cpp
class Solution {
public:
    typedef tuple<int, int, int> ti;
    typedef pair<int, int> pi;
    
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int K) {
        
        vector<vector<pi>> adj_list(n);
        
        for(vector<int>& f: flights)
            adj_list[f[0]].push_back({f[1], f[2]});
        
        priority_queue<ti, vector<ti>, greater<ti>> pq;
        pq.push({0, src, K+1});
        
        while(pq.size())
        {
            int cost, vertex, steps;
            tie(cost, vertex, steps) = pq.top(); pq.pop();
            
            // as the dijkstra is greedy if we encounter
            // the dst this cost is the minimum one
            if(vertex == dst)
                return cost;
            
            // check if we exceeded the steps
            if(!steps)
                continue;
            
            for(pi to: adj_list[vertex])
            {
                pq.push({cost+to.second, to.first, steps-1});
            }
        }
        return -1;
    }
};
```

</details>

This might be due to the priority queue. Time complexity : @DBabichev think it is O(E+(Vk)*log(Vk)), because there will be no more than Vk different elements in our SortedList (Heap) at any moment.

- Bellman-Ford: This exciting because this is very straight forward, this
push us to check exactly Bellman-Ford works, Instead of blindly applying the
code, It better to have a deeper understanding about how it actually work.
Actually BF is space optimised DP (2D to 1D). The problem I was facing was
in a single step there could be multiple relaxation. This should be restricted.
Only one update should take place from previous state. So we store the previous
state and relax from it. This require the knowledge of how exactly BF works.

<details> <summary> code 132ms </summary>

```cpp
class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int K) {
        
        vector<int> prev_state(n, 1e8);
        prev_state[src] = 0;
        
        for(int i = 0; i < K+1; ++i)
        {
            vector<int> curr_state(prev_state);
            for(vector<int> f: flights)
            {
                int from = f[0];
                int to = f[1];
                int cost = f[2];
                
                curr_state[to] = min(curr_state[to], prev_state[from] + cost);
            }
            prev_state = curr_state;
        }
        
        return prev_state[dst] == 1e8 ? -1 : prev_state[dst];
    }
};
```

</details>

## Complexity

I'm not in a right mood to check the complexity. There are lot of conflicts.
[1](https://leetcode.com/problems/cheapest-flights-within-k-stops/discuss/361711/Java-DFSBFSBellman-Ford-Dijkstra's/579871)
