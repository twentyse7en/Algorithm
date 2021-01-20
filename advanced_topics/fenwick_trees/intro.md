# Fenwick Trees / Binary Indexed Trees

## Motivation

If we have a array `[1, 2, 3, 4, 5]` and we need to find the sum
between index 0 to 3. Smart way is to compute the `prefix sum` `O(N)`.
But what if we need to change the values, then we need to recompute 
the `prefix sum` this makes it inefficient for this dynamic operation.   
Oh god please help !! Ok now he send us the `Fenwick trees` aka `Binary Indexed Trees`
to make the world a bit less chaotic.   
It solves exactly the problem we were facing, sum between ranges and
update the array when we needed efficiently.

## How magic happens

Better watch the [video](https://www.youtube.com/watch?v=RgITNht_f4Q) it is much easier than words.

<img src="https://user-images.githubusercontent.com/59721339/104131164-b6179580-539a-11eb-8b52-ac7f6a96aea2.png" />   

ex : sum untill 7. So in the array each cell is responsible for a
range of values. 
- Note: This is 1-based indexing
- no. of cells responsible is based on Least Significant Bit.  
for 7 - `111` -> 1 cell, itself    
for 6 - `110` -> 2 cells below  
for 4 - `100` -> 4 cells below

How to find sum between a range ?  
It's a piece of cake if we know how to find sum upto a particular index.

## How to construct
[Video](https://www.youtube.com/watch?v=BHPez138yX8)  
- Deepcopy the Array
- Update the immediate parent for all index.

## Example

[Create Sorted Array through Instructions](https://leetcode.com/problems/create-sorted-array-through-instructions/)
```cpp
class Solution {
public:
    
    int c[100001];
    
    void update(int x)
    {
        // update all the parents how are responsible
        while(x < 1e5+1)
        {
            c[x]++;
            x += x&-x;   // x&-x gives Least Significant Bit
        }
    }
    
    int get(int x)
    {
        int res = 0;
        while(x > 0)
        {
            res += c[x];
            x -= x&-x;  // sum childs
        }
        return res;
    }
    
    int createSortedArray(vector<int>& A) {
       // This could be only solved using some segment trees
       // Let's use fenwick trees which is a updation of
       // PrefixSumArray with dynamic operation
       memset(c, 0, sizeof(c));
       int res = 0;
       int mod = 1e9+7;
        // intution is to store the count of values
        // so we can query the sum of values, which will
        // the count less than a value
       for(int i = 0; i < A.size(); ++i)
       {
          // count/sum below the current value
          // count/sum till the currValue 
          // Above = i - till currValue
          res = (res + min(get(A[i]-1), i - get(A[i])))%mod;
          update(A[i]);
       }
        return res;
    }
};
```
