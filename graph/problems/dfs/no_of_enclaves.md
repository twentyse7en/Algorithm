# No of Enclaves

# Approach

Only need to traverse from the boundary

```cpp
class Solution {
public:
    int row, col;
    int flag;
    
    void dfs(vector<vector<int>>& A, vector<vector<int>>& visited, int curr_row, int curr_col)
    {
       // check valid 
        if(curr_row >= 0 && curr_col >=0 && curr_row < row && curr_col < col && A[curr_row][curr_col] && !visited[curr_row][curr_col])
        {
            // mark as visited
            visited[curr_row][curr_col] = 1;
            
           // visited neighbours 
           dfs(A, visited, curr_row - 1, curr_col);
           dfs(A, visited, curr_row + 1, curr_col);
           dfs(A, visited, curr_row, curr_col - 1);
           dfs(A, visited, curr_row, curr_col + 1);
        }
    }
    
    int numEnclaves(vector<vector<int>>& A) {
        
        // Approach would be to start traverse from the boundary
        // nodes
        
        row = A.size(); 
        col = A[0].size();
        vector<vector<int>> visited(row, vector<int>(col, 0));
        
        int res = 0;
        for(int i = 0; i < row; ++i)
            for(int j = 0;  j < col; ++j)
                if(i == 0 || j == 0 || i == row -1 || j == col - 1)
                    dfs(A, visited, i, j);
       
        // now the visited will contain 1
        // for which can be reached from the boundary
        // It should be excluded
        int count = 0;
        for(int i = 0; i < row; ++i)
            for(int j = 0; j < col; ++j)
                if(A[i][j] && !visited[i][j])
                    count++;
        
        
        return count;
    }
};
```
