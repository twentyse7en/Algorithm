<img src="https://user-images.githubusercontent.com/59721339/101616769-cc49d300-3a35-11eb-9519-980008419357.png" align="center" />

```cpp
#include <iostream>
using namespace std;

struct ListNode
{
    int data;
    int size;
    ListNode* next;

    ListNode(int val)
        :data(val), next(NULL)
    {
    }
};

class Queue
{
    private:
        int qsize;
        ListNode* front;
        ListNode* rear;

    public:
        Queue()
            :front(NULL), rear(NULL)
        {}

        void enqueue(int);
        int dequeue();
        bool isEmpty();
        int size();
};

void Queue::enqueue(int val)
{
    // edge case if no item
    if(front == NULL)
    {
        ListNode* tmp = new ListNode(val);
        front = tmp;
        rear = tmp;
        qsize = 1;
    }
    else{
        rear->next = new ListNode(val);
        rear = rear->next;
        qsize += 1;
    }
}

int Queue::dequeue()
{
    // edge case if no elements
    if(qsize == 0)
    {
        cout << "No elements" << endl;
        return INT32_MAX;
    }
    
    int val = front->data;
    ListNode *tmp = front;

    front = front->next;
    delete tmp;

    // SUPER Important: Because it is easy to slip
    if(qsize == 0) rear = NULL;

    return val; 
}

int Queue::size()
{
    return qsize;
}

bool Queue::isEmpty()
{
    return front == NULL;
}


int main()
{
    Queue q;
    q.enqueue(10);
    q.enqueue(20);

    cout << q.dequeue() << endl;
    cout << q.dequeue() << endl;

}

```

## RESOURCE:

[queue and stack](https://introcs.cs.princeton.edu/java/43stack/)
