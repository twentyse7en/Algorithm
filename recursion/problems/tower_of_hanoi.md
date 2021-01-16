# Tower of Hanoi

This is very standard problem.

## Resources
[Khan Academy](https://www.khanacademy.org/computing/computer-science/algorithms/towers-of-hanoi/a/towers-of-hanoi-continued)  
[Aditya verma](https://www.youtube.com/watch?v=l45md3RYX7c&list=PL_z_8CaSLPWeT1ffjiImo0sYTcnLzo-wY&index=11&pbjreload=101)  
[GFG problem](https://practice.geeksforgeeks.org/problems/tower-of-hanoi-1587115621/1)


## Note

<img src="https://github.com/twentyse7en/Algorithm-notes/blob/main/recursion/problems/tower_of_hanoi.png" />

## Code

```cpp
class Solution{
    public:
    // You need to complete this function

    // avoid space at the starting of the string in "move disk....."
    long long toh(int N, int from, int to, int aux) {
        // Your code here
        if(N == 1)
        {
            printf("move disk %d from rod %d to rod %d\n", 1, from, to);
            return 1;
        }
        
        long long count = 0;
        // decrease
        count += toh(N-1, from, aux, to);
        
        printf("move disk %d from rod %d to rod %d\n", N, from, to);
        count += 1;
        // conquer
        count += toh(N-1, aux, to, from);
        return count;
    }

};
```

## Complexity

*Time complexity* : O(2<sup>n</sup>)  
*Space complexity* : O(n)
