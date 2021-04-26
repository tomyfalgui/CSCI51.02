#include "IntStack.hpp"
#include <iostream>
using namespace std;

void traverseLinkedList(IntNode *in)
{
    while (in != NULL)
    {
        cout << (*in).getInt() << " ";
        in = (*in).getNext();
    }
}

int main(void)
{
    // implement node struct [x]
    // implement a linked list but it's not quite a stack
    // creation and traversal
    IntNode *third = new IntNode(3, NULL);
    IntNode *second = new IntNode(2, third);
    IntNode *head = new IntNode(1, second);
    cout << "Linked List Traversal" << endl;
    traverseLinkedList(head);
    //Implemented an IntStack struct (including push and pop functions).
    cout << "\nStack" << endl;
    IntStack *stack = new IntStack();
    cout << "PUSHING" << endl;
    for (int i = 1; i < 10; i++)
    {
        cout << i << " ";
        (*stack).push(i);
    }
    // should print 9 8 7 ... 1
    cout << "\nPopping" << endl;
    for (int i = 1; i < 10; i++)
    {
        cout << (*stack).pop() << " ";
    }

    delete stack;
    delete head;
    delete second;
    delete third;
    return 0;
}