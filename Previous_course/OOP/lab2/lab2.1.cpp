#include <iostream>

using namespace std;

struct stack {
    int value;
    stack *next;
};
stack *head;

void print() {
    stack *Print_Element = head;
    while (Print_Element != NULL) {
        cout << Print_Element->value << " ";
        Print_Element = Print_Element->next;
    }
    cout << endl;
}

void push(int value) {
    stack *Add_Element = new stack;
    Add_Element->value = value;
    Add_Element->next = head;
    head = Add_Element;
    print();
}

void pop() {
    stack *New_Head = head->next;
    delete head;
    head = New_Head;
    print();
}

int size() {
    stack *target = head;
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

void multipop(int cap)
{
    int i, sizeN = size();
    if (cap > sizeN) cap = sizeN;
    for (i = 0; i < cap; i++) pop();
}

int main()
{
    int i;

    cout << "/*ADD*/\n";
    for (i = 1; i < 11; i++) {
        push(i);
    }
    cout << "\n/*DELETE*/\n";
    for (i = 0; i < 5; i++) {
        pop();
    }
    cout << "\nSize = " << size() << endl;
    print();

    return 0;
}