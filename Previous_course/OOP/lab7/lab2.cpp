#include <iostream>

using namespace std;

class Node
{
    public:
        int value;
        Node *next;
        
        void add(int);
        void del(int);
        void transfer(int);
        int sum();
};
static Node *head;

void Node::add(int value) {
    Node *New_Elemet = new Node;
    New_Elemet->value = value;
    New_Elemet->next = head;
    head = New_Elemet;
}

void Node::del(int value)
{
    Node *Delete_Element = head;
   if (Delete_Element->value == value) {
            Delete_Element = head->next;
            delete head;
            head = Delete_Element;
            return;
        }
    while (Delete_Element->next != NULL) {
        if (Delete_Element->next->value == value) {
            Node *New_Head = Delete_Element->next;
            Delete_Element->next = Delete_Element->next->next;
            New_Head->next = head;
            head = New_Head;
            New_Head = head->next;
            delete head;
            head = New_Head;
        }
        Delete_Element = Delete_Element->next;
    }
}

void Node::transfer(int value)
{
    Node *Find = head;
    while (Find->next != NULL) {
        if (Find->next->value == value) {
            Node *New_Head = Find->next;
            Find->next = Find->next->next;
            New_Head->next = head;
            head = New_Head;
        }
        Find = Find->next;
    }
}

int Node::sum()
{
    int i;
    Node *Sum = head;
    for (i = 1; Sum->next != NULL; i++) {
        Sum = Sum->next;
    }
    return i;
}


int main()
{
    int i;
    Node n;

    for (i = 0; i < 10; i++) n.add(i);
    cout << head->value << " <- " << head->next->value << " <- " << head->next->next->value << "..." <<endl;
    n.transfer(2);
    cout << head->value << " <- " << head->next->value << " <- " << head->next->next->value << "..." << endl;

    return 0;
}