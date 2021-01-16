# Search a 2D Matrix II


This was exercise to do inside recusrsion ii explore card obviously I was
expecting a divide and conquer algorithm, and don't get confused with the 
example test case given.  

## Intuition

For divide and conquer we divide the search space into 4 parts we only
search in 3 parts, and we get rid of one part.

<img src="https://user-images.githubusercontent.com/59721339/103978810-5eaed500-51a2-11eb-858c-c9214a6bcc61.png" />

```cpp
class Solution {
public:
    bool search(vector<vector<int>>& matrix, int r_start, int r_end, int c_start, int c_end, int target)
    {
        if(r_start > r_end || c_start > c_end)     
            return false;
        
        int r_mid = (r_start + r_end)/2;
        int c_mid = (c_start + c_end)/2;
        
        if(target ==  matrix[r_mid][c_mid])
            return true;
        
        // zone 1 | zone 2 | zone 3
        if(target < matrix[r_mid][c_mid])
            return  search(matrix, r_start, r_mid-1, c_start, c_mid -1, target)
                 || search(matrix, r_mid, r_end, c_start, c_mid-1, target)
                 || search(matrix, r_start, r_mid-1, c_mid, c_end, target);
        
        return search(matrix, r_mid + 1, r_end, c_start, c_mid, target)
             ||search(matrix, r_mid + 1, r_end, c_mid+1, c_end, target) 
             ||search(matrix, r_start, r_mid, c_mid+1, c_end, target);
    }
    
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int row = matrix.size();
        int col = matrix[0].size();
        return search(matrix, 0, row - 1, 0, col - 1, target);
    }
};
```

*Time Complexity* : recurrence = 3(N/4) + 1; O(N<sup>log<sub>4</sub>3</sup>) N = row*col (master's theorem condition 2)


## Approach 2

But there is a interesting property, which makes this even faster. from top right
this feels like BST.

<img src="https://assets.leetcode.com/static_assets/discuss/uploads/files/1488858512318-monosnap-2017-03-06-22-48-17.jpg"/>

```cpp
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int row = matrix.size();
        if(row == 0 || !matrix[0].size())
            return false;
        
        int col = matrix[0].size();
        int r = 0, c = col - 1;
        while(r <= row-1 && c >=0)
        {
           int curr_val = matrix[r][c];
           if(curr_val == target) 
               return true;
           
           if(curr_val < target)
               r+=1;
           else
               c-=1;
        }
            
        return false;
    }
};
```

*Time complexity* : O(m+n)  
*Space complexity* : O(1)
