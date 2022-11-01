#pragma once
#include "party.h"
#include <fstream>
#include <cstring>

using namespace std;

class stack
{
public:
    stack(); // default constructor
    stack(const int size); // build stack with a given size
    stack(const int size, party ** partyList); // build a stack with a list
    stack(const stack &aStack); // copy constructor
    ~stack(); // class destructor

    void push(const party &aParty); // push a party to front of stack
    bool pop(party &aParty); // pop the party at the front of the stack off
    bool peek(party &aParty) const; // peek at the top item
    int getSize() const; // get the size of the stack
    bool isEmpty() const; // check if the stack is empty
    void printStack(); // print the values in the stack
    int getTotalItems() const;



    int loadFromFile(const char *filename, stack &); // load a stack from
    // the file
    void saveToFile(const char *filename,  party &aParty) const;
    // save new values to the stack file

    const stack& operator=(const stack &aStack); // overload assignment
    // operator
    friend ostream& operator<<(ostream &, const stack &); // overload outstream

private:
    party ** index;
    const static int INIT_CAP = 20;
    const static int GROWTH_FACTOR = 2;
    int currentSize;
    int top;

    void print(party **); // recursive print the array
    void destroy(); // destroy the array and its pointers
    void grow(); // grow the array if needed.
    void init(stack &);
};