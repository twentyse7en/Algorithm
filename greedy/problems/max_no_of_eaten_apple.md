# Maximum No of eaten apples

[problem statemet](https://leetcode.com/problems/maximum-number-of-eaten-apples/)

## Implementation

Well I tried to come up with a solution, which was reasonable. But it
was getting wrong answer on submitting. I tedious to debug. When we come up 
with implementation, try to reduce the code, which helps during debugging and
less error while implementing.

This has is good problem, for exercising implementation. I was able to come
up with priority queue, but it is okay to have duplicates here, that was 
a key point.

**Side note** : `priority_queue` in cpp is *max heap*, so we need to do
a hack to make this *min heap*, this is very necessary in the toolbox.

```cpp
// min heap
priority_queue<int, vector<int>, greater<int>> min_heap;

// max heap
priority_queue<int> max_heap;
```

<details>
<summary>
This is my code, this gave my WA, see how much conditions it have to check
</summary>

```cpp
class Solution {
public:
    int eatenApples(vector<int>& apples, vector<int>& days) {
        unordered_map<int, int> umap;
        priority_queue<int, vector<int>, greater<int>> pq;
        
        int count = 0;
        int idx;
        for(idx = 0; idx < apples.size(); ++idx)
        {
            // check if we have something today to eat
            if(umap.find(idx) != umap.end() && umap[idx] > 0)
                count++;
            else if(apples[idx] > 0)
            {
                // still we haven't eaten any thing, but we have somthing to eat
                count++;
                apples[idx]--;
                
                // also save remaining apples
                if(apples[idx] > 0 && days[idx] > 1)
                {
                    umap[idx + days[idx] - 1] += apples[idx];
                    pq.push(idx + days[idx] -1); // this may cause duplicates
                }

            }
            else {
                // still we haven't eaten anything
                // only hope is future reserve
                // if anything exist in the future can be consumed
                while(!pq.empty())
                {
                    int day = pq.top();
                    if(day < idx)
                        pq.pop();
                    else{
                        if(umap[day] > 0)
                        {
                            // yeah we got some thing
                            umap[day]--;
                            count++;
                            break;
                        }
                        else{
                            // nothing exist
                            pq.pop();
                        }
                    }
                }
            }
        }
        
        while(!pq.empty())
        {
            int day = pq.top();
           // printf("day : %d apple : %d\n", day, umap[day]);
            if(day < idx)
                pq.pop();
            else if(umap[day] > 0)
            {
                umap[day]--;
                count++;
                idx++;
            }
            else{
                pq.pop();
            }
        }
        
        return count;
    }
};
```

</details>

This is working solution and has less condition.

- Add the apples
- Remove the expired
- Take the apple if existed. 

Very clean and concise, But there is flaw in time complexity. 
We can converge to solution faster after the iteration through the 
arrays are complete. 
ex: in `[2000], [2000]` there will be 2000 iteration, but we can converge
faster, after 1 iteration we can directly add the remaining values.

<details>
<summary> Slower solution </summary>

```cpp
class Solution {
public:
    
    typedef pair<int, int> pii;
    
    int eatenApples(vector<int>& apples, vector<int>& days) {
        
        // we need min heap this is the key 
        // <expiry_date, apples>
        priority_queue<pii, vector<pii>, greater<pii>> min_heap;
        int n = days.size(); 
        int count = 0;
        
        for(int day = 0; day < n || min_heap.size(); ++day)
        {
            // add the apples if exist 
            // also if it is apple season
            if(day < n && apples[day] > 0)
            {
                int expiry_date = days[day] + day - 1;
                min_heap.push({expiry_date, apples[day]});
            }
             
           // remove all expired one 
            while(min_heap.size())
            {
                if(min_heap.top().first < day)
                    min_heap.pop();
                else
                    break;
            }
            
            // get the apple
            if(min_heap.size())
            {
                pii apple = min_heap.top(); min_heap.pop();
                count++;
                if(apple.second > 1)
                    min_heap.push({apple.first, apple.second - 1});
            }
        }
        
        return count;
        
    }
};
```

</details>

<details>
<summary> More faster solution </summary>
```cpp
class Solution {
public:
    
    typedef pair<int, int> pii;
    
    int eatenApples(vector<int>& apples, vector<int>& days) {
        
        // we need min heap this is the key 
        // <expiry_date, apples>
        priority_queue<pii, vector<pii>, greater<pii>> min_heap;
        int n = days.size(); 
        int count = 0;
        int day; 
        for(day = 0; day < n; ++day)
        {
            // add the apples if exist 
            // also if it is apple season
            if(apples[day] > 0)
            {
                int expiry_date = days[day] + day - 1;
                min_heap.push({expiry_date, apples[day]});
            }
             
           // remove all expired one 
            while(min_heap.size())
            {
                if(min_heap.top().first < day)
                    min_heap.pop();
                else
                    break;
            }
            
            // get the apple
            if(min_heap.size())
            {
                pii apple = min_heap.top(); min_heap.pop();
                count++;
                if(apple.second > 1)
                    min_heap.push({apple.first, apple.second - 1});
            }
        }
        // here we complete the n days, still there could be apples
       // as there aren't any apple produced we can converge to answer fastly 
        while(min_heap.size())
        {
            // remove the expired
            while(min_heap.size())
            {
                if(min_heap.top().first < day)
                    min_heap.pop();
                else
                    break;
            }
            
            // consume entirely 
            if(min_heap.size())
            {
                pii apple = min_heap.top(); min_heap.pop();
                
                int exp = apple.first; 
                int quantity = apple.second;
                
                //input [2000] : min_heap <2, 2000> only consume 2 apples
                if(exp - day + 1 < quantity)
                {
                    count += exp - day + 1; 
                    day = exp + 1;
                }
                else
                {
                    count += quantity;
                    day += quantity;
                }
            }
        }
        
        return count;
        
    }
};
```
</details>

## Complexity

Time complexity : O(n\*lg(n))

Space complexity : O(n)
