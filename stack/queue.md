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

## Queue using array

<img src="https://user-images.githubusercontent.com/59721339/101622048-952af000-3a3c-11eb-8e29-24943b35e165.png" align="center" />

```cpp
#include <cstdint>
#include<iostream>
using namespace std;


// cicular implementation
class Queue
{
    private:
        int size;
        int max_capacity;
        int* arr;
        int front;
        int rear;

    public:
        Queue(int capacity)
            :max_capacity(capacity), arr(new int[capacity]), size(0), front(-1), rear(-1)
        {}

        void enqueue(int);
        int dequeue();
        bool isFull();
        bool isEmpty();
};

bool Queue::isFull()
{
    return size == max_capacity;
}

bool Queue::isEmpty()
{
    return size == 0;
}

void Queue::enqueue(int val)
{
    if(isFull())
    {
        cout << "Max capacity reached" << endl;
        return;
    }

    rear = (rear + 1) % max_capacity;
    arr[rear] = val;
    size += 1;

    cout << "Inserted @" << rear << endl;
}

int Queue::dequeue()
{
    if(isEmpty())
    {
        cout << "Queue is empty" << endl;
        return INT32_MAX;
    }

    int val = arr[front];
    front++;
    size--;
    if(isEmpty())
    {
        front = -1;
        rear = -1;
    }
   
    return val;
}


int main()
{
    Queue q(2);

    q.dequeue();
    q.enqueue(10);
    q.enqueue(20);
    q.dequeue();
    q.dequeue();
    q.enqueue(40);
    q.dequeue();
}

```

## RESOURCE:

[queue and stack](https://introcs.cs.princeton.edu/java/43stack/)
