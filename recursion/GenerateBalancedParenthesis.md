# Generate Parentheses

Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.

[problem statement](https://leetcode.com/problems/generate-parentheses/)


## Bruteforce

Try all posibility and check parenthesis   
*time complexity*:  O(Nx2^N)  
*space complexity* : O(Nx2^N) // naively every sequence can be valid

```cpp
class Solution {
public:
    bool isBalanced(string& s)
    {
        stack<char> k;
        for(int i = 0; i < s.size(); ++i)     
        {
           if(s[i] == '(') 
               k.push('(');
            else
            {
                if(k.size() == 0)
                    return false;
                k.pop();
            }
        }
        return true;
    }
    
    void helper(string s, int right, int left, vector<string>& res)
    {
        if(right == 0 && left == 0)
        {
            // check if balaneced
            if(isBalanced(s))
                res.push_back(s);
            return;
        }
       // next value can be right parenthesis or left 
        s.push_back('x');
        
        if(right)
        {
            s[s.size()-1] = ')';
            helper(s, right-1, left, res);
        }
        
        if(left)
        {
            s[s.size()-1] = '(';
            helper(s, right, left - 1, res);
        }
    }
    
    vector<string> generateParenthesis(int n) {
        vector<string> res;
        if(n == 1)
        {
            res.push_back("()");
            return res;
        }
        string s;
        helper(s, n, n, res);
        return res;
    }
};
```

## Approach 2

Way cooler, I haven't seen such implementation. This is good.  
*time and space* : this is complicated, I have no idea how they summarize 
to nth catalan no.

```cpp
class Solution {
public:
    void helper(string s, vector<int>& res, int left, int right)
    {
        if(left == 0 && right == 0)
        {
            res.push_back(s);
            return;
        }
        
        if(left)
            helper(s + '(', res, left-1, right + 1);
        if(right)
            helper(s + ')', res, left, right - 1);
        
    }
    
    vector<string> generateParenthesis(int n) {
        vector<string> res;
        // this actually beutiful
        // we can put left parenthesis freely
        // if we have put a left parenthesis
        // now we have choice to put right/left
        helper("", res, n, 0);
        return res;
    }
};
```
