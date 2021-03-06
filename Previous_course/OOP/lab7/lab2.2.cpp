#include <iostream>

using namespace std;

class node {
    private:
        int value;
        int pr;
        node *next;
    public:
        void print();
        void push(int, int);
        void pop();
        int size();
        void multipop(int);
};
static node *head;

void node::print() {
    node *Print_Element = head;
    while (Print_Element != NULL) {
        cout << Print_Element->value << "(" << Print_Element->pr << ")" << " <- ";
        Print_Element = Print_Element->next;
    }
    cout << "NULL" << endl;
}

void node::push(int value, int pr) {
    if (head == NULL) {
        node *New_Head = new node;
        New_Head->value = value;
        New_Head->pr = pr;
        New_Head->next = NULL;
        head = New_Head;
        print();
        return;
    }
    node *target = head->next;
    node* prev = head;
    node *Add_Element = new node;
    Add_Element->value = value;
    Add_Element->pr = pr;
    if (head == NULL) {
        Add_Element->next = NULL;
        head = Add_Element;
        print();
        return;
    }
    if (head->pr < Add_Element->pr) {
        Add_Element->next = head;
        head = Add_Element;
        print();
        return;
    }
    while (1) {
        if (target == NULL) {
            prev->next = Add_Element;
            Add_Element->next = NULL;
            print();
            return;
        }
        if (target->pr < Add_Element->pr) {
            prev->next = Add_Element;
            Add_Element->next = target;
            print();
            return;
        }
        target = target->next;
        prev = prev->next;
    }
}

void node::pop()
{
    node *New_Head = head->next;
    delete head;
    head = New_Head;
    print();
}

int node::size()
{
    node *target = head;
    int s = 0;
    if (target != NULL) {
        s = 1;
        while (target->next != NULL) {
            s++;
            target = target->next;
        }
    }
    return s;
}

void node::multipop(int cap)
{
    int i, sizeN = size();
    if (cap > sizeN) cap = sizeN;
    for (i = 0; i < cap; i++) pop();
}

int main()
{    
    int i;
    node n;
    //cout << "/*ADD*/\n";
   /* for (i = 1; i < 11; i++) {
        push(i, i);
    }*/
   // cout << "\n/*DELETE*/\n";
   /* for (i = 0; i < 5; i++) {
        pop();
    }
    cout << "\nSize = " << size() << endl;
    print();*/
    n.push(9, 3);
    n.push(7, 10);
    n.push(8,9);
    n.push(10, 20);
    n.push(1, 1);
    n.pop();
    return 0;
}