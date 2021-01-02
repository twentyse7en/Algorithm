#include<bits/stdc++.h>
using namespace std;

// Time complexity : O(n^2)
// ----------------------------------------

// Insert a single element to end
void addToEnd(stack<int> &s, int temp)
{
    if(s.empty())
    {
        s.push(temp);
        return;
    }

    int x = s.top(); s.pop();
    addToEnd(s, temp);
    s.push(x);
}

// main reversing function
// ----------------------------------------
void reverse_stack(stack<int>& s)
{
    if(s.size() == 1)
        return ;
    
    int temp = s.top();  s.pop();
    
    // revers the remaining part
    reverse_stack(s);

    // insert the current element to the end
    addToEnd(s, temp);
    
    return;
}

int main()
{
    stack<int> s;
    s.push(10);
    s.push(20);
    s.push(30);
    s.push(40);

    while(!s.empty())
        {
            cout << s.top() << " "; s.pop();
        }
    cout << endl;
    
    s.push(10);
    s.push(20);
    s.push(30);
    s.push(40);

    reverse_stack(s);
    
    cout << "After reversing" << endl;

    while(!s.empty())
        {
            cout << s.top() << " "; s.pop();
        }
    cout << endl;
}
