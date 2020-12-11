// ======= Iterative preorder ======================================

class Solution {
public:
    void preorder(TreeNode* root, vector<int> &res)
    {
       TreeNode* curr = root;
       stack<TreeNode*> treeStack;
       
        while(curr || treeStack.size())
        {
           if(curr)
           {
               res.push_back(curr->val);
               if(curr->right) treeStack.push(curr->right);
               curr = curr->left;
           }
            else{
                curr = treeStack.top(); treeStack.pop();
                
            }
        }
    }
    
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> res;
        preorder(root, res);
        return res;
    }
};
