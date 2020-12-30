# Pseudo-Palindromic Paths in a Binary Tree

[problem statement](https://leetcode.com/problems/pseudo-palindromic-paths-in-a-binary-tree/)

## Intution

This is very straight forward question. We have two subtask
- find all the path 
- check if the path is pseudo palindromic

This is very easy to achieve with dfs and do the psuedo palindromic check

<details>
<summary> My first Approach </summary>

```cpp
class Solution {
public:
    int res;
    
    void dfs(TreeNode* root, vector<int> count)
    {
        if(!root->left && !root->right)
        {
            count[root->val - 1]++;   
            
            // we need
            // total count
            // odd and even
            int pathLength = 0; 
            int odd = 0, even = 0;
            for(int i = 0; i < count.size(); ++i)
            {
                pathLength += count[i];
                if(count[i]%2)
                    odd++;
                else
                    even++;
            }
            
            if(pathLength%2 == 1 && odd == 1)
                res++;
            if(pathLength%2 == 0 && odd == 0)
                res++;
        }
        
        // increment count
        count[root->val - 1]++;
        
        // visit left 
        if(root->left)
            dfs(root->left, count);
        
        // visit right
        if(root->right)
            dfs(root->right, count);
    }
    
    int pseudoPalindromicPaths (TreeNode* root) {
        
        if(!root)
            return 0;
        
        res = 0;
        // keep track of the count
        vector<int> count(9, 0);
        dfs(root, count);
        
        return res;
    }
};
```

</details>


*Time Complexity* : O(N) </br>
*Space Complexity* : O(H) (H -> height of the tree)

## Improvement

The below improvement doesn't improve the time or space complexity.
But using a bit vector saves some space.

### Psuedo - palindrome

I wan't to improve the solution. For the first part the logic is:
- If path length is odd then 1 odd no. is allowed
- If path length is even no odd no. is allowed.
The trick here is that, If one odd exist then there will be another odd
in even path.

- Now the problem reduced to, **atmost one odd is allowed**. I'm have already seen this trick
but unlikly for me to come up again.

### The space can be improved

Here we can use a bit vector and save some space, but here It takes too
much effort for a smaller improvement. If we use vector then the space
consumed is O(9) which is O(1), so asymptotically no. difference.
I'm skipping that.

But I figured out the black magic. We want atmost one 1 in the bitvector. 

`n & (n - 1)` does the trick
ex: `n = 1000000` `n - 1 : 0111111` thus `n&(n-1)` gives `1`
