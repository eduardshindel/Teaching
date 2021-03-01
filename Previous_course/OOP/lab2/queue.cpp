#include <iostream>
#include <ctime>

using namespace std;

struct node {
    int value;
    node *next;
};
node *head;

void push(int value) {
    if (head == NULL) {
        node *New_Head = new node;
        New_Head->value = value;
        New_Head->next = NULL;
        head = New_Head;
        return;
    }
    node *New_Elemet = new node;
    New_Elemet->value = value;
    New_Elemet->next = NULL;
    node *Find_Next = head;
    while (Find_Next->next != NULL) Find_Next = Find_Next->next;
    Find_Next->next = New_Elemet;
}

int main() {
    int i, b;
    srand(time(NULL));

    cout << "How many: ";
    cin >> i;
    float time1 = clock();
    for (b = 1; b <= i; b++) push(rand());
    float time2 = clock();
    cout << "Time: " << (time2 - time1) / 1000 << endl;
    return 0;
}