# Generate subsets

<img src="https://user-images.githubusercontent.com/59721339/101345541-2bc8a700-38ad-11eb-94ff-14ab59026ccb.png" align="center" />

```cpp
#include <bits/stdc++.h>
using namespace std;

void generateBitMask(vector<vector<int>> &bitmasks, vector<int> partialMask, int len, int curr)
{
    if(len == curr)
    {
        bitmasks.push_back(partialMask);
        return;
    }

    // add the element
    partialMask[curr] = 1;
    generateBitMask(bitmasks, partialMask, len, curr+1);

    // don't add the element
    partialMask[curr] = 0;
    generateBitMask(bitmasks, partialMask, len, curr+1);

}

int main()
{
    int len = 3;
    vector<vector<int>> bitmasks;
    vector<int> partialMask(len, 0);
    
    generateBitMask(bitmasks, partialMask, len, 0);

    for(int i = 0; i < bitmasks.size(); ++i)
    {
        cout << "{" ;
        for(int j = 0; j < bitmasks[i].size(); ++j)
        {
            if(bitmasks[i][j] == 1)
                cout << j + 1 << ",";
        }

        cout << "}" << endl;
    }
}

```
