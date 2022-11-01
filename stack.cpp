#include "stack.h"

/*
 * Default class constructor
 */
stack::stack(): top(0)
{
    currentSize = INIT_CAP;
    index = new party *[currentSize];

    for(auto i = 0; i < currentSize; i++)
        index[i] = nullptr;

}


/*
 * Load the stack with test data on load.
 * INPUTS: theStack the stack we wish to load with test data.
 * OUTPUTS: the total number of parties added to the stack
 */
int stack::init(stack &theStack)
{
    return loadFromFile("stack.txt", theStack);
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

/*
 * create a stack with a given size
 * @param  size - the size of the stack
 */
stack::stack(const int size):top(0),currentSize(size)
{
    index = new party *[currentSize];

    for(auto i = 0; i < currentSize; i ++)
        index[i] = nullptr;
}


/*
 * Copy constructor
 * @param aStack the stack we wish to copy from.
 */
stack::stack(const stack &aStack):index(nullptr),top(0)
{
    *this = aStack;
}

/*
 * Class Destructor
 */
stack::~stack()
{
    destroy();
}

/*
 * Destroy all the pointers inside the stacks array, and also destroy the
 * pointer to the array itself.
 */
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


/*
 * Push a new party onto the top of the stack
 * @param aParty a reference to the party we wish to add.
 */
void stack::push(const party &aParty)
{
    if(currentSize == top)
        grow();
    index[top] = new party(aParty);
    top++;
}

/*
 * Pop the first party in the stack off
 * @param aParty a reference to a party, the deleted parties values will be
 * copied into it so the caller of this function can then use that reference
 * to get info about the party we just removed.
 */
bool stack::pop(party &aParty)
{
    if(top == 0)
        return false;

    aParty = *(index[top - 1]);
    delete index[top - 1];
    top--;
    return true;
}

/*
 * Get a copy of the item at the top of the stack.
 * @param aParty a reference to a party, the values of the party on top will
 * be copied into it.
 */
bool stack::peek(party &aParty) const
{
    if(top == 0)
        return false;
    aParty = *(index[top - 1]);
    return true;
}


/*
 * Get the total size of the current stack
 * @return the currentSize of the stack
 */
int stack::getSize() const
{
    return currentSize;
}


/*
 * Check to see if the stack is empty
 * @return true if the stacks top pointer = nullptr false if else.
 */
bool stack::isEmpty() const
{
    return index == nullptr;
}

/*
 * Grow the current stack array by 2x its size if we run out of room in the
 * current stack
 */
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

/*
 * Get the total number of items currently inside the stack
 * @return the total number of items currently in the stack.
 */
int stack::getTotalItems() const
{
    int totalItems = 0;
    for(auto i = 0; i < top; i++)
    {
        totalItems++;
    }

    return totalItems;
}

/*
 * Print all the parties inside our current stack
 * @return output about all the parties in our stack
 */
void stack::printStack()
{
    if(isEmpty())
    {
        return;
    }
    print(index);

}

/*
 * recursively print all the items in the stack
 * @return the printed information about all the parties in the stack
 */
void stack::print(party **array)
{
    party aParty;
    cout << "****** Customers to contact ****** " << endl;
    for(auto i = 0; i < top; i++)
    {
        aParty = *(index[i]);
        cout << aParty;
    }
    cout << "****** End of Contacts ****** " << endl;
}


/*
 * Load data for the stack from a file
 * @param filename the name of the file we wish to open
 * @param aStack the stack we wish to store the loaded data into
 * @return the total number of items loaded from the file.
 */
int stack::loadFromFile(const char *filename, stack& aStack)
{

    fstream file(filename);
    int totalLoaded = 0;
    const int MAX_CHAR = 101;
    char partyName[MAX_CHAR];
    char email[MAX_CHAR];
    party newParty;
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
        file.get(email, MAX_CHAR, '\n');

        // set true if promos in CSV is 'true' else set false.
        newParty.setPartyName(partyName);
        newParty.setEmail(email);
        aStack.push(newParty);
        totalLoaded++;
        file.get(partyName, MAX_CHAR, ';');
    }
    file.close();

    return totalLoaded;
}

/*
 * Save the recently contacted party to the stack file so we have data about
 * who we contacted
 * @param filename the name of the file we wish to store the data in
 * @param aParty the party we wish to store.
 */
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

/*
 * Overloaded assignment operator
 * @param aStack the stack we wish to copy from
 * @return stack& a reference to this
 */
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


/*
 * Overloaded out stream operator, print the party at the top of the stack
 * @param out a reference to the ostream
 * @param aStack the stack we are inserting into the stream
 * @return out the reference to the output stream
 */
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


