# Quick short note on problems

## Hypothesis - Induction

You may have already read how this but again as a summary.

**General Structure**  
```cpp

void print(int n)
{
    //1. base
    //----------------------

    if(n == 0)
        return;
    
    // hypothesis
    //----------------------
    print(n - 1);

    // induction
    //-----------------------
    cout << n << endl;
}
```

Induction does the main work If you want to print N to 1 instead of 1 to N,
swap the hypothesis and Induction.  

**EASY**  
- Height of binary tree :  
*Hypothesis* : height of left and right tree  
*Induction* : `1 + max(left, right)`   

- Sort an array : There is kinda confusion as `Mergesort` is recursion. if
we follow HypoInd, we actual endup with insertion sort.

*Hypothesis*: Sort from 1 to N-1
*Induction*: Insert Nth element in correct position.

- Sort a stack : This is more meaningful question. See more details in 
actual solution in notes.

- *Reverse the stack* : Here it's a kind a tricky, one recursion to reverse
the remaining elements, and another to insert the current element to end
of the reversed stack.   

*Hypothesis* : Reverse for N-1 elements  
*Induction* : Insert the N on the bottom
Time complexity : O(N<sup>2</sup>)

## Problems List
- [Print N-bit binary numbers having more 1s than 0s ](https://practice.geeksforgeeks.org/problems/print-n-bit-binary-numbers-having-more-1s-than-0s0252/1#)

