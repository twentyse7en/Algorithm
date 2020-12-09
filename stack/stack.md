<img src="https://user-images.githubusercontent.com/59721339/101596119-8a5f6380-3a1a-11eb-8db9-477b6e7ba31d.png" align="center" />

```cpp
#include <iostream>
using namespace std;

#define MAX 100
class Stack{
    private:
        int A[MAX];
        int top;

    public:
        Stack()
            : top(-1)
        {}

        bool push(int);
        bool isEmpty();
        int pop();
        int peek();
};

bool Stack::push(int x)
{
    // check overflow then push
    if(top > MAX-1)
    {
        cout << "OVERFLOW" << endl;
        return false;
    }

    A[++top] = x;
    return true;
}

int Stack::pop()
{
    // check underflow then pop
    if(top < 0)
    {
        cout << "Underflow " << endl;
        return 0;
    }

    return A[top--];
}

bool Stack::isEmpty()
{
    return top == -1;
}

int Stack::peek()
{
    if(top < 0)
    {
        cout << "Underflow" << endl;
        return 0;
    }

    return A[top];
}

int main()
{
    Stack s;
    s.push(10);
    s.push(20);
    cout << s.pop() << endl;
    cout << s.peek() << endl;
    cout << s.pop() << endl;
    cout << s.isEmpty() << endl;
}

```


```cpp
#include<iostream>
using namespace std;

struct LinkedList
{
    int x;
    LinkedList* prev;

    LinkedList(int data)
        :x(data), prev(NULL)
    {}
};


class Stack{

    private:
        LinkedList* head;

    public:
        Stack()
            :head(NULL)
        {  }

        bool push(int val);
        int pop();
};

bool Stack::push(int val)
{
    // no-overflow
    LinkedList* tmp = new LinkedList(val);
    tmp->prev = head;
    head = tmp;
    return true;
}

int Stack::pop()
{
    // check underflow
    if(head == NULL)
    {
        cout << "Underflow" << endl;
        return 0;
    }

    int val = head->x;
    LinkedList* prev = head->prev;
    // deallocate the memory
    delete head;
    // assign value to prev
    head = prev;
    return val;
}

int main()
{
    Stack s;
    s.push(10);
    s.push(20);
    s.push(30);

    cout << s.pop() << endl;
    cout << s.pop() << endl;
    cout << s.pop() << endl;
    cout << s.pop() << endl;
}

```
