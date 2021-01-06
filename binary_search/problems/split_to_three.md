# Ways to Split Array Into Three Subarrays



-    Make a prefix sum array.
-     Now start traversing the array and assume the sum[i] to be the sum of 'left' array.
-    The 'middle' array has to be atleast this sum so use binary search over the prefix sum array to find the starting value
-    The maximum possible value for the 'middle' array is the (sum of array - left array sum)/2 again find the ending value using the binary search.
-    Having the starting and ending possible indexes of 'middle' array we will add the count to the final answer.

The key here is to identify the max and min value of possible second split which gives second and third subarray. I have already 
seen the prefix array concept but this application didn't get into mind.

```cpp
int waysToSplit(vector<int>& nums) 
{
	long result=0,n=nums.size(),d=1000000007;
	for(int i=1;i<n;i++) nums[i]+=nums[i-1]; //use nums for prefix sum to save space

	for(int i=0;i<n;i++)
	{
		if(nums[i]>nums.back()/3) break; //so that sum(subarray1)<=sum(nums)/3

        // both elements will not be in the n-1 position
		vector<int>::iterator low=lower_bound(nums.begin()+i+1,nums.end()-1,2*nums[i]); //so sum(subarray2)>=sum(subarray1)
		vector<int>::iterator up=upper_bound(low,nums.end()-1,nums[i]+(nums.back()-nums[i])/2); //so that sum(subarray2)<=sum(subarray3)
		result=(result+up-low)%d;
	}
	return result;
}
```

Below is a slightly different implementation of same logic.

```cpp
class Solution {
public:
    int waysToSplit(vector<int>& nums) {
        
        int n = nums.size();
        int mod = 1e9 +  7;
        int res = 0;
        
        
        // calculate prefix sum
        vector<int> prefixArr(n);
        prefixArr[0] = nums[0];
        for(int i = 1; i < n; ++i)
            prefixArr[i] = prefixArr[i-1] + nums[i];
        
        // we need two splits to get the 3 array
        // we will fix first one and try to find the second one
        for(int i = 0; i < n; ++i)
        {
            // split will be on i + 1;
            int sumArr1 = prefixArr[i];
            int remaining = prefixArr.back() - sumArr1;
            
            // min val of sumArr2 is sumArr1
            // thus sum of arr till it will sumArr1*2
            // this will lower bound
            // search from next positon from first arrray
            int low = lower_bound(prefixArr.begin() + i + 1, prefixArr.end(), sumArr1*2) - prefixArr.begin();
            
            // next we need the upper bound the last element which satisfy the condition
            // upper_bound strictly greater than value | +1 what we are seeking
            // sumArr2 = sumArr3 is the last possible value for sumArr2
            // whole remaining sum after the - sumArr1 /2 will give you boundary
            // IMP: It can't be the last index, then there will be empty array for last one
            int upper = upper_bound(prefixArr.begin() + i + 1 , prefixArr.begin()+n-1, sumArr1 + (remaining)/2) - prefixArr.begin(); 
            
            // if we have the upper and low then we can have any index as the starting split
            // I didn't exactly gone through the edge cases and worked out the problem
            res += (max(upper - low, 0)) % mod;
            
            res %= mod;
        }
        
        return res;
    }
};
```
