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
