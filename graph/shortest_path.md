# Shortest Path

One of the most important topic in graph

## Contents
 - [DAG Relaxation]()
 - [Dijkstra]()
 - [Bellman-ford]()
 
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


## Bellman-Ford

Hurray!! now we can solve graph containing negative weights. However, if the graph contains a negative cycle, then, clearly, the shortest path to some vertices may not exist (due to the fact that the weight of the shortest path must be equal to minus infinity). We can modify the Bellman-Ford to get negative cycle.

**How this works** : Consider there is no negative cycle. We will create an array of distances d[0…n−1], which after execution of the algorithm will contain the answer to the problem. In the beginning we fill it as follows: d[v]=0, and all other elements d[] equal to infinity ∞.

The algorithm consists of several phases. Each phase scans through all edges of the graph, and the algorithm tries to produce relaxation along each edge (a,b) having weight c. Relaxation along the edges is an attempt to improve the value d[b] using value d[a]+c. In fact, it means that we are trying to improve the answer for this vertex using edge (a,b) and current response for vertex a.

It is claimed that n−1 phases of the algorithm are sufficient to correctly calculate the lengths of all shortest paths in the graph.

*Why n-1 ?*
Because the maximum path length will be n-1 for n vertex.

*How this differ from Dijkstra ?*
Dijkstra is **greedy** If we select min value in a round, It sure that no other path could exist smaller than this. But if the path contain
-ve weights there could be a different path that could outperform the small one right now. In Bellman-ford we try all the path that exist for that vertex from source that way we
are sure about shortest path, It follows **DP**.

*What happens with negative cycles?*
It will still relax after n-1 round, which is contradiction to our earlier statement. There should not be path with n-1 edges.

<img src="https://user-images.githubusercontent.com/59721339/103064578-54091300-45da-11eb-8122-7aaa9a1df654.png" align="center" />

**Implementation**
Unlike other graph algorithm we don't need adjacency  list or matrix. Simple 
edge list will do the work.

<details>
 <summary>
  Simple implementation for no negative cycle
 </summary>
 
```cpp
// for assuming no-negative cycle

struct edge
{
    int a, b, cost;
};

int n, m, v;
vector<edge> e;
const int INF = 1000000000;

void solve()
{
    vector<int> d (n, INF);
    d[v] = 0;
    // loop n-1 times
    for (int i=0; i<n-1; ++i)
        // for all the edges in edge list
        for (int j=0; j<m; ++j) 
            if (d[e[j].a] < INF)
                d[e[j].b] = min (d[e[j].b], d[e[j].a] + e[j].cost);
    // display d, for example, on the screen
}
```

 </details>
 
 <details>
 <summary>
  Added simple optimization and way to get parent (still wil not report negative cycle)
 </summary>
 
```cpp
\\ improvement : sometimes we don't need n-1 loop, if there is no relaxation
\\ we can stop.
\\ added way to recover the parent.

void solve()
{
    vector<int> d (n, INF);
    d[v] = 0;
    vector<int> p (n, -1);

    for (;;)
    {
        bool any = false;
        for (int j = 0; j < m; ++j)
            if (d[e[j].a] < INF)
                if (d[e[j].b] > d[e[j].a] + e[j].cost)
                {
                    d[e[j].b] = d[e[j].a] + e[j].cost;
                    p[e[j].b] = e[j].a;
                    any = true;
                }
        if (!any)  break;
    }

    if (d[t] == INF)
        cout << "No path from " << v << " to " << t << ".";
    else
    {
        vector<int> path;
        for (int cur = t; cur != -1; cur = p[cur])
            path.push_back (cur);
        reverse (path.begin(), path.end());

        cout << "Path from " << v << " to " << t << ": ";
        for (size_t i=0; i<path.size(); ++i)
            cout << path[i] << ' ';
    }
}
```
</details>

<details>
 <summary>
  To check for negative cycle we need a extra relaxation, we there is relaxation in last round, then there is negative cycle. To retrieve the negative cycle, it is sufficient to remember the last vertex x for which there was a relaxation in nth phase. This vertex will either lie in a negative weight cycle, or is reachable from it. To get the vertices that are guaranteed to lie in a negative cycle, starting from the vertex x, pass through to the predecessors n times. Hence we will get the vertex y, namely the vertex in the cycle earliest reachable from source. We have to go from this vertex, through the predecessors, until we get back to the same vertex y (and it will happen, because relaxation in a negative weight cycle occur in a circular manner).
 </summary>
 
 ```cpp
 void solve()
{
    vector<int> d (n, INF);
    d[v] = 0;
    vector<int> p (n - 1);
    int x;
    for (int i=0; i<n; ++i)
    {
        x = -1;
        for (int j=0; j<m; ++j)
            if (d[e[j].a] < INF)
                if (d[e[j].b] > d[e[j].a] + e[j].cost)
                {
                    d[e[j].b] = max (-INF, d[e[j].a] + e[j].cost);
                    p[e[j].b] = e[j].a;
                    x = e[j].b;
                }
    }

    if (x == -1)
        cout << "No negative cycle from " << v;
    else
    {
        // the last node may or mayn't be in the negative cycle.
        // the neihbours of vertex in negtive cycle also get relaxed.
        // so we loop backward to make sure we are in negative cycle.
        int y = x;
        for (int i=0; i<n; ++i)
            y = p[y];
        
        // now we can start from y and stop when we see y.
        vector<int> path;
        for (int cur=y; ; cur=p[cur])
        {
            path.push_back (cur);
            if (cur == y && path.size() > 1)
                break;
        }
        reverse (path.begin(), path.end());

        cout << "Negative cycle: ";
        for (size_t i=0; i<path.size(); ++i)
            cout << path[i] << ' ';
    }
}

 ```
 
</details>

## Complexity
Time complexity : O(|V| (|V| + |E|)) (This is for adjacency list, may be O(V\*E) for edge list)
Space complexity : O(|V|)

## Further Read
There is even optimised version of Bellman-Ford, visit [source](https://cp-algorithms.com/graph/bellman_ford.html)
