# Diagonal traversal

[problem statement](https://leetcode.com/problems/diagonal-traverse/)

## Implementation

So here we need to traverse in some level, so BFS was my bet and it worked.
I wasn't much interested as bfs was easy, Definitly there could be some hacky 
solution, there was and It is actual interesting, may be even useful in someother
problem.

```cpp
// BFS
class Solution {
public:
    vector<int> findDiagonalOrder(vector<vector<int>>& matrix) {
        vector<int> res;
        int row = matrix.size();
        if(row == 0) return vector<int>();
        int col = matrix[0].size(); 
        
        queue<pair<int, int>> q; 
        int start = 1, count;
        bool flag = false;
        
        vector<vector<int>> visited(row, vector<int>(col, 0));
        q.push({0, 0});
        res.push_back(matrix[0][0]);
        int mov[2][2] = {{0, 1}, {+1, 0}};
        
        while(!q.empty())
        {
           int siz = q.size(); 
           count = 0;
           while(siz--) 
           {
               pair<int, int> curr = q.front(); q.pop();
               for(int i = 0; i < 2; ++i)
               {
                   int curr_row = curr.first + mov[i][0];
                   int curr_col = curr.second + mov[i][1];
                   if(curr_row >= 0 && curr_row < row && curr_col >= 0 && curr_col < col && !visited[curr_row][curr_col])
                   {
                       // push , mark visit, increment count
                       q.push({curr_row, curr_col});
                       visited[curr_row][curr_col] = 1;
                       count++;
                       res.push_back(matrix[curr_row][curr_col]);
                   }
               }
           }
            // reverse the part
            if(flag)
                reverse(res.begin() + start, res.end());
            
            flag = !flag;
            start += count;
        }
        return res;
    }
};
```

```cpp
class Solution {
public:
    vector<int> findDiagonalOrder(vector<vector<int>>& matrix) {
        vector<int> res;
        int row = matrix.size();
        if(row == 0) return vector<int>();
        int col = matrix[0].size(); 
        
        queue<pair<int, int>> q; 
        int start = 1, count;
        bool flag = false;
        
        vector<vector<int>> visited(row, vector<int>(col, 0));
        q.push({0, 0});
        res.push_back(matrix[0][0]);
        int mov[2][2] = {{0, 1}, {+1, 0}};
        
        while(!q.empty())
        {
           int siz = q.size(); 
           count = 0;
           while(siz--) 
           {
               pair<int, int> curr = q.front(); q.pop();
               for(int i = 0; i < 2; ++i)
               {
                   int curr_row = curr.first + mov[i][0];
                   int curr_col = curr.second + mov[i][1];
                   if(curr_row >= 0 && curr_row < row && curr_col >= 0 && curr_col < col && !visited[curr_row][curr_col])
                   {
                       // push , mark visit, increment count
                       q.push({curr_row, curr_col});
                       visited[curr_row][curr_col] = 1;
                       count++;
                       res.push_back(matrix[curr_row][curr_col]);
                   }
               }
           }
            // reverse the part
            if(flag)
                reverse(res.begin() + start, res.end());
            
            flag = !flag;
            start += count;
        }
        return res;
    }
};
```

## Complexity
time complexity : O(row * col)
space complexity : O(row * col) 
