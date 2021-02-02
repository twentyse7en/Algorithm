# 151. Reverse Words in a String
[link](https://leetcode.com/problems/reverse-words-in-a-string/)


# Best Approach

1. reverse
2. reverse individual words
3. remove the space.

This might feel very hard to implement, but they are easy.

```cpp
class Solution {
public:
    
    void reverse_words(string& s)
    {
       int sz = s.size();
       for(int i = 0; i < sz; ++i)
       {
           if(s[i] == ' ')
               continue;
           
           // now it's start of word
           int next = i+1; 
           while(next < sz && s[next] != ' ')
               next++;
           reverse(s.begin()+i, s.begin()+next);
           i = next;
       }
    }
    
    void remSpace(string& s)
    {
        // very cool
        int i = 0, j = 0, n = s.size();
        while(j < n)
        {
            // skip the white space
            while(j < n && s[j] == ' ')
                j++;
            
            // copy the values
            while(j < n && s[j] != ' ')
                s[i++] = s[j++];
            
            while(j < n && s[j] == ' ')
                j++;
            
            if(j < n)
                s[i++] = ' ';
        }
        s = s.substr(0, i);
    }
    
    string reverseWords(string s) {
       // reverse the string
        reverse(s.begin(), s.end());
        
        // reverse the individual words
        reverse_words(s);
        
        // remove the extra space
        remSpace(s);
        
        
        return s;
    }
};
```

# Python, go brr.

```python
def solution(s):
   return ' '.join(s.split()[::-1]);
```

# CPP : Simple
```cpp
class Solution {
public:
    string reverseWords(string s) {
        stringstream ss(s);
        stack<string> st;
        string out;
        while(ss >> out)
            st.push(out);
       
        out = "";
        
        if(st.size())
        {
            out.append(st.top());
            st.pop();
        }
        
        while(st.size())
        {
            out.append(" ");
            out.append(st.top());
            st.pop();
        }
        return out;    
    }
};
```
