// ====== Stack + iteration =======================
// O(n) space


class Solution {
public:

    vector<int> inorderTraversal(TreeNode* root) {
        stack<TreeNode*> treeStack;
        TreeNode* curr = root;
        vector<int> res;
    
        // do it iteratively
        while(curr || treeStack.size())
        {
            if(curr != NULL)
            {
                treeStack.push(curr);
                curr = curr->left;
            }
            
            else
            {
                curr = treeStack.top();
                treeStack.pop();
                res.push_back(curr->val);
                curr = curr->right;
                
            }
               
        }
        
        return res;
    }
};

// ====== Morris traversal ========================
// O(1) space
