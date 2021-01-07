# Kth Missing Positive Number

If we look at the constrains this could be solved in O(n) will give AC.
But that is less interesting, so let's solve this even quicker.   

The given array is sorted and we are looking for something lower than O(n) so
Binary search with O(lgn) is good bet. But we can't directly apply binary
search in this scenario, we need to transform it. But to what ?

## Intution

I didn't comeup with solution, I was didn't get the idea after reading many
times. But the key idea is to calculate the missing point upto each index. 
this makes sense because we are searching for kth missing point. We can find
a index where the missing no.s is less than k then we can calculate k from
there.  

Interesting property to find the missing no. is `a[i] - i - 1` will give the
missing no. upto i.  
for ex: `[2, 10]` by the equation `[1, 8]`

```cpp
class Solution {
public:
    int findKthPositive(vector<int>& arr, int k) {
        int l = 0;
        int r = arr.size() - 1;
        
        if(arr.size() == 0)
            return k;
       int m; 
        while(l <= r)
        {
           m = (l + r) / 2;
           // find the missing point till this point
           if(arr[m] - m - 1 < k)
           {
               // this could be valid solution
               // but look for even better solution
               l = m + 1;
           }
           else{
               // look on left side
               r = m - 1;
           }
        }
        
        // know we have the lower bound
        // till m there are a[m] - i - 1 missing points
        // a[m] + k - (a[m] - m - 1)
        // k + m + 1 
        // k + l 
        return k + l;
    }
};
```


