#include "driver.h"

void menu()
{
    queue theQueue;
    stack theStack;
    party aParty;
    int option = 0;
    while(option != 8)
    {
        cout << " ****** MENU: ****** " << endl;
        cout << "1.\t Add a party. " << endl
             << "2.\t Seat the next party. " << endl
             << "3.\t See whos next. " << endl
             << "4.\t Display the queue (prints whole queue). " << endl
             << "5.\t Contact customers for promotions (displays customer "
                "info) " << endl
             << "6.\t See all customers who want promotional offers. " <<
             endl
             << "7.\t See past customers contacted for promotional offers "
             << endl
             << "8.\t Quit" << endl << endl;

        cout << "Please enter a menu choice from above (EX 1. to add): ";
        option = getInteger();

        switch(option)
        {
            case 1:
                queueOperations(theQueue, theStack, 1);
                break;
            case 2:
                queueOperations(theQueue, theStack,2);
                break;
            case 3:
                queueOperations(theQueue, theStack,3);
                break;
            case 4:
                queueOperations(theQueue, theStack, 4);
                break;
            case 5:
                stackOperations(theStack, 1);
                break;
            case 6:
                stackOperations(theStack, 2);
                break;
            case 7:
                stackOperations(theStack,3);
                break;
            case 8:
                cout << "Thanks for using me! " << endl;
                break;
            default:
                cout << "That is not a valid menu choice please try again! "
                << endl;
                break;
        }
    }
}


void queueOperations(queue &theQueue, stack &theStack, int option)
{
    typedef char* charP; // rename char *
    charP partyName = nullptr;
    party aParty;

    if(option > 4)
    {
        cout << "Unsupported operation choice for " << option
             << " please try again! " << endl;
        return;
    }
    switch(option)
    {
        case 1:
            aParty = makeParty();
            if(theQueue.enqueue(aParty))
            {
                partyName = new char[aParty.getPartyNameLength() + 1];
                aParty.getPartyName(partyName);
                cout << "Success " << partyName << " has been added to the "
                                                   "queue " << endl;
                if(partyName)
                    delete []partyName;
            }
            if(aParty.getPromos())
            {
                partyName = new char[aParty.getPartyNameLength() + 1];
                aParty.getPartyName(partyName);
                cout << "Adding " << partyName << " to the promos list "
                     << endl;
                theStack.push(aParty);
                if(partyName)
                    delete []partyName;
            }
            break;
        case 2:
            if(!theQueue.peekFront(aParty))
            {
                cout << "There are currently no parties in the queue! " <<
                     endl;
                break;
            }

            cout << "*****************************" << endl;
            cout << "Seating the next party.. " << endl;
            cout << "Seating: " << aParty << endl;
            theQueue.dequeue(aParty);
            cout << "*****************************" << endl;
            break;
        case 3:
            if(theQueue.isEmpty())
            {
                cout << "The queue is currently empty! Nothing to display.. "
                     << endl;
                break;
            }
            theQueue.peekFront(aParty);
            cout << "The next party to be sat is: " << endl;
            cout << "\t" << aParty << endl;
            break;
        case 4:

            if(theQueue.isEmpty())
            {
                cout << "The queue is currently empty! Nothing to display.. "
                     << endl;
                break;
            }

            cout << theQueue << endl;
            theQueue.printQueue();
            break;
        default:
            cout << "unsupported operation, please try again " << endl;
            break;
    }
}


void stackOperations(stack &theStack, int option)
{
    party aParty;
    stack previousCustomers;
    char * partyName = nullptr;
    char  next = 'y';
    // could use overloaded stack print stream to print party info.

    switch(option)
    {
        case 1:
            cout << "There are currently: " << theStack.getSize()
                 << " customers waiting to be contacted " << endl;
            while(next != 'n')
            {
                if(!theStack.peek(aParty))
                {
                    cout << "End of customers to contact! " << endl;
                    break;
                }
                cout << theStack << endl;
                theStack.pop(aParty);
                theStack.saveToFile("stack.txt", aParty);
                cout << "Would you like to see the next customer? "
                     << "(y for yes, n for no): ";

                getChar(next);
            }
            break;
        case 2:
            if(!theStack.peek(aParty))
            {
                cout << "There are no customers waiting to be contacted! "
                     << endl;
                break;
            }

            cout << "There are " << theStack.getSize() << " customers to "
                                                          "contact " << endl;
            theStack.printStack();
            break;
        case 3:
            previousCustomers.loadFromFile("stack.txt", previousCustomers);
            cout << "You have contacted: " << previousCustomers.getSize()
                 << " customers in the past " << endl;
            previousCustomers.printStack();
            break;
         default:
            cout << "Unsupported operation! Try again " << endl;
            break;
    }
}


void getChar(char &output)
{
    cin >> output;

    while(cin.fail())
    {
        cin.clear();
        cin.get();
        cin.ignore(101,'\n');
        cerr << "Please enter a valid character choice: (y for yes, n for no) "
             << endl;
        cout << "Enter input: ";
        cin >> output;
    }

    cin.ignore(101,'\n');

    while(toupper(output) != 'Y' && toupper(output) != 'N')
    {
        cerr << "Please enter a choice of y for yes, n for no. " << endl;
        cout << "Enter input: ";
        cin >> output;
        cin.ignore(101,'\n');
    }
}

void getInput(char *& chars) {
    char *input = nullptr; // store the input from input stream
    char *temp = nullptr; // store a temp copy of the input each time input
    // grows
    int wordSize = 0; // the size of the word we got from input

    while (cin.good() && cin.peek() != EOF) {
        char letter = cin.get(); // grabs the current character in the input

        if (letter == '\n') {
            break;
        }

        if (!input) {
            input = new char[2];
            input[0] = letter;
            input[1] = '\0';
            wordSize = 1;
        } else {
            wordSize = strlen(input);
            // +2 so we can get the letter plus have enough space to append
            // cstrings null node terminator to the end.
            temp = new char[wordSize + 2]{0};
            strcpy(temp, input);
            delete[]input;
            input = temp;
            input[wordSize] = letter;
            input[wordSize + 1] = '\0';
        }

    }


    chars = new char[strlen(input) + 1];
    // copy the users input into the passed in pointer.
    strcpy(chars, input);
    // get rid of our dynamic input pointer.
    delete[]input;
}

int getInteger()
{
    int numberIn;
    cin >> numberIn;

    while(cin.fail())
    {
        cin.clear();
        cin.ignore(101, '\n');
        cerr << "Please enter a whole number as input "
        << "(EX 100 or 379) " << endl;
        cin >> numberIn;
    }

    cin.ignore(101, '\n');
    return numberIn;
}

party makeParty()
{
    typedef char * charC; // redefine char * to avoid having to type the
    // special char *
    charC partyName = nullptr;
    charC specialSeats = nullptr;
    charC pEmail = nullptr;
    charC  promos = nullptr;
    bool wantsPromos = false;
    int partySize;
    party aParty;



    cout << "Enter the first and last name of the party: ";
    getInput(partyName);
    cout << "How many people are in the party (EX 5 or 3): ";
    partySize = getInteger();
    cout << "Will the party need special seating? (h. for highchair, b. for "
            "booster, n. for none): ";
    getInput(specialSeats);
    cout << "Would the party like to recieve updates about promotions we're "
            "having? (y. for yes, n.for no) ";
    getInput(promos);

    if(strcmp(promos, "y") == 0)
    {
        cout << "Please enter the email address for the party EX(j@J.com): ";
        getInput(pEmail);
        wantsPromos = true;
        aParty.setEmail(pEmail);
    }

    aParty.setPartyName(partyName);
    aParty.setSpecialSeating(specialSeats);
    aParty.setPartyCount(partySize);
    aParty.setPromos(wantsPromos);

    if(partyName)
    {
        delete []partyName;

    }

    if(specialSeats)
    {
        delete []specialSeats;

    }

    if(pEmail)
    {
        delete []pEmail;
    }

    if(promos)
    {
        delete []promos;

    }

    return aParty;





}

int main()
{
    menu();
    return 0;
}