# Diameter of tree

```cpp
class Solution {
public:
    int diameter = 0;
    
    int dfs(TreeNode* root)
    {
        if(root == NULL)
            return 0;

        int left = dfs(root->left);
        int right = dfs(root->right);
        
        // printf("curr %d left %d right %d", root->val, left, right);
        
        
        int curr_max =  left + right;
        diameter = max(diameter, curr_max);
        
        return max(left, right)+1;
        
    }

    int diameterOfBinaryTree(TreeNode* root) {
        diameter = 0;
        dfs(root);
        return diameter;
    }
};
```

# Longest path between node in N-ary tree

Longest path is same as diameter of N-ary tree

```cpp
int dfs(vector<vector<int>>& adj, int curr_node, unordered_map<int, int>& map, int& diameter)
{
    if(adj[curr_node].size() == 0)
        return 1;

    int first = 0;
    int second = 0; 
    int curr;

    for(int nextNode: adj[curr_node])
    {
        curr = dfs(adj, nextNode, map, diameter);
        
        if(curr > first) {
            second = first;
            first = curr;
        }
        else{
            second = max(curr, second);
        }
    }

    // printf("%d %d %d \n", curr_node, first, second);
    diameter = max(diameter, first + second);

    return first + 1; 
}

int Solution::solve(vector<int> &A)
{
    vector<vector<int>> adj(A.size(), vector<int>({}));
    int root;
    for(int i = 0; i < A.size(); ++i)
    {
        if(A[i] == -1)
            root = i;
        else{
            adj[A[i]].push_back(i);
        }
    }

    int diameter = 0;
    unordered_map<int, int> map;

    dfs(adj, root, map, diameter);

    return diameter;
}
```
