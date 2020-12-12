// ===== It's a bit different from the previous one ==========
//
// using two stack
// the root needs to visit again if it is true we are allowed to 
// choose it.


class Solution {
public:
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
};



// This answer is alse interesting 
// This use only one stack
// But kinda a follow the what we did in the above
// Push 2 times the same elements if we are visiting for 
// first time.
// If there is two instance of the same element then we 
// need to add it's left and right
// if there is already one instacnce then we are visiting it
// twice, mark as visit or do something

class Solution {
public:
    vector<int> postorderTraversal(TreeNode *root) {
        vector<int> ret;
        if(!root) return ret;
        stack<TreeNode*> st;

        // push twice
        st.push(root);
        st.push(root);
        TreeNode *cur;

        while(!st.empty()){

            cur = st.top();
            st.pop();

            // special care for root node
            if(!st.empty()&&st.top() == cur){
                if(cur->right) {
                    st.push(cur->right);
                    st.push(cur->right);
                }
                if(cur->left){
                    st.push(cur->left);
                    st.push(cur->left);
                }
            }
            // only one instance
            else
                ret.push_back(cur->val);
        }
        return ret;
    }
};
