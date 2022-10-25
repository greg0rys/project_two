#include "stack.h"

stack::stack(): top(0)
{
    currentSize = INIT_CAP;
    index = new party *[currentSize];

    for(auto i = 0; i < currentSize; i++)
        index[i] = nullptr;
}

/*
 * create a stack with a prebuilt array of pointers to parties
 * currentSize will be the size of the prebuilt array being passed in
 * we will then copy them all into the index pointer.
 */
stack::stack(const int size, party **partyList):top(0),currentSize(size)
{
    index = new party *[currentSize];
    for(auto i = 0; i < currentSize; i++)
        index[i] = new party(*partyList[i]);
}

stack::stack(const int size):top(0),currentSize(size)
{
    index = new party *[currentSize];

    for(auto i = 0; i < currentSize; i ++)
        index[i] = nullptr;
}


stack::stack(const stack &aStack):index(nullptr),top(0)
{
    *this = aStack;
}


stack::~stack()
{
    destroy();
}


void stack::destroy()
{
    for(auto i = 0; i < top; i++)
    {
        if(index[i]) // delete the pointer in the array
            delete index[i];
    }

    if(index)
        delete []index; // delete the array
}


void stack::push(const party &aParty)
{
    if(currentSize == top)
        grow();
    index[top] = new party(aParty);
    top++;
}


bool stack::pop(party &aParty)
{
    if(top == 0)
        return false;

    aParty = *(index[top - 1]);
    delete index[top - 1];
    top--;
    return true;
}


bool stack::peek(party &aParty) const
{
    if(top == 0)
        return false;
    aParty = *(index[top - 1]);
    return true;
}



int stack::getSize() const
{
    return currentSize;
}



bool stack::isEmpty() const
{
    return index == nullptr;
}


void stack::grow()
{
    currentSize *= GROWTH_FACTOR;
    auto ** tempStack = new party*[currentSize];

    for(auto i = 0; i < top; i++)
        // copy only pointers
        tempStack[i] = index[i];
    delete []index;
    index = tempStack;


}

void stack::loadFromFile(const char *filename)
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

    file.get(partyName,MAX_CHAR,';');

    while(!file.eof())
    {
        file.get();
        file.get(specialSeats, MAX_CHAR, ';');
        file.get();
        file.get(email, MAX_CHAR, ';');
        file >> partySize;
        file.ignore(MAX_CHAR,'\n');
        file.get(promos, MAX_CHAR, '\n');
        if(strcmp(promos, "true") == 0)
        {
            wantPromos = true;
        }
        else
        {
            wantPromos = false;
        }

        party newParty(partyName, partySize, specialSeats, email, wantPromos);
        push(newParty);
        totalLoaded++;
        file.get(partyName, MAX_CHAR, ';');
    }
    file.close();
}


const stack& stack::operator=(const stack &aStack)
{
    if(this == &aStack)
        return *this;
    destroy(); // clear out any values already in this stack
    top = aStack.top;
    currentSize = aStack.currentSize;
    index = new party *[currentSize];

    for(auto i = 0; i < top; i++)
        index[i] = new party(*aStack.index[i]);

    return *this;
}