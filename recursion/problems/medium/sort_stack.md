# Sort stack

Only use stack operation. Now this is tricker than sort array we already
solved. But How to identify this as a recursive question ?  
What I feel about this type of problems are once you categorised the problem,
you actually done the half of the work. This could be done with iteration
too but we need to explicitly make extra stack. When we need extra stack, we
could think of recursion. Or doing exactly same process for the subproblems.

Anyway let's think of the recursive version first.

## Thinking process

- Step 1 : Recursion confirmed
- Step 2 : Check *HypoInd* works
```
// sort N-1
// insert N at correct position (like in insert sort )
```
Feels this could meets the constrains

```cpp
#include<bits/stdc++.h>
using namespace std;

void insertVal(stack<int> &s, int x)
{
    // Base case
    if(s.empty())
    {
        s.push(x);
        return;
    }

    
    // Here actual comparison happens
    if(s.top() < x)
    {
        // now we have insert at correct position
        // Hypothesis
        int temp = s.top(); s.pop();
        insertVal(s, x);
        
        // Induction
        s.push(temp);
    }
    else
        s.push(x);
    
}

stack<int> sort_stack(stack<int> s)
{
    // Base 
    // -------------------
    if(s.size() == 1)
        return s;
    
    // Hypothesis
    // ------------------
    int temp = s.top(); s.pop(); 
    sort_stack(s);

    // Induction
    // -----------------
    // insert the temp to proper place
    insertVal(s, temp);
    return s;
}

int main()
{
    stack<int> s;
    s.push(50);
    s.push(30);
    s.push(40);
    s.push(20);
    s.push(70);
    // sort
    // non - decreasing / Ascending order
    s = sort_stack(s);
    while(s.size())
    {
        cout << s.top() << " " ;
        s.pop();
    }
}
```

