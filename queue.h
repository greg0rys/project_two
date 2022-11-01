#pragma once
#include <cstring>
#include <cctype>
#include <iostream>
#include "party.h"
#include "stack.h"

using namespace std;

class queue
{
public:
    queue(); // default constructor
    queue(const queue &); // copy constructor
    ~queue(); // class destructor

    int init(queue &); // load the queue with test data
    bool isEmpty(); // check if the queue is empty
    bool enqueue(const party &); // add a party to end of queue
    bool dequeue(party &) noexcept(false); // remove the front party
    bool peekFront(party &); // get a copy of the front party
    void printQueue(); // print the whole queue
    int getCount() const; // get the number of people in the queue.

    int loadfromfile(const char *, queue &); // load data from a file
    friend ostream& operator<<( ostream &out, const queue &aQueue); //
    // overload outstream

private:
    struct node
    {
        party * aParty;
        node * next;

        node():aParty(nullptr), next(nullptr)
        {}

        node(const party &aCopy)
        {
            aParty = new party(aCopy);
            next = nullptr;
        }

        ~node()
        {
            if(aParty)
                delete aParty;
            aParty = nullptr;
            next = nullptr;
        }
    };

    node *front, *tail;
    int count;
    // private method stubs
    node * destroy (node *&); // destroy all the pointers in the queue
    node * append(node *&, const party &); // add a party to end of queue
    void print(node *front); // recursively print the queue
    node * removeFront(node *&, party &); // remove the front party from the
    // queue



};