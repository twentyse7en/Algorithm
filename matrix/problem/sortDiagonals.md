# 1329. Sort the Matrix Diagonally

Can be done conviently if we know the property of diagonal.

## Intial approach

traverse each diagonal individually.

```cpp
class Solution {
public:
    int r, c;
    
    void helper(vector<vector<int>>& mat, int curr_r, int curr_c)
    {
        vector<int> buffer;
        int tmp_r = curr_r, tmp_c = curr_c;
        while(tmp_r < r && tmp_c < c)
            buffer.push_back(mat[tmp_r++][tmp_c++]);
        
        sort(buffer.begin(), buffer.end());
       
        int i = 0;
        while(curr_r < r && curr_c < c)
            mat[curr_r++][curr_c++] = buffer[i++];
    }
    
    vector<vector<int>> diagonalSort(vector<vector<int>>& mat) {
        r = mat.size();
        c = mat[0].size();
        // traverse from the start of the diagonal
        for(int i = 0; i < c; ++i)
            helper(mat, 0, i);
        
        for(int i = 1; i < r; ++i)
            helper(mat, i, 0);
        
        return mat;
    }
};
```

## Simple approach

*time* : O(MNlogD) D->length of longest diagonal.
*space* : O(MN)

```cpp
class Solution {
public:
    vector<vector<int>> diagonalSort(vector<vector<int>>& mat) {
        // remeber it is max heap
        // so add values from end of the matrix
        int r = mat.size();
        int c = mat[0].size();
        
        unordered_map<int, priority_queue<int>> hm;
        for(int i = 0; i < r; ++i)
            for(int j = 0; j < c; ++j)
                hm[i-j].push(mat[i][j]);
        
        for(int i = r-1; i >= 0; --i)
            for(int j = c-1; j>= 0; --j)
            {
                mat[i][j] = hm[i-j].top();
                hm[i-j].pop();
            }
        return mat;
    }
};
```
