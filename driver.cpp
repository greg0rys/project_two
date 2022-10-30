#include "driver.h"

void menu()
{
    queue theQueue;
    stack theStack;
    char * partyName = nullptr;
    char * specialSeats = nullptr;
    char * partyEmail = nullptr;
    char * nextParty = nullptr;
    int partyCount;
    bool wantsPromos;
    bool removed;
    party aParty;
    int option = 0;
    while(option != 7)
    {
        cout << " ****** MENU: ****** " << endl;
        cout << "1.\t Add a party. " << endl
             << "2.\t Seat the next party. " << endl
             << "3.\t Display the queue (prints whole queue). " << endl
             << "4.\t Contact customers for promotions (displays customer "
                "info) " << endl
             << "5.\t See all customers who want promotional offers. " <<
             endl
             << "6.\t See past customers contacted for promotional offers "
             << endl << endl;

        cout << "Please enter a menu choice from above (EX 1. to add): ";
        option = getInteger();

        switch(option)
        {
            case 1:
               aParty = makeParty();
               theQueue.enqueue(aParty);
                break;
            case 2:
                if(theQueue.dequeue(aParty))
                {
                    if(partyName)
                    {
                        delete []partyName;
                    }
                    partyName = new char[aParty.getPartyNameLength() + 1];
                    aParty.getPartyName(partyName);
                    cout << partyName << " has been seated! " << endl;
                    theStack.push(aParty);
                }
                break;
            case 3:
                theQueue.printQueue();
                cout << endl;
                break;
            default:
                cout << "That is not a valid menu choice please try again! "
                << endl;
        }
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