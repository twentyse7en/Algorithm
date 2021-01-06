#include<iostream>
using namespace std;

void print_no(int n, int curr)
{
    if(n < curr)
        return;

    cout << curr << endl; 
    print_no(n, curr+1);
}

void print(int n)
{
    // base
    if(n == 0)
        return;
    
    // hypothesis
    print(n - 1);

    // induction
    cout << n << endl;
}

int main()
{
    int n = 10;
    /* print_no(n, 1); */
    print(n);
}
