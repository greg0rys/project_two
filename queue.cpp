#include "queue.h"

queue::queue(): top(nullptr),tail(nullptr)
{}


queue::queue(const queue &aCopy): top(nullptr), tail(nullptr)
{
    *this = aCopy;
}


queue::~queue()
{
    destroy(top);
}


void queue::destroy(node *& head)
{
    if(!head)
    {
        return;
    }
    destroy(head->next);
    delete head;
    head = nullptr;
    tail = nullptr;
}


bool queue::isEmpty()
{
    return (top == nullptr);
}


void queue::enqueue(const party &aParty)
{
    top = append(top,aParty);
}


queue::node * queue::append(queue::node *&top, const party& aParty)
{

    if(!top)
    {
        return new node(aParty);
    }
}