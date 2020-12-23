# Shortest Path

One of the most important topic in graph

## Contents
 - DAG Relaxation
 - Dijkstra
 - Bellman-ford
 
 ## Introduction
 
 If the graph have no weights we can use __bfs__ to find the shortest path between two vertex. The weighted graph is the more general case.
 In weighted graph there could be **negative cycles** in that case shortest path is **undefined**.
  A negative-weight cycle is a path π starting and ending at same vertex with w(π) < 0.
  
  <img src="https://user-images.githubusercontent.com/59721339/102963126-5f8f0800-450e-11eb-9b2f-6bb26f2d692f.png" align="center" />
  
  ## DAG Relaxation
  - For Directed Acyclic Graph
  - weight can be negative
  
  As a general algorithmic paradigm, a **relaxation algorithm** searches for a
solution to an optimization problem by starting with a solution that is not optimal, then iteratively
improves the solution until it becomes an optimal solution to the original problem. In the single
source shortest paths problem, we would like to find the weight δ(s, v) of a shortest path from
source s to each vertex v in a graph. As a starting point, for each vertex v we will initialize an
upper bound estimate d(v) on the shortest path weight from s to v, +∞ for all d(s, v) except
d(s, s) = 0. During the relaxation algorithm, we will repeatedly relax some path estimate d(s, v),
decreasing it toward the true shortest path weight δ(s, v). If ever d(s, v) = δ(s, v), we say that
estimate d(s, v) is fully relaxed. When all shortest path estimates are fully relaxed, we will have
solved the original problem. (This is what we done in 0-1 matrix bfs part, considering all 0's as source and graph was DAG)

```py
def DAG_RELAXATION(Adj, w, s):

  # get the topological order
  _, order = dfs(Adj, s)
  order.reverse()
  
  # intialize the distance matrix
  d = [float('inf') for _ Adj]
  parent = [None for _ in Adj]
  
  d[s], parent[s] = 0, s
  
  # iterate in topo order and relax
  for u in order:
    for v in adj[u]:
      # relax
      if d[v] > d[u] + w[u][v]:
        d[v] = d[u] + w[u][v]
        parent[v] = u
        
  return d, parent
```

__Complexity__ : O( V + E ) `dfs for topo-order`

## Dijkstra

- Any graph but no negative edges

The algorithm is fairly intuitive, though its implementation can be more complicated than that of other shortest path algorithms.
Dijkstra’s algorithm discretizes this continuous process by repeatedly relaxing edges from
a vertex whose minimum weight path estimate is smallest among vertices whose out-going edges
have not yet been relaxed(greedy). In order to efficiently find the smallest minimum weight path estimate,
Dijkstra’s algorithm is often presented in terms of a minimum priority queue data structure. Dijk-
stra’s running time then depends on how efficiently the priority queue can perform its supported
operations.

<img src="https://user-images.githubusercontent.com/59721339/102968910-b8fd3400-451a-11eb-8223-547a30fe836b.png" align="center" />

Every time it take the minimum distance (remove it from the list as it is solved) and relax out going edges. The complexity lies on
taking the minimum distance and relaxing the out going edges.

### Priority queue
We need three operation
- `insert(val, key)`
- `extract_min()`
- `decrease_key(val, new_key)`

#### Hash table
- O(1) for `insert` and `decrease_key`
- O(v) for `extract_min`

Thus the complexity become : __O(V^2 + E)__ <br/>
This is great for dense graph as E = V^2 and this implementation is linear.

### Binary Heap
- all operation in O(log(v)) (Implementation in MIT 6.006)
- TODO: add implementaton

This makes the complexity :  __O(Vlog(v) + Elog(v))__

### Fibonnacci Heap
For graphs in between sparse and dense, there is an even
more sophisticated priority queue implementation using a data structure called a Fibonacci Heap,
which supports amortized O(1) time insertion and decrease-key operations, along with O(log n)
minimum extraction.


Complexity: __O(|V| log |V| + |E|)__

Why does dijkstra fail in negative weights?

Because it is greedy. Detailed [explanation](https://stackoverflow.com/questions/6799172/negative-weights-using-dijkstras-algorithm/6799344#6799344)

### Implementation

[Dense](https://cp-algorithms.com/graph/dijkstra.html) | 
[Sparse](https://cp-algorithms.com/graph/dijkstra_sparse.html)

<details>
 <summary> Dense </summary>
 
```cpp
 const int INF = 1000000000;
 // adjacent list representation
 vector<vector<pair<int, int>>> adj;

void dijkstra(int s, vector<int> & d, vector<int> & p) {

    int n = adj.size();
    d.assign(n, INF); // distance
    p.assign(n, -1);  // parent
    vector<bool> u(n, false); // mark visited

    d[s] = 0;
    for (int i = 0; i < n; i++) {
    
        // for finding the unvisited minmum distance
        int v = -1;
        for (int j = 0; j < n; j++) {
            if (!u[j] && (v == -1 || d[j] < d[v]))
                v = j;
        }

        // we can stop
        if (d[v] == INF)
            break;
            
        // mark as visited
        u[v] = true;
        
        
        for (auto edge : adj[v]) {
            int to = edge.first;
            int len = edge.second;
            
            // relax
            if (d[v] + len < d[to]) {
                d[to] = d[v] + len;
                p[to] = v;
            }
        }
    }
}

 ```
 
 For Retrieving path
 
 ```cpp
 vector<int> restore_path(int s, int t, vector<int> const& p) {
    vector<int> path;

    for (int v = t; v != s; v = p[v])
        path.push_back(v);
    path.push_back(s);

    reverse(path.begin(), path.end());
    return path;
}
 ```
 
</details>


<details>
 <summary>
  For sparse graph
 </summary>
 
  __NOTE__: There is no `decrease_key()` instead we add the duplicates(updated values). We immideatly update the distace[] if the value of in priority_queue
 doesn't match with the distance, then it's a duplicate
 
 ```cpp
 
const int INF = 1000000000;
vector<vector<pair<int, int>>> adj;

void dijkstra(int s, vector<int> & d, vector<int> & p) {

    int n = adj.size();
    
    // initializing
    d.assign(n, INF);
    p.assign(n, -1);
    
    // mark source as 0
    d[s] = 0;
    
    using pii = pair<int, int>;
    // priority_queue is default max_heap little hack to make min_heap (BTW it only store pii)
    priority_queue<pii, vector<pii>, greater<pii>> q;
    q.push({0, s}); // push the source node
    
    while (!q.empty()) {
    
        int v = q.top().second;
        int d_v = q.top().first;
        q.pop();
        
        // to handle duplicates
        if (d_v != d[v])
            continue;

        for (auto edge : adj[v]) {
            int to = edge.first;
            int len = edge.second;

            if (d[v] + len < d[to]) {
                d[to] = d[v] + len;
                p[to] = v;
                
                // we don't decrease the key
                // But add a duplicate with updated values
                q.push({d[to], to});
            }
        }
    }
}
 ```
 
</details>
