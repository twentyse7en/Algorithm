# Height of binary Tree

It is actual the maximum no. of nodes in the path. *Actual height* is 
the no. of edges in the path.

```cpp
class Solution {
public:
    int maxDepth(TreeNode* root) {
        
        // Base case
        if(root == NULL)
            return 0;
        
        // Hypothesis 
        // solve the left subtree
        // solve the right substree
        int left = maxDepth(root->left);
        int right = maxDepth(root->right);
        
        // Induction
        return 1 + max(left, right);
    }
};
```
