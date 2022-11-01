#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"
#include "queue.h"

queue::queue(): front(nullptr), tail(nullptr), count(0)
{
    init(*this);
}


/*
 * load test data into the queue.
 */
void queue::init(queue &theQ)
{
   loadfromfile("queue.txt", theQ);
}

queue::queue(const queue &aCopy): front(nullptr), tail(nullptr), count(0)
{
    *this = aCopy;
}


queue::~queue()
{
    destroy(front);
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

int queue::loadfromfile(const char *filename, queue &theQ)
{
    fstream file(filename);
    int totalLoaded = 0;
    const int MAX_CHAR = 101;
    char partyName[MAX_CHAR];
    char specialSeats[MAX_CHAR];
    char email[MAX_CHAR];
    int partySize;
    char promos[MAX_CHAR];
    bool wantPromos; // can be set using strcmp on read
    static int call_count = 0;

    if(call_count < 1)
    {
        cout << (!file ? "Error! " : "Success: ") << (!file ? "failed to open "
                                                            : "loading from ") << filename << endl;
        call_count++;
    }

    if(!file)
    {
        return 0;
    }

    file.get(partyName,MAX_CHAR,';');

    while(!file.eof())
    {
        file.get();
        file.get(specialSeats, MAX_CHAR, ';');
        file.get();
        file.get(email, MAX_CHAR, ';');
        file.get();
        file >> partySize;
        file.ignore(MAX_CHAR,';');
        file.get(promos, MAX_CHAR, '\n');
        file.ignore(MAX_CHAR, '\n');
        // set true if promos in CSV is 'true' else set false.
        wantPromos = (strcmp(promos, "true") == 0);

        party newParty(partyName, partySize, specialSeats, email, wantPromos);
        theQ.enqueue(newParty);
        totalLoaded++;
        file.get(partyName, MAX_CHAR, ';');
    }
    file.close();

    return totalLoaded;
}

bool queue::isEmpty()
{
    return (front == nullptr);
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
 * INPUT: node *&front a pointer reference to the front pointer of the queue
 * party &aParty - a reference to a party joining the queue
 * OUTPUT node * the updated front pointer to the caller.
 */
queue::node * queue::append(queue::node *&rear, const party& aParty)
{
    // base case the queue is empty;

    if(!front)
    {
        node * temp = new node(aParty);
        front = tail = temp;
        front->next = temp;
        tail->next = front;
        count = 1;
        return front;
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
    front = removeFront(front, aParty);
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
        delete front;
        front = nullptr;
        return front;
    }

    node * temp = front;
    aParty = *front->aParty;
    front = front->next;
    tail->next = front;
    delete temp;
    return front;
}


int queue::getCount() const {
    return count;
}


bool queue::peekFront(party &aParty)
{
    // if queue isn't empty; copy the front pointer into the param ref.
    if(!isEmpty())
    {
        aParty = *front->aParty;

    }
    // true if the queue isn't empty; false if else.
    return !isEmpty();
}


void queue::printQueue()
{
    print(front);
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