# Minimum Spanning Tree

## Index
- [Introduction](https://github.com/twentyse7en/Algorithm-notes/blob/main/graph/minimum_spanning_tree.md#introduction)
- [Properties](https://github.com/twentyse7en/Algorithm-notes/blob/main/graph/minimum_spanning_tree.md#properties)
- [Kruskal's Algorithm](https://github.com/twentyse7en/Algorithm-notes/blob/main/graph/minimum_spanning_tree.md#kruskals-algorithm)

## Introduction

What is a minimum spanning tree ?
Given a weighted undirected graph.
- We want to find a subtree of this graph which connects all vertices (i.e. it is a spanning tree)
- has the least weight (i.e. the sum of weights of all the edges is minimum) of all possible spanning trees.
This spanning tree is called a minimum spanning tree.

<img src="https://raw.githubusercontent.com/e-maxx-eng/e-maxx-eng/master/img/MST_before.png" align="center"/> 
<img src="https://raw.githubusercontent.com/e-maxx-eng/e-maxx-eng/master/img/MST_after.png" align="center"/>

## Properties
- A minimum spanning tree of a graph is unique, if the weight of all the edges are distinct. Otherwise, there may be multiple minimum spanning trees. (Specific algorithms typically output one of the possible minimum spanning trees).
- Minimum spanning tree is also the tree with minimum product of weights of edges. (It can be easily proved by replacing the weights of all edges with their logarithms)
- The maximum spanning tree (spanning tree with the sum of weights of edges being maximum) of a graph can be obtained similarly to that of the minimum spanning tree, by changing the signs of the weights of all the edges to their opposite and then applying any of the minimum spanning tree algorithm.

## Kruskal's Algorithm

Just to note, If we try bruteforce to generate all spanning tree, the no. of 
spanning tree = <sup>|E|</sup>C<sub>|v|</sub> - no. of cycles.

- All the nodes are in isolated, forming single node tree
- Sort edges based on the weights
- Unify edges if ends of the edges belong to different group

(side note: This feels like a application of dsu)

<img src="https://upload.wikimedia.org/wikipedia/commons/5/5c/MST_kruskal_en.gif" align="center" width="300" height="300"/>

Implementation details: 
 - make every vertex a set O(V)
 - Sort the edges O(Elog(E)) / O(Elog(V)) (SIDENOTE: for dense graph, E = V<sup>2</sup> so Log(E) = 2log(V))
 - We iterate through all the edges (in sorted order) and for each edge determine whether the ends belong to different trees (with two find_set calls in O(1) each). Finally, we need to perform the union of the two trees (sets), for which the DSU union_sets function will be called - also in O(1)
 So overall complexity : **O(Elog(V) + E + M)** or **O(Elog(V))**

```cpp
//========== DSU ===============================

vector<int> parent, rank;

void make_set(int v) {
    parent[v] = v;
    rank[v] = 0;
}

int find_set(int v) {
    if (v == parent[v])
        return v;
    return parent[v] = find_set(parent[v]);
}

void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        if (rank[a] < rank[b])
            swap(a, b);
        parent[b] = a;
        if (rank[a] == rank[b])
            rank[a]++;
    }
}

struct Edge {
    int u, v, weight;
    bool operator<(Edge const& other) {
        return weight < other.weight;
    }
};

int n;
vector<Edge> edges;

int cost = 0;
vector<Edge> result;
parent.resize(n);
rank.resize(n);

// ========== DSU =====================================

// create individual set
for (int i = 0; i < n; i++)
    make_set(i);

// Sort the edges
sort(edges.begin(), edges.end());

// iterate through edges
for (Edge e : edges) {
    if (find_set(e.u) != find_set(e.v)) {
        cost += e.weight;
        result.push_back(e);
        union_sets(e.u, e.v);
    }
}
```
[source](https://cp-algorithms.com/graph/mst_kruskal_with_dsu.html)

**TODO**
- Prim's Algorithm
- advantage of one over another
