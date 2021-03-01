#include <iostream>

using namespace std;

class stack {
    private:
        int value;
        stack *next;
    public:
        void print();
        void push(int);
        void pop();
        int size();
        void multipop(int);
};
static stack *head;

void stack::print() {
    stack *Print_Element = head;
    while (Print_Element != NULL) {
        cout << Print_Element->value << " ";
        Print_Element = Print_Element->next;
    }
    cout << endl;
}

void stack::push(int value) {
    stack *Add_Element = new stack;
    Add_Element->value = value;
    Add_Element->next = head;
    head = Add_Element;
    print();
}

void stack::pop() {
    stack *New_Head = head->next;
    delete head;
    head = New_Head;
    print();
}

int stack::size() {
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

void stack::multipop(int cap)
{
    int i, sizeN = size();
    if (cap > sizeN) cap = sizeN;
    for (i = 0; i < cap; i++) pop();
}

int main()
{
    int i;

    stack st;

    cout << "/*ADD*/\n";
    for (i = 1; i < 11; i++) {
        st.push(i);
    }
    cout << "\n/*DELETE*/\n";
    for (i = 0; i < 5; i++) {
        st.pop();
    }
    cout << "\nSize = " << st.size() << endl;
    st.print();

    return 0;
}