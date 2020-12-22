# Surrounded Region

[Problem statement](https://leetcode.com/problems/surrounded-regions/submissions/)

## Idea

dfs on the surrounded edges

## Implementation

```cpp
class Solution {
public:
    int row, col;
    
    void dfs(vector<vector<char>>& board, vector<vector<int>>& visited, int curr_row, int curr_col)
    {
        if(curr_row >= 0 && curr_col >= 0 && curr_row < row && curr_col < col )
        {
            if(visited[curr_row][curr_col] == 0 && board[curr_row][curr_col] == 'O')
            {
                visited[curr_row][curr_col] = 1;
                dfs(board, visited, curr_row - 1, curr_col);
                dfs(board, visited, curr_row + 1, curr_col);
                dfs(board, visited, curr_row, curr_col + 1);
                dfs(board, visited, curr_row, curr_col - 1);
            }

        }
    }
    
    void solve(vector<vector<char>>& board) {
        if(board.size() == 0) 
            return;

        row = board.size();
        col = board[0].size();

        vector<vector<int>> visited(row, vector<int>(col, 0));

        for(int i = 0; i < row; ++i)
            for(int j = 0; j < col; ++j)
                if(i == 0 || j == 0 || i == row - 1 || j == col - 1)
                    dfs(board, visited, i, j);

        // now our visited contain the one's that isn't surrounded
        for(int i = 0; i < row; ++i)
            for(int j = 0; j < col; ++j)
                if(board[i][j] == 'O' && visited[i][j] == 0)
                    board[i][j] = 'X';
        

    }
};
```
