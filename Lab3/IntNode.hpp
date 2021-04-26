struct IntNode
{
private:
    int data;
    IntNode *next;

public:
    IntNode(int i, IntNode *n)
    {
        data = i;
        next = n;
    }

    int getInt()
    {
        return data;
    }

    IntNode *getNext()
    {
        return next;
    }

    ~IntNode()
    {
    }
};
