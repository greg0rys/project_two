#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"
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
        tail->next = top;
        return top;
    }

    node * temp = new node(aParty);
    temp->next = rear->next;
    rear->next = temp;
    rear = temp;
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
        return false;
    try{
        top = remove(top, aParty);
        return true;
    }
    // to keep our ADT from outputting the message, we will copy it into the
    // errorMsg pointer.
    catch(std::logic_error &error)
    {
        if(errorMsg)
            delete []errorMsg;
        errorMsg = new char[101];
        strcpy(errorMsg, error.what());
        return false;
    }
}


/*
 * Recursive remove the target node from the queues front
 * INPUT: node *& a pointer to the top of the queue, party &aParty, the
 * party we wish to remove, party &partyInfo, the removed parties information.
 * OUTPUT: node * the updated queue.
 */
queue::node * queue::remove(queue::node *&top, party &aParty) noexcept(false)
{
   if(!top)
      throw(std::logic_error("The list is empty"));

   node * toRemove = top;
   aParty = *top->aParty;
   tail->next = top->next;
   top = top->next;
   delete toRemove;

   return top;
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
     int index = 1;

     if(!front)
     {
         return;
     }

    // base case if front = tail then we need to return so we don't loop
    if(front == tail->next)
    {
        cout << "Party " << index << ": " << *front->aParty << endl;
        return;
    }

        cout << "Party " << index << ": " << *front->aParty << endl;
        index++;
        print(front->next);


}


/*
 * overload the == operator to compare if two parties are the same party.
 * if both parties have the same name they are a match
 * OUTPUT: true if the parties have the same name, false if else.
 */
bool operator==(const party &partyA, const party &partyB)
{
    return (strcmp(partyA.partyName, partyB.partyName) == 0);
}



ostream& operator<<(ostream &out, const queue &aQueue)
{
    typedef queue::node node;
    int index = 1;

    for(node * front = aQueue.top; front; front = front->next)
    {
        cout <<"Party " << index << ": " << front->aParty << endl;
        index++;
    }

    return out;
}


#pragma clang diagnostic pop