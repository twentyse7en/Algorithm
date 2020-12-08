<img src="https://user-images.githubusercontent.com/59721339/101490498-6f441380-3988-11eb-92f5-e61f36c393eb.png" align="center" />

```cpp
#include <bits/stdc++.h>
using namespace std;

bool lowerEnd(vector<int> a, vector<int> b)
{
    if(a[1] != b[1])
        return a[1] < b[1];
    return a[2] < b[2];
}

int main()
{
    int S[] = {1,3,3};
    int F[] = {2,5,4};

    vector<vector<int>> meeting;

    int size = sizeof(S)/sizeof(S[0]);

    for(int i = 0; i < size; ++i)
    {
        vector<int> tmp;
        tmp.push_back(S[i]);
        tmp.push_back(F[i]);
        tmp.push_back(i+1);

        meeting.push_back(tmp);
    }

    sort(meeting.begin(), meeting.end(), lowerEnd);

    for(auto x: meeting)
        cout << x[0] << " " << x[1] <<endl;

    cout << "res " << endl;

    int curr_end = meeting[0][1];
    cout << meeting[0][0] << meeting[0][1] << endl;

    for(int i = 1; i < size; ++i)
    {
        if(curr_end < meeting[i][0])
        {
            cout << meeting[i][0] << meeting[i][1] << endl;
            curr_end = meeting[i][1];
        }

    }
}

```
