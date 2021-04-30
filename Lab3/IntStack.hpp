#include <cstddef>
#include <cstdio>
#include <iostream>
#include "IntNode.hpp"

struct IntStack
{
private:
    IntNode *top;

public:
    IntStack()
    {
        top = NULL;
    }

    void push(int i)
    {
        top = new IntNode(i, top);
    }

    int pop()
    {
        if (top == NULL)
        {
            printf("No More top");
            // do nothing
            exit(1);
        }
        else
        {
            int value = (*top).getInt();
            IntNode *newTop = (*top).getNext();
            delete top;
            top = newTop;
            return value;
        }
    }

    ~IntStack()
    {
        while (top != NULL)
        {
            IntNode *temp = top;
            top = (*top).getNext();
            delete temp;
            temp = NULL;
        }
    }
};
