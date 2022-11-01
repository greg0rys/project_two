#include "party.h"

/*
 * Defualt constructor
 */
party::party():partyName(nullptr),partyCount(0),
                specialSeating(nullptr), email(nullptr),promos(false)
{}


/*
 * Create a party with a given name and email
 */
party::party(char * pName, char * pEmail):
partyCount(0), specialSeating(nullptr), promos(true)
{
    partyName = new char[strlen(pName) + 1];
    strcpy(partyName,pName);
    email = new char[strlen(pEmail) + 1];
    strcpy(email,pEmail);
}


/*
 * Create a party with all attributes set by client
 */
party::party(char *pName, int pSize, char *sSeating, char *pEmail, bool
wantPromos)
{
    partyName = new char[strlen(pName) + 1];
    strcpy(partyName, pName);
    specialSeating = new char[strlen(sSeating) + 1];
    strcpy(specialSeating,sSeating);
    email = new char[strlen(pEmail) + 1];
    strcpy(email, pEmail);
    partyCount = pSize;
    promos = wantPromos;

}


/*
 * Create a party with name size and seating info
 */
party::party(char * pName, char * sSeats, int pSize):
partyCount(pSize),email(nullptr),promos(false)
{
    partyName = new char[strlen(pName) + 1];
    specialSeating = new char [strlen(sSeats) + 1];
    strcpy(partyName,pName);
    strcpy(specialSeating, sSeats);
}


/*
 * Class destructor
 */
party::~party()
{
    destroy();
    partyName = specialSeating = email = nullptr;
    promos = false;
    partyCount = 0;
}


/*
 * Destroy all the pointers used by this object if they're set at destruction
 */
void party::destroy()
{
    if(partyName)
        delete []partyName;
    if(specialSeating)
        delete []specialSeating;
    if(email)
        delete []email;

}


/*
 * Copy constructor
 */
party::party(const party &aCopy): partyName(nullptr), partyCount(0),
specialSeating(nullptr), email(nullptr), promos(false)
{
    *this = aCopy;
}


/*
 * Set the parties name
 * INPUT: pName a char pointer with the parties name
 */
void party::setPartyName(char * pName)
{
    if(partyName)
        delete []partyName;
    partyName = new char[strlen(pName) + 1];
    strcpy(partyName,pName);

}


/*
 * Set the parties count
 * INPUT: an int representing the total number of people in the party
 */
void party::setPartyCount(int &count)
{
    partyCount = count;

}


/*
 * Set the parties special seating choice
 * INPUT seating a char pointer with the special seating value
 */
void party::setSpecialSeating(char *seating)
{
    if(specialSeating)
        delete []specialSeating;
    specialSeating = new char[strlen(seating) +  1];
    strcpy(specialSeating, seating);
}


/*
 * Set the parties email address
 * INPUT: pEmail a char pointer with the parties email in it
 */
void party::setEmail(char * pEmail)
{
    if(email)
        delete []email;

    email = new char[strlen(pEmail) + 1];
    strcpy(email, pEmail);

}


/*
 * Set the users promotions preferences
 * INPUT: getPromos a boolean true if they want promos false if else.
 */
void party::setPromos(bool getPromos)
{
    promos = getPromos;
}


/*
 * Get the parties name
 * INPUT: a char pointer to copy the name into.
 * OUTPUT: the parties name
 */
void party::getPartyName(char *pName)
{
    strcpy(pName, partyName);
}


/*
 * Get the parties promotional choices
 * OUTPUT: true if they want promos false if else.
 */
bool party::getPromos() const
{
    return promos;
}


/*
 * Get the length of the parties name
 * OUTPUT: the length of the parties name as an int
 */
int party::getPartyNameLength() const
{
    return ((int)strlen(partyName));
}


/*
 * Get the parties email address
 * INPUT: a char pointer to copy the email into
 * OUTPUT: the parties email address
 */
void party::getPartyEmail(char * pEmail)
{
    strcpy(pEmail,email);
}


/*
 * Get the length of the parties email address
 * OUTPUT: the length of the parties email address as an int
 */
int party::getPartyEmailLength() const
{
    return strlen(email);
}


/*
 * Overload the classes assignment operator to create deep copies
 */
party& party::operator=(const party &aCopy)
{
    if(this == &aCopy)
    {
        return *this;
    }
    destroy(); // clean up any old pointers

    // special case, all the pointers are null in the copy.
    if(!aCopy.partyName && !aCopy.specialSeating && !aCopy.email)
    {
        partyName = nullptr;
        specialSeating = nullptr;
        email = nullptr;
    }

    if(aCopy.partyName)
    {
        partyName = new char[strlen(aCopy.partyName) + 1];
        strcpy(partyName, aCopy.partyName);
    }
    else
    {
        partyName = nullptr;
    }

    if(aCopy.specialSeating)
    {
        specialSeating = new char[strlen(aCopy.specialSeating) + 1];
        strcpy(specialSeating, aCopy.specialSeating);
    }
    else
    {
        specialSeating = nullptr;
    }

    if(aCopy.email)
    {
        email = new char[strlen(aCopy.email) + 1];
        strcpy(email, aCopy.email);
    }
    else
    {
        email = nullptr;
    }

    partyCount = aCopy.partyCount;
    promos = aCopy.promos;

    return *this;
}


/*
 * Overload the classes output stream operator.
 * Prints different party values based on the promo choice of the party.
 */
ostream &operator<<(ostream &out, const party &aParty)
{

    if(aParty.specialSeating == nullptr)
    {
        out  << aParty.partyName << " " << aParty.email <<
        endl;
        return out;
    }
    out  << aParty.partyName << " Party Size: " << aParty
    .partyCount << " Special Seating Choice: " << aParty.specialSeating <<
    endl;



    return out;
}
