#pragma once
#include "party.h"
#include <fstream>
#include <cstring>

using namespace std;

class stack
{
public:
    stack();
    stack(const int size);
    stack(const int size, party ** partyList);
    stack(const stack &aStack);
    ~stack();

    void push(const party &aParty);
    bool pop(party &aParty);
    bool peek(party &aParty) const;
    int getSize() const;
    bool isEmpty() const;
    void printStack();


    int loadFromFile(const char *filename, stack &);
    void saveToFile(const char *filename,  party &aParty) const;

    const stack& operator=(const stack &aStack);
    friend ostream& operator<<(ostream &, const stack &);

private:
    party ** index;
    const static int INIT_CAP = 20;
    const static int GROWTH_FACTOR = 2;
    int currentSize;
    int top;

    void print(party **);
    void destroy();
    void grow();
    int getTotalItems() const;
};