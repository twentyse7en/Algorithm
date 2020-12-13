# Clone a graph

Basic traversal and bit hack.

BFS 

```cpp
class Solution {
public:
    Node* cloneGraph(Node* node) {
        
        if(!node) return NULL;
        
        // normal bfs stuff
        unordered_map<Node*, Node*> m;
        queue<Node*> q;
    
        // we push the neighbors afte
        // we create new nodes
        // {} -> creates a empty vector
        Node* root = new Node(node->val, {});
        q.push(node);
        
        // register
        m[node] = root;
        
        while(!q.empty())
        {
            Node* curr = q.front(); q.pop();
            
            for(Node* currNeigh: curr->neighbors)
            {
                if(m.find(currNeigh) == m.end())
                {
                    // create a new node
                    m[currNeigh] = new Node(currNeigh->val, {});
                    q.push(currNeigh);
                }
                // append the fresh node
                m[curr]->neighbors.push_back(m[currNeigh]);
            }
        }
        
        
    return root;
    }
};
```

DFS - recursion

```cpp

class Solution {
    private:
        map<Node*, Node*> m;
    
public:
    void dfs(Node* node)
    {
        // iterate through the neighbors
        for(Node* x: node->neighbors)
        {
            if(m.find(x) == m.end())
            {
                m[x] = new Node(x->val, {});
                dfs(x);
            }
            m[node]->neighbors.push_back(m[x]);
        }
    }
    
    Node* cloneGraph(Node* node) {
        // let's do a basic dfs
        if(!node) return NULL;
        
        m[node] = new Node(node->val, {});
        
        dfs(node);
        
        return m[node];
    }
};
```

## Iterative dfs

Iterative dfs is slower than recursive dfs, I have no idea how this should be true.

```cpp
class Solution {
    private:
        map<Node*, Node*> m;
    
public:
    
    Node* cloneGraph(Node* node) {
        // let's do a basic dfs
        if(!node) return NULL;
        
        m[node] = new Node(node->val, {});
        
        stack<Node*> s;
        int size;
        s.push(node);
        
        while(!s.empty())
        {
            size = s.size();
            while(size--)
            {
                Node* top = s.top(); s.pop();
                reverse(top->neighbors.begin(), top->neighbors.end());
                
                for(Node* curr_neighbor: top->neighbors)
                {
                    // if not visited add it to the stack
                    if(m.find(curr_neighbor) == m.end())
                    {
                        m[curr_neighbor] = new Node(curr_neighbor->val, {});
                        s.push(curr_neighbor);
                    }
                    m[top]->neighbors.push_back(m[curr_neighbor]);
                }
            }
        }
        
        return m[node];
    }
};
```
