# Binary Tree

## Index
- Traversal

## Traversal
This  is the fundamental of the tree. You need to traverse. 

**preorder** : 
- visit root
- visit left subtree
- visit right subtree

<details>
<summary> Recursion is trivial </summary>

```cpp
class Solution {
public:
    void preorder(TreeNode* root, vector<int>& res)
    {
        if(root == NULL)
            return;
        
        // visit the root
        res.push_back(root->val);
        // visit the left
        preorder(root->left, res);
        // visit the right
        preorder(root->right, res);
        
    }
        
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> res;
        preorder(root, res);
        return res;
    }
};
```

</details>

<details> 
<summary>
Iterative, just think how recursion stack is constructed 
</summary>

```cpp
class Solution {
    public:
        vector<int> preorderTraversal(TreeNode* root) {
            vector<int> res;

            if(root == NULL)
                return res;

            stack<TreeNode*> s;
            s.push(root);

            while(s.size())
            {
                TreeNode* curr = s.top(); s.pop();
                res.push_back(curr->val);
                if(curr->right)
                    s.push(curr->right);
                if(curr->left)
                    s.push(curr->left);
            }
            return res;
        }
};
```

</details>

**Inorder** 
- visit left subtree
- visit root
- visit right subtree

<details> 
    <summary>
       Recursion 
    </summary>

```cpp
class Solution {
public:
    void inorder(TreeNode* root, vector<int>& res)
    {
        if(root == NULL)     
            return;
        
        // visit the left subtree
        if(root->left) 
            inorder(root->left, res);
        
        // visit the node
        res.push_back(root->val);
        
        // visit the right subtree
        if(root->right)
            inorder(root->right, res);
    }
    
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> res;
        inorder(root, res);
        return res;
    }
};
```


</details>

<details>
<summary> Iterative, again don't need to memorise if you closely   
observe the recursion stack.
</summary>

```cpp
vector<int> inorderTraversal(TreeNode* root) {
    vector<int> res;
    if(NULL == root)
        return res;
    stack<TreeNode* > s;

    while(root || s.size())
    {
        if(root)
        {
            s.push(root);
            root = root->left;
        }
        else
        {
            // we have already visited it's left 
            // visit the root
            TreeNode* curr = s.top();  s.pop();
            res.push_back(curr->val);
            root = curr->right;
        }
    }
    return res;
}
```

</details>   

**Preorder**
- visit left subtree
- visit right subtree
- visit root   
Useful for evaluvating mathematical expression with priority.

<details>
    <summary>
        Iterative, #NOTE: we need additional stack to keep track of visited        
    </summary>

```cpp
void postorder(TreeNode* root, vector<int> &res)
    {
        TreeNode* curr = root;
        stack<TreeNode*> treeStack;
        stack<bool> visited;
        bool status;
        
        if(!curr) return;
        
        treeStack.push(curr);
        visited.push(false);
        
        while(treeStack.size())
        {
            curr = treeStack.top(); treeStack.pop();
            status = visited.top(); visited.pop();
            
            if(status) 
            {
                res.push_back(curr->val);
                continue;
            }
            
            // if false first time visiting
            // put it , then right , then left
            treeStack.push(curr); visited.push(true);
            if(curr->right) 
            {
                treeStack.push(curr->right);
                visited.push(false);
            }
            
            if(curr->left)
            {
                treeStack.push(curr->left);
                visited.push(false);
            }
            
        }
        
    }
    
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> res;
        postorder(root, res);
        return res;
    }
```

</details>




