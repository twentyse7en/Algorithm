# 0-1 Matrix

[problem statement](https://leetcode.com/problems/01-matrix/solution/)


## Approach

<img src="https://github.com/twentyse7en/Algorithm-notes/blob/main/graph/problems/assests/0-1%20matrix.png" align="center" />
## code

### DP

```cpp
class Solution {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& matrix) {
        
        int row = matrix.size();
        if(row == 0)
            return matrix;
        int col = matrix[0].size();
        

       
        vector<vector<int>> result(row, vector<int>(col, INT_MAX));
        
        // first visit
        for(int i = 0; i < row; ++i)
            for(int j = 0; j < col; ++j)
            {
               if(matrix[i][j] == 0) 
                   result[i][j] = 0;
                else
                {
                   // check edge condition
                   if(i > 0 && result[i - 1][j] != INT_MAX) 
                       result[i][j] = min(result[i][j], result[i - 1][j] + 1);
                   if(j > 0 && result[i][j -1] != INT_MAX)
                       result[i][j] = min(result[i][j], result[i][j - 1] + 1);
                }
            }
        
        for(int i = row - 1; i >= 0; --i)
            for(int j = col - 1; j >= 0; --j)
            {
               if(i+1 < row && result[i+1][j] != INT_MAX)
                   result[i][j] = min(result[i][j], result[i+1][j] + 1);
                if(j+1 < col && result[i][j + 1] != INT_MAX)
                    result[i][j] = min(result[i][j], result[i][j + 1] + 1);
            }
        
        return result;
    }
};
```

### BFS

```cpp
class Solution
{
    public:
     vector<vector<int>> updateMatrix(vector<vector<int>>& matrix) {
         int row = matrix.size();
         if(row == 0) return matrix;
         int col = matrix[0].size();
         
         vector<vector<int>> result(row, vector<int>(col, INT_MAX));
         
         queue<pair<int, int>> que;
         
         for(int i = 0; i < row; ++i)
             for(int j = 0; j < col; ++j)
             {
                if(matrix[i][j] == 0) 
                {
                    result[i][j] = 0;
                    que.push({i, j});
                }
             }
         
         int dir[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, +1}};
         
         while(!que.empty())
         {
            // we don't need to store the size like in traditional bfs 
            // why? we store it to keep track of level, here we explictly store it
             pair<int,  int> curr = que.front(); que.pop();
             
             for(int i = 0; i < 4; i++)
             {
                int r = curr.first + dir[i][0];
                int c = curr.second + dir[i][1];
                 
                 if(r >= 0 && r < row && c >= 0 && c < col)
                 {
                    // if we improve the distance update it
                     if(result[r][c] > result[curr.first][curr.second] + 1)
                     {
                         result[r][c] = result[curr.first][curr.second] + 1;
                         // push that to queue for further propogating
                         que.push({r, c});
                     }
                 }
             }
             
         }
         
             return result;
         
     }
    
};
```
