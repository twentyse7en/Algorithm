# N - Queens problem

this time start from my dumb idea to a better idea, not mine but someone else.

<img src="https://user-images.githubusercontent.com/59721339/101376150-3a778400-38d6-11eb-9cef-83eaa0e049b0.png" align="center" />
<img src="https://user-images.githubusercontent.com/59721339/101380039-02bf0b00-38db-11eb-89df-ec69f724dbfd.png" align="center" />
<img src="https://user-images.githubusercontent.com/59721339/101449323-941b9500-394e-11eb-94b3-6e2ee6d7527f.png" align="center" />


## Coding time.

This is perfect solution time complexity n! <br/>
There is N possibilities to put the first queen, not more than N (N - 2) to put the second one, not more than N(N - 2)(N - 4) for the third one etc. In total that results in O(N!) time complexity.
Space complexity : O(N) to keep an information about diagonals and rows.

// #NOTE: the actual trick here is checking the diagonals in o(1). 

```cpp
#include <bits/stdc++.h>
using namespace std;

struct flag{
        int N;
        vector<int> col;
        vector<int> diag;
        vector<int> anti_diag;

        flag(int n)
        :N(n), col(n, 1), diag(2*n -1, 1), anti_diag(2*n -1, 1) 
        {  }

        bool isvalid(int r, int c)
        {
            return col[c] && diag[r + c] && anti_diag[r - c + N - 1] ;
        }

        void addQueen(int r, int c)
        {
            col[c] = 0;
            diag[r + c] = 0;
            anti_diag[r - c + N -1] = 0;
        }
        
        void remQueen(int r, int c)
        {
            col[c] = 1;
            diag[r + c] = 1;
            anti_diag[r - c + N -1] = 1;
        }
};

void solve(vector<vector<string>> &res, vector<string> board, int row, int n, flag f)
{
    if(row == n)
    {
        for(string s: board)
            cout << s << endl;

        res.push_back(board);
    }


    for(int col = 0; col < n; ++col)
    {
        // check the three condition
        if(f.isvalid(row, col))
        {
            f.addQueen(row, col);
            board[row][col] = 'Q';

            // try for more solution
            solve(res, board, row+1, n, f);

            // backtrack
            f.remQueen(row, col);
            board[row][col] = '.';
        }
    }
}

int main()
{
    int n = 4;
    vector<vector<string>> res;
    vector<string> board(n, string(n, '.'));

    // track the following
    flag f(n);
    solve(res, board, 0, n, f);
    
}

```

// # naive approach for checking the diagonals
```cpp
        for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; --i, --j)
            if (nQueens[i][j] == 'Q')
                return false;
        //check if the 135° diagonal had a queen before.
        for (int i = row - 1, j = col + 1; i >= 0 && j < n; --i, ++j)
            if (nQueens[i][j] == 'Q')
                return false;
```
