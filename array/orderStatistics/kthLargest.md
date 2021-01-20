# Kth Largest Element

Classic question.

## Naive 
*Time Complexity* : O(nlgn)  (4ms)
*Space Complexity*: CPP uses IntroSort(Quick, Heap, Insertion) I think 
the one with worse space is Quick ranging from O(lgn) to O(N) this is
for the recursion stack. [ref](https://stackoverflow.com/a/15035050)

```cpp
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        return nums[nums.size() - k];
    }
};
```

## Quick Select

*Time Complexity* : O(N) to O(N<sup>2</sup>)  (72ms)
*Space Complexity* : O(lgN) to O(N<sup>2</sup>)

```cpp
class Solution {
public:
    int quickSelect(vector<int>& nums, int low, int high, int k)
    {
        int curr = low;
        for(int i = low; i < high; ++i)
        {
            if(nums[i] <= nums[high])
            {
                swap(nums[i], nums[curr]);
                curr++;
            }
        }
        int diff = high - curr + 1;
        if(diff == k)
            return nums[high];
        
        // it can be on left
        if(k > diff)
            return quickSelect(nums, low, curr-1, k-diff);
        return quickSelect(nums, curr, high-1, k);
            
        
    }
    
    int findKthLargest(vector<int>& nums, int k) {
        return quickSelect(nums, 0, nums.size()-1, k);
    }
};
```

But the extra space can be avoid using iteration.

```cpp
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        k = nums.size() - k; // index of the kth largest
        int l = 0, r = nums.size()-1, pivot;
        
        while(l<=r)
        {
            int i = l;
            // random value is the value@l
            // this is partition
            for(int j = l+1; j <= r; ++j)
                if(nums[j] < nums[l])       // NOTE: we are using < not <=
                    swap(nums[j], nums[++i]);
           // swap back         
           swap(nums[l], nums[i]);
            
           if(k == i)         
               return nums[i];
           else if(k < i) 
               r = i - 1;
           else
               l = i + 1;      
        }
        return -1;
    }
};
```

## Min-Heap
I like this solution
*time complexity* : O(nlogk)   (8ms)
*space complexity* : O(k)

```cpp
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        priority_queue<int, vector<int>, greater<int>> min_heap;
        for(int i = 0; i < nums.size(); ++i)
        {
            min_heap.push(nums[i]);
            if(min_heap.size() > k)
                min_heap.pop();
        }
        return min_heap.top();
    }
};
```

## Builtin - fn

*time complexity*: average O(n)  // (4ms)
*space complexity* : O(last - first)

```cpp
class Solution {
public:
    static bool compare(int i, int j)
    {
        return i > j;
    }
    int findKthLargest(vector<int>& nums, int k) {
        // nth element will be in the correct place
        nth_element(nums.begin(), nums.begin()+k-1, nums.end(), compare);
        return nums[k-1];
    }
};
```
