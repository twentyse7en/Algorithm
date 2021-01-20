#include<bits/stdc++.h>
using namespace std;


struct node{
    node* next;
    int data;

    node(int x)
    {
        data = x;
    }
};

void append(int x, node* head)
{
    // create new node 
    node*  tmp = new node(x);
    node*  curr = head;
    while(curr->next)
        curr = curr->next;
    curr->next = tmp;
}

// Time complexity : O(N)
// Space complexity: O(N)
// ----------------------------------------------
node* rem_dup(node* head)
{
    unordered_set<int> s;
    node* tmp = head;
    node* prev;
    while(tmp)
    {
        int data = tmp->data;
        if(s.find(data) != s.end())
        {
            //duplicates
            prev->next = tmp->next;
            tmp = tmp->next;
        }
        else{
            //  insert to s
            s.insert(data);
            prev = tmp;
            tmp = tmp->next;
        }
    }
    return head;
}

//-- No extra space -----------------
// 
node* rem(node* head)
{
    node* tmp = head;
    node *prev, *curr;
    while(tmp)
    {
        prev = tmp;
        curr = tmp->next;
        while(curr)
        {
            if(curr->data == tmp->data)
            {
                prev->next = curr->next;
                curr = curr->next;
                cout << "removing " << tmp->data << endl;
            }
            else
            {
                prev = curr;
                curr = curr->next;
            }
        }
        tmp = tmp->next;
        
    }
    return head;
}

int main()
{
    node* head = new node(2);
    append(2, head);
    append(2, head);
    append(2, head);
    head = rem(head);
    while(head)
    {
        cout << head->data << endl;
        head = head->next;
    }
}
