# Graph

## Thoughts on graph

 When ever I revisit the graph I have to refresh few basic concepts. Without these concepts you can't survive in the world of graph.
 DP is hard but the tools you use for DP is recursion + memo, but for exploring graph you need a even better tool paacck!
 
## Contents
- [Representation](https://github.com/twentyse7en/Algorithm-notes/blob/main/graph/intro.md#representaion)
- [DFS](https://github.com/twentyse7en/Algorithm-notes/blob/main/graph/dfs.md)
- [BFS]()
- [Disjoint set union]()
- [Minimum Spanning Tree]()
- [standard question]()

## Important types of graph

- Undirected graph - no specific direction between vertex
- directed graph - there is direction between vertex
- weighted graphs -  there is weight associated with each graph

### Tree
- undirected graph with no cycles.
- Rooted tree:
 - designated root nodes
 - each edges point away from or towards the root node.

### Directed Acylic Graph

The titles say everything, directed graph with no cycles. It is really important.

### Bipartite Graph

The graph whose vertices can be divided into 2 differen groups u, v , such that every edge connect between u, v.

## Complete Graph

There is unique edge between every pair of nodes. Useful for worst case testing.

**we will see this in detail later**

## Representaion
### Adajacency matrix

<img src="https://user-images.githubusercontent.com/59721339/102005923-b2183980-3d42-11eb-8736-d23014f884bb.png" align="center" />
<img src="https://user-images.githubusercontent.com/59721339/102005937-d07e3500-3d42-11eb-85eb-9056a890861d.png" align="center" />

## Adjacency List

<img src="https://user-images.githubusercontent.com/59721339/102005960-f1468a80-3d42-11eb-8e6f-5979b7a0c94c.png" align="center" />
<img src="https://user-images.githubusercontent.com/59721339/102005963-f6a3d500-3d42-11eb-9d1d-3ad0c726baa0.png" align="center" />

## Edge List


<img src="https://user-images.githubusercontent.com/59721339/102005989-3965ad00-3d43-11eb-8ad1-f321ae134ced.png" align="center" />
<img src="https://user-images.githubusercontent.com/59721339/102005998-539f8b00-3d43-11eb-9386-74d325060d83.png" align="center" />

## End note
It's better to keep my own notes, so there is no need to research again for each time.
