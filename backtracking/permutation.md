## Permutation

This is very straight if you think about backtracking.

```cpp
    #include <bits/stdc++.h>
    using namespace std;

    void generatePermutation(vector<int> bitmask,int arr[],int &len,vector<int> partialAns)
    {
        if(partialAns.size() == len)
        {
            cout << "{ ";
            for(int x: partialAns)
                cout << x << ", " ;
            cout << "}" << endl;
        }

        for(int i = 0; i < len; ++i)
        {
            // It ain't visited
            if(bitmask[i] == 1)
            {
                // add that to the partial ans
                partialAns.push_back(arr[i]);
                bitmask[i] = 0;
                generatePermutation(bitmask, arr, len, partialAns);

                // undo the last move
                partialAns.pop_back();
                bitmask[i] = 1;
            }

        }
    }

    int main()
    {
        int len =  4;
        vector<int> bitmask(len, 1);
        int arr[] = {1, 2, 3, 4};
        vector<int> partialAns;

        generatePermutation(bitmask, arr, len, partialAns);
    }

```
