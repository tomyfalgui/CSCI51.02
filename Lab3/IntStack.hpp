#include <cstddef>
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
            // do nothing
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
};
