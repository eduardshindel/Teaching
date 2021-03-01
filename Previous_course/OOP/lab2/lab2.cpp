#include <iostream>
#include <ctime>

using namespace std;

struct Node
{
    int value;
    Node *next;
};
Node *head;

void add(int value) {
    Node *New_Elemet = new Node;
    New_Elemet->value = value;
    New_Elemet->next = head;
    head = New_Elemet;
}

void del(int value)
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

void transfer(int value)
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

int sum()
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
    int i, b;
    srand(time(NULL));

   /* for (i = 0; i < 10; i++) add(i);
    cout << head->value << " " << head->next->value << " " << head->next->next->value <<endl;
    transfer(2);
    cout << head->value << " " << head->next->value << " " << head->next->next->value << endl;
*/
	/*for (b = 0; b<3; b++){
	
	cin >> i;
	add(i);
	};
	cout << head->value << " " << head->next->value << " " << head->next->next->value <<endl;
	
	del(9);
	cout << head->value << " " << head->next->value <<endl;*/

    cout << "How many: ";
    cin >> i;
    float time1 = clock();
    for (b = 1; b <= i; b++) add(rand());
    float time2 = clock();
    cout << "Time: " << (time2 - time1) / 1000 << endl;
	
    return 0;
}
