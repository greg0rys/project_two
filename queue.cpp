#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"
#include "queue.h"

queue::queue(): top(nullptr),tail(nullptr)
{}


queue::queue(const queue &aCopy): top(nullptr), tail(nullptr),count(0)
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


bool queue::enqueue(const party &aParty)
{
    tail = append(tail,aParty);
    return true; // we can just return true, as there is no condition that
    // would prevent a party from being added to the queue
}


/*
 * Recursively append a new party to the end of the queue and update the
 * pointers
 * INPUT: node *&top a pointer reference to the top pointer of the queue
 * party &aParty - a reference to a party joining the queue
 * OUTPUT node * the updated top pointer to the caller.
 */
queue::node * queue::append(queue::node *&rear, const party& aParty)
{
    // base case the queue is empty;

    if(!top)
    {
        node * temp = new node(aParty);
        top = tail = temp;
        top->next = temp;
        tail->next = top;
        count = 1;
        return top;
    }

    node * temp = new node(aParty);
    temp->next = rear->next;
    rear->next = temp;
    rear = temp;
    count++;
    return rear;


}


/*
 * Remove a party from the front of the queue
 * INPUT: party &aParty - the party to remove, party &partyInfo - a copy of
 * the removed pointers information.
 * OUTPUT: true if the operation was a success, false if else.
 */
bool queue::dequeue(party &aParty)
{
    if(isEmpty())
    {
        return false;
    }
    top = removeFront(top, aParty);
    count--;
    return true;
}

queue::node* queue::removeFront(node *& head, party &aParty) {
    if(!head)
    {
        return head;
    }

    if(head == tail)
    {
        delete top;
        top = nullptr;
        return top;
    }

    node * temp = top;
    aParty = *top->aParty;
    top = top->next;
    tail->next = top;
    delete temp;
    return top;
}


int queue::getCount() const {
    return count;
}


bool queue::peekFront(party &aParty)
{
    // if queue isn't empty; copy the top pointer into the param ref.
    if(!isEmpty())
    {
        aParty = *top->aParty;

    }
    // true if the queue isn't empty; false if else.
    return !isEmpty();
}


void queue::printQueue()
{
    print(top);
}


void queue::print(queue::node *front)
{

    // base case we've reached a null place in the list.
    if(!front)
    {
        return;
    }

    // case 2: we've reached the tail of the list, return from here so we
    // don't loop back around
    if(front == tail)
    {
        cout << *(front->aParty) << endl;
        return;
    }

    cout << *(front->aParty) << endl; // print data before recursing so it
    // prints in correct order.
    print(front->next); // print the next party

}


/*
 * todo: move this to party class
 * overload the == operator to compare if two parties are the same party.
 * if both parties have the same name they are a match
 * OUTPUT: true if the parties have the same name, false if else.
 */
bool operator==(const party &partyA, const party &partyB)
{
    return (strcmp(partyA.partyName, partyB.partyName) == 0);
}


/*
 * override the stream insertion operator to output how many people are in
 * the queue at a given time when the queue is called to be printed.
 */
ostream& operator<<(ostream &out, const queue &aQueue)
{
    out << "The queue currently has: " << aQueue.getCount()
        << " people in it" << endl;

    return out;
}


#pragma clang diagnostic pop