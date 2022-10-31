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
    // growth strategy grow array by 2x its size.
    currentSize *= GROWTH_FACTOR;
    auto ** tempStack = new party*[currentSize];

    for(auto i = 0; i < top; i++)
        // copy only pointers
        tempStack[i] = index[i];
    delete []index;
    index = tempStack;


}


int stack::getTotalItems() const
{
    int totalItems = 0;
    for(auto i = 0; i < top; i++)
    {
        totalItems++;
    }

    return totalItems;
}


void stack::printStack()
{
    if(isEmpty())
    {
        return;
    }
    print(index);

}


void stack::print(party **array)
{
    typedef char* charP;
    charP partyName = nullptr;
    charP email = nullptr;
    party aParty;
    int count = 0;
    cout << "****** Customers to contact ****** " << endl;
    for(auto i = 0; i < top; i++)
    {
        aParty = *(index[i]);
        cout << aParty;
    }
}

int stack::loadFromFile(const char *filename, stack& aStack)
{

    fstream file(filename);
    int totalLoaded = 0;
    const int MAX_CHAR = 101;
    char partyName[MAX_CHAR];
    char email[MAX_CHAR];
    party newParty;

    cout << (!file ? "Error! " : "Success: ") << (!file ? "failed to open "
    : "loading from ") << filename << endl;
    if(!file)
    {
        return 0;
    }
    file.get(partyName,MAX_CHAR,';');

    while(!file.eof())
    {
        file.get();
        file.get(email, MAX_CHAR, '\n');

        // set true if promos in CSV is 'true' else set false.
        newParty.setPartyName(partyName);
        newParty.setEmail(email);
        cout << newParty << endl;
        aStack.push(newParty);
        totalLoaded++;
        file.get(partyName, MAX_CHAR, ';');
    }
    file.close();

    return totalLoaded;
}


void stack::saveToFile(const char *filename,  party &aParty) const
{
    ofstream file(filename, std::ios_base::app); // append to the file
    char * pName = nullptr;
    char * email = nullptr;
    pName = new char[aParty.getPartyNameLength() + 1];
    email = new char[aParty.getPartyEmailLength() + 1];
    aParty.getPartyName(pName);
    aParty.getPartyEmail(email);

    // make use of overloaded out stream operator in party ADT
    file << pName << ";" << email << endl;
    file.close();

    if(pName)
        delete []pName;
    if(email)
        delete []email;

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


ostream& operator<<(ostream& out, const stack &aStack)
{
    char * partyName = nullptr;
    char * email = nullptr;
    party aParty;
    aStack.peek(aParty);
    partyName = new char[aParty.getPartyNameLength() + 1];
    email = new char[aParty.getPartyEmailLength() + 1];
    aParty.getPartyName(partyName);
    aParty.getPartyEmail(email);

    out << "Customer: " << partyName << " Email: " << email << endl;
    if(partyName)
        delete []partyName;
    if(email)
        delete []email;
    return out;
}


