# No of Students unable to eat

[problem statement](https://leetcode.com/problems/number-of-students-unable-to-eat-lunch/submissions/)

## Intuition

I underestimated the question, but this is actual good. The point that 
I missed while interpreting the question was if the top of the stack contain
a food nobody in the queue want to eat then every one in the queue is
unable to eat.

## Approach 1

Straight forward simulation, key point to avoid the infinity loop is to
keep track of the no. of students. 

```cpp
class Solution {
public:
    int countStudents(vector<int>& students, vector<int>& sand) {
        // To avoid inf loop : have the count of the student
        // even if someone go to end, somebody should eat the top
        int count[] = {0, 0};
        queue<int> q;
        for(int x: students)
        {
            q.push(x);
            count[x]++;
        }
        
        // stack
        reverse(sand.begin(), sand.end());
        
        while(sand.size() && count[sand.back()])
        {
            // eat if top match
            if(sand.back() == q.front())
            {
                count[sand.back()]--;
                q.pop();
                sand.pop_back();
            }
            else{
                // append to back
                q.push(q.front());
                q.pop();
            }
        }
        
        // know simulate 
        
        
        return q.size();
    }
};
```

As this is simulation I'm not sure how to come up with a time complexity.

## Approach 2

I'm impressed with this  little trick. We don't actual need a queue. The 
order doesn't matter, what matter is the no. of students.

```cpp
class Solution {
public:
    int countStudents(vector<int>& students, vector<int>& s) {
        
        // count the no. of students
        int count[] = {0, 0};
        
        for(int x: students)
            count[x]++;
        
        int k = 0;
        for(; k < students.size() && count[s[k]] > 0; ++k)
        {
            count[s[k]]--;
        }
        
        return students.size() - k;
    }
};
```

Time complexity: O(n)

Space complexity : O(1)
