# Rotten Oranges

[problem statement]()

For all fresh oranges, find the length to nearest rotten orange.

## Approach 1

Dumb but iTworKed. Start bfs from all rotten oranges and relax all the fresh
oranges. 

```cpp
class Solution {
public:
    int row;
    int col;
    
    bool isValid(int r, int c)
    {
        return !(r < 0 || r >= row | c < 0 | c >= col);
    }
    
    void bfs(vector<vector<int>>& grid, vector<vector<int>>& dist, int r, int c)
    {
        // if we could relax the neighbor visit it
        int dir[4][2] = {{1,0}, {-1, 0}, {0,1}, {0, -1}};
        
        queue<pair<int, int>> q;
        q.push({r, c});
        
        while(q.size())
        {
            int size = q.size();
            while(size--)
            {
                pair<int, int> curr = q.front(); q.pop();
                r = curr.first;
                c = curr.second;
                for(int i = 0; i < 4; ++i)
                {
                    int next_r = r + dir[i][0];
                    int next_c = c + dir[i][1];

                    if(isValid(next_r, next_c) && grid[next_r][next_c] == 1 && dist[next_r][next_c] > dist[r][c] + 1)
                    {
                        //relax and visit
                        dist[next_r][next_c] = dist[r][c] + 1;
                        q.push({next_r, next_c});
                    }
                }
                
            }
        }
    }
    
    int orangesRotting(vector<vector<int>>& grid) {
        
        //do bfs from all rotten oranges
        // relax the distance of the fresh oranges
        row = grid.size();
        col = grid[0].size();
        vector<vector<int>> dist(row, vector<int>(col, INT_MAX));
        
        for(int i = 0; i < row; ++i)
            for(int j = 0; j < col; ++j)
                if(grid[i][j] == 2)
                {
                    dist[i][j] = 0;
                    bfs(grid, dist, i, j);
                }
        
        
        int res = 0;
        for(int i = 0; i < row; ++i)
            for(int j = 0; j < col; ++j)
                if(grid[i][j] == 1)
                    res = max(res, dist[i][j]);
        
        return res == INT_MAX ? -1: res;
    }
};
```

Why this is a bad idea, obviously it have to run bfs for all the rotten oranges.

## Approach 2

Add all rotten oranges to level one then start bfs.

*Time Complexity* : O(row*col)   
*Space Complexity* : O(row *col)

```cpp
class Solution {
public:
    
    typedef pair<int, int> pii;
    int row, col; 
    
    bool isValid(int r, int c)
    {
        return !(r < 0 || r == row || c < 0 || c == col);
    }
    
    int orangesRotting(vector<vector<int>>& grid) {
        
        row = grid.size();     
        col = grid[0].size();
        
        vector<vector<int>> dist(row, vector<int>(col, INT_MAX));
        
        // push all the rotten oranges
        queue<pii> q;
        for(int i = 0; i < row; ++i)
            for(int j = 0; j < col; ++j)
            {
                if(grid[i][j] == 2)
                {
                    q.push({i, j});
                    dist[i][j] = 0;
                }
                else if(grid[i][j] == 0)
                    dist[i][j] = 0;
            }
        
        
        int dir[4][2] = {{1,0}, {-1,0}, {0,1}, {0, -1}};
        
        // now start bfs
        while(q.size())
        {
            int size = q.size();
            while(size--)
            {
                pii curr = q.front(); q.pop();
                
                // visit the neighbors
                for(int i = 0; i < 4; ++i)
                {
                    int r = curr.first + dir[i][0];
                    int c = curr.second + dir[i][1];
                    
                    if(isValid(r, c) && dist[r][c] > dist[curr.first][curr.second] + 1)
                    {
                        dist[r][c] = dist[curr.first][curr.second] + 1;
                        q.push({r, c});
                    }
                }
            }
        }
        
        int res = 0;
        for(int i = 0; i < row; ++i)
            for(int j = 0; j < col; ++j)
                res = max(res, dist[i][j]);
       
        return res == INT_MAX ? -1 : res;
    }
};
```

