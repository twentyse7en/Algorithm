# Decoded String at Index

## Approach

This is kinda tricky question, but I was able to catch the hint and made a 
algorithm, what ate up my time was the indexing, the query was in 1-based indexing.
So I have to convert it to zero based to my implementation to work. 

```cpp
class Solution {
public:
    long long int getLength(string& S, int end)
    {
       long long int buffer = 0;
       for(int i = 0; i < end;++i) 
       {
           if(isdigit(S[i]))
              buffer *= (S[i]-'0');
           else
              buffer += 1;  
       }
        return buffer;
    }
    
    string decodeAtIndex(string S, int K) {
        string res;
        long long int len;
        
        // converting to zero indexing
        // This took a lot of time
        K -= 1;
        
        for(int i = S.size() - 1; i >= 0; --i)
        {
           // this could be avoided 
            // we only need to calculate the length intially 
            
           len = getLength(S, i); 
            
           if(isdigit(S[i]))
               K = K % len;
            else
              if(len  == K)            
              {
                  res.push_back(S[i]);
                  break;
              }
        }
        return res;
    }
};
```

This can be improved as we don't need to call the length always.

## Improved Approach

This follows 1 based indexing. Consider following example.
```
a23 k = 2
a2  k = 2
a   k = 0 // I was confused at this stage

// k = 0 means we have reached the solution
```

```cpp

    public String decodeAtIndex(String S, int K) {
        
        long curLength = 0;
        char c = 0;
        
        for (int i = 0; i < S.length(); i++) {
            c = S.charAt(i);
            if (Character.isDigit(c)) { \\ a1
                curLength *= c - '0';
            }
            else { \\ b1
                curLength++;
            }
        }
        
        for (int i = S.length() - 1; i >= 0; i--) {
            c = S.charAt(i);
            if (Character.isDigit(c)) { \\ a2
                curLength /= c - '0';
                K %= curLength;
            }
            else { \\ b2
                if (K == 0 || K == curLength) {
                    return "" + c;
                }
                curLength--;
            }
        }
        
        throw null;
    }
```
