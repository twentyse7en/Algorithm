# No of islands

```cpp
class Solution {

public:
    int m;
    int n;
    
    bool isvalid(vector<vector<char>>& grid, int x, int y)
    {
        if(x >= 0 && x < m && y >= 0 && y < n && grid[x][y] == '1')
            return true;
        return false;
    }
    
    void dfs(vector<vector<char>>& grid, vector<vector<int>>& visited, int x_pos, int y_pos)
    {
        // mark as visited
        visited[x_pos][y_pos] = 1;
        // cout << x_pos << " "  << y_pos << endl;
        // the connection
        int x_axis[] = {1, -1, 0, 0};
        int y_axis[] = {0, 0, 1, -1};
        
        int x;
        int y;
        
        
        // visit the neighbours if not visited
        for(int i = 0; i < 4; i++)
        {
            x = x_pos + x_axis[i];
            y = y_pos + y_axis[i];
            // cout << x << " " << y << " " << isvalid(grid, x, y)  << endl;
            if(isvalid(grid, x, y) && visited[x][y] == 0)
            {
                dfs(grid, visited, x, y);
            }
        }
        
        // cout << "end searching" << endl;
    }

    int numIslands(vector<vector<char>>& grid) {
        m = grid.size();
        n = grid[0].size();
        int count = 0;
        
        // construct a table to mark visited
        vector<vector<int>> visited(m, vector<int> (n, 0));
        
        for(int i = 0; i < m; i++)
        {
            for(int j = 0; j < n; j++)
            {
                // if not visited
                if(visited[i][j] == 0 && grid[i][j] == '1')
                {
                    // dfs
                    count++;
                    // cout << "new" << endl;
                    dfs(grid, visited, i, j);
                }
            }
        }
        
        return count;
    }
};
```

Space complexity :  o(m*n) can reduce if i edit grid inplace.
Time complexity : O(m*n) (usually O(v+e) here e = 4*v)
