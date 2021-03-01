#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <ctime>

#define COUNT 10  

using namespace std;

struct node {
    int value;
    node *left;
    node *right;
};

void insert(node *&root, int value) {
    if (root == NULL) {
        root = new node;
        root->value = value;
        root->left = NULL;
        root->right = NULL;
        return;
    }
    if (root->value == value) return;
    if (root->value > value) {
        if (root->left != NULL) insert(root->left, value);
        else {
            node *new_element = new node;
            new_element->value = value;
            new_element->left = NULL;
            new_element->right = NULL;
            root->left = new_element;
            return;
        }
    }
    if (root->value < value) {
        if (root->right != NULL) insert(root->right, value);
        else {
            node *new_element = new node;
            new_element->value = value;
            new_element->left = NULL;
            new_element->right = NULL;
            root->right = new_element;
            return;
        }
    }
}

void show(node *root, int space)  {  
    if (root == NULL) return;   
    space += COUNT;    
    show(root->right, space);    
    cout << endl;  
    for (int i = COUNT; i < space; i++)  
        cout << " ";  
    cout << root->value << "\n";  
    show(root->left, space);  
}  

int main() {
    srand(time(NULL));
    int i = 1;
    node *root = NULL;

    cout << "How many: ";        
    cin >> i;
    float time1 = clock();
    for (int j = 1; j <= i; j++) insert(root, j);
    float time2 = clock();
    cout << "Time: " << (time2 - time1) / 1000 << endl;
    //show(root, 0);
    return 0;
}