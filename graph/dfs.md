# DFS

I'm not yet comfortable with the cpp implementation so will follow the python version

<p>
A depth-first search (DFS) also finds all vertices reachable from s, but does so by searching undiscovered 
vertices as deep as possible before exploring other branches. Instead of exploring
all neighbors of s one after another as in a breadth-first search, depth-first searches as far as possi-
ble from the first neighbor of s before searching any other neighbor of s. Just as with breadth-first
search, depth-first search returns a set of parent pointers for vertices reachable from s in the order
the search discovered them, together forming a DFS tree.
</p>

```py
# Recursion
def dfs_visit(Adj, s, parent=None, order=None):
    if parent is None:
        parent = [None for v in Adj]
        parent[s] = s
        order = []
        
    for v in Adj[s]:                     #for all neighbours of s
        if parent[v] is None:            #if not visted
            parent[v] = s
            dfs_visit(Adj, v, parent, order)   #go in depth recursively
 
    # Note: the node is added after visiting all it's childrens
    order.append(s)                      #So the last element
    print(parent,order)
    return parent, order
```

Let's talk about the complexity
<p>
How fast is depth-first search? A recursive dfs call is performed only when a vertex does not have
a parent pointer, and is given a parent pointer immediately before the recursive call. Thus dfs is
called on each vertex at most once. Further, the amount of work done by each recursive search
from vertex v is proportional to the out-degree deg(v) of v. Thus, the amount of work done by
depth-first search is O( v∈V deg(v)) = O(|E|). Because the parent array returned has length |V |,
depth-first search runs in O(|V | + |E|) time.

<br/> Sum up
<br/> **Time complexity**  : __O(v+e)__ ( o(e) for dfs then o(v) for the parent list )
<br/> **Space complexity** : __O(v+e)__ ( depends on the depth of stack, in worst case O(e) and o(v) for tracking parents)
</p>

With a single dfs you mightn't explore all vertex in the graph for this you have to use full dfs

```py
def full_dfs(Adj):
    parent = [None for v in Adj]
    order = []
    for v in range(len(Adj)):
    if parent[v] is None:
    parent[v] = v
    dfs(Adj, v, parent, order)
    return parent, order
```
## Iterative

**Important stuff**
- we use stack
- reverse the adj list

```py
def dfs_iterative(adj, s):
    parent = [None for _ in adj]
    parent[s] = s
    stack = deque()
    stack.append(s)

    while len(stack) > 0:
        v = stack.pop()
        # if parent[v] is None:
        print(f"LOG: visited {v}")
        # parent[v] = s
        # reversed is required or the adj list will
        # not be processed in order
        for u in reversed(adj[v]):
            if parent[u] is None:
                parent[v] = u
                stack.append(u)
```

## Fundamental questions
- [Number of Islands]()

## Application
- For a weighted graph, DFS traversal of the graph produces the minimum spanning tree and all pair shortest path tree.
- Detecting cycle in a graph 
- Path Finding
- Topological Sorting
- To test if a graph is bipartite
- Finding Strongly Connected Components of a graph
