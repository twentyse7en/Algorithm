#  Largest Rectangle in Histogram

[problem statement](https://leetcode.com/problems/largest-rectangle-in-histogram/)

## My Approach

For every element, find the no. of subarray on right greater than equal to that
element also to left. Thus we get the breadth and multiply it with the current 
height.

*Time complexity* : O(N<sup>2</sup>)

```cpp
class Solution {
public:
    
    unordered_map<int, pair<int, int>> umap;
    
    int left(vector<int>&  heights, int curr)    
    {
       int count = 0; 
       int h = heights[curr];
       while(--curr >= 0 && heights[curr] >= h) 
           count++;
        
       return count;
    }
    
    int right(vector<int>&  heights, int curr)    
    {
       int count = 0; 
        int h = heights[curr];
        while(++curr < heights.size() && heights[curr] >= h)
            count++;
        
        return count;
    }
    
    int largestRectangleArea(vector<int>& heights) {
        
        int n = heights.size(); 
        int res = 0;
        
       int k = 0; 
       while(k < n && heights[k] == 1) 
          k++; 
        
        if(k == n)
            return n;
        
        for(int i = 0; i < n; ++i) 
        {
            int l = left(heights, i);
            int r = right(heights, i);
            
            umap[i] = {l, r};
            
            // printf("left:%d right:%d curr:%d\n", l, r, heights[i]);
            res = max(res, heights[i]*(l + r + 1));
        }
        
        return res;
    }
};
```


## Improvements

My approach  is O(N<sup>2</sup>) this isn't enough. While thinking about
DP It's kinda difficult to think because what to save in memo. Let's check
the discussion.

Here is an improved one.

`l`: the first coordinate of the bar to the left with height h[l] < h[i].  
`r`: the first coordinate of the bar to the right with height h[r] < h[i].

<img src="https://user-images.githubusercontent.com/59721339/103434428-29950680-4c27-11eb-832a-3c323c7fff79.png" align="center" />

```java
int maxArea = 0;
for (int i = 0; i < height.length; i++) {
    maxArea = Math.max(maxArea, height[i] * (lessFromRight[i] - lessFromLeft[i] - 1));
}
```

Core is to calculate `lessFromRight` and `lessFromLeft` in O(N). It not that
easy to prove what he says is O(N). In simple words 

Consider the test case
```
indices.......... : 0 1 2 3 4 5 6 7 8 9 10 11
heights.......... : 4 9 8 7 6 5 9 8 7 6 5 4.
lessFromLeft :-1 0 0 0 0 0 5 5 5 5 . .
```

In this, when we reach 5 at index 10, we start searching for idx=9, i.e. p points at 6.
6 > 5.
Now, we want something which is smaller than 5, so it should definitely be smaller than 6. So 6 says to 5:

I've already done the effort to find the nearest number that's smaller than me and you needn't traverse the array again till that point. My lessFromLeft points at index 5 and all the elements between that and me are greater than me so they are surely greater than you. So just jump to that index and start searching from there.

So you next p directly points at idx = 5, at value 5.

`The question remains how is this O(N)?`   
This is the essence `Each node that tells the back-scan to bounce over it will never participate in any future back-scans ever again`.

Because asking value is less than it, and for the next upcoming asking value
should be less than current value to query, so the nodes  already 
covered aren't covered again. With an example we can prove that we
don't visit what we already visited.

<img src="https://user-images.githubusercontent.com/59721339/103434677-d58c2100-4c2a-11eb-92d3-c5258abca203.png" align="center" height="400" />

```cpp
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
       int n = heights.size(); 
        if(n == 0)
            return 0; 
       
       vector<int> leftArr(n, 0);
       vector<int> rightArr(n, 0);
        
       for(int i = 0; i < n; ++i)
       {
           int p = i - 1;
           
           while(p >= 0 && heights[p] >= heights[i])
               p = leftArr[p];
           
           leftArr[i] = p;
       }
        
       for(int i = n-1; i >= 0; --i)
       {
           int p = i + 1; 
           
           while(p < n && heights[p] >= heights[i])
               p = rightArr[p];
           
           rightArr[i] = p;
       }
        
       int res = 0;
       for(int i = 0; i < n; ++i) 
          res = max(res, heights[i] * (rightArr[i] - leftArr[i] - 1));
        
        return res;
    }
};
```

Another approach is to use [stack](https://leetcode.com/problems/largest-rectangle-in-histogram/discuss/28900/Short-and-Clean-O(n)-stack-based-JAVA-solution) which is  even harder to understand.

## Stack solution

Stack solution is kinda cool. Better to picturize it.

<img src="https://user-images.githubusercontent.com/59721339/103436557-e6e12780-4c42-11eb-87e8-cdde4af529a9.png" />

- put 6 to stack
- 2 < 6 so we can't club 6 with 2 (but can club 2 with 6)
- calculate the area of 6 ie, 6
- push 5 to stack.
- 4 < 5, can't club 5 with 4 | what is the breadth index(4) - index(2) - 1
- push 4
- push 5
- can't club 5 with 1 | breadth = index(1) - index(4) - 1 
- can't club 4 with 1 | breadth = index(1) - index(2) - 1;
- can't club 2 with 1 | breadth = index(i)
- stack contains only 1
- push 6
- reached the end pop 6 | breadth = len - index(1) - 1;
- pop 1 | breadth =  len;

*Intution* behing the element in stack: first element will be smallest 
till i

Consider this specific situation in stack : [2, 4, 5] next element : 1  
5 knows 1 is less than it, so we can get the right limit from it, what about
the right part ?  

This is the tricky part, for `5` it is `4` it is the previous element in
the stack. Thus we get the right limit and left limit thus whole breath.
for `2` there is no value before it, so it is smallest till `i`.

```cpp
public int largestRectangleArea(int[] heights) {
        int len = heights.length;
        Stack<Integer> s = new Stack<>();
        int maxArea = 0;
        for (int i = 0; i <= len; i++){
            int h = (i == len ? 0 : heights[i]);
            if (s.isEmpty() || h >= heights[s.peek()]) {
                s.push(i);
            } else {
                int tp = s.pop();
                maxArea = Math.max(maxArea, heights[tp] * (s.isEmpty() ? i : i - 1 - s.peek()));
                i--;
            }
        }
        return maxArea;
    }
```

This is very hard to comeup with.
