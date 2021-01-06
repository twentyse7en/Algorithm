# RECURSION NOTES

## Introduction 

- We have a input we make a `decision` and input become smaller.  
`input` -> `Decision` -> `smaller input`
- How to *Identify* such problem?  
we have some choices and we have to make some decision.
- *Recursion Tree* : once you decision this, coding is cakewalk.

## Decision
At every stage we have to make decision.  
Ex: generate all subset of [A, B, C]   
At every stage we to decide if we have to include A, B, C.

## Recursion Tree
The `Yes` or `No` decision we make at every stage is viewed as a tree.  
Ex: from the above example we will have 2 branches according to each decision.
Include `A` , not include `A`.


## Induction and Hypothesis

So this is kinda cool. We will take an example.  

Ex: **Print no. from 0 - n**:  
`print(7)` -> `1, 2, 3, 4, 5, 6, 7` : `Original problem`  
Hypothesis : It's solved for `print(6)` : `1, 2, 3, 4, 5, 6`  
No we have do to hypothesis, ie. print `7`

recursion work like this, magic. But cool!

```cpp
void print(int n)
{
    // base
    if(n == 0)
        return;
    
    // hypothesis
    print(n - 1);

    // induction
    cout << n << endl;
}
```

## Reference
[Aditya verma](https://www.youtube.com/watch?v=kHi1DUhp9kM&list=PL_z_8CaSLPWeT1ffjiImo0sYTcnLzo-wY)


