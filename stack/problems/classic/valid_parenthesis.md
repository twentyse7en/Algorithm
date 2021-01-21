# Valid Parenthesis

[problem statement]()


## My Solution

```cpp
class Solution {
public:
    bool isMatching(char y, char x)
    {
        if(x == ')' && y == '(')
            return true;
        if(x == '}' && y == '{')
            return true;
        if(x ==']' &&  y == '[')
            return true;
        
        return false;
            
    }
    bool isValid(string s) {
        // feels like the naive question upgraded
        stack<char> opStack;
        for(char x: s)
        {
            // if you see open bracket push
            if(x == '(' || x == '{' || x == '[')
            {
                opStack.push(x);
            }
            else{
                // closing then it should match
                if(opStack.size() == 0)
                    return false;
                char y = opStack.top(); opStack.pop();
                if(!isMatching(y, x))
                    return false;
            }
        }
        return opStack.empty();
    }
};
```

## Another Beutiful solution

```cpp
bool isValid(string s) {

    // pruning
    // size can't be odd
    if(s.size()%2)
        return false;

    stack<char> opStack;
    for(char c: s)
    {
        if(c == '(')
            opStack.push(')');
        else if(c == '{')
            opStack.push('}');
        else if(c == '[')
            opStack.push(']');

        // pop time
        else if(opStack.empty() || opStack.top() != c)
            return false;
        else
            opStack.pop();
    }
    return opStack.empty();
}
```
