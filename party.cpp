#include "party.h"

party::party():partyName(nullptr),partyCount(0),
                specialSeating(nullptr), email(nullptr),promos(false)
{}


party::party(char * pName, char * pEmail):partyName(pName), email(pEmail),
partyCount(0), specialSeating(nullptr), promos(true)
{}


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


party::party(char * pName, char * sSeats, int pSize):partyName(pName),
specialSeating(sSeats),partyCount(pSize),email(nullptr),promos(false)
{}


party::~party()
{
    if(partyName)
        delete []partyName;
    if(specialSeating)
        delete []specialSeating;
    if(email)
        delete []email;
    partyName = nullptr;
    specialSeating = nullptr;
    email = nullptr;
    partyCount = 0;
    promos = false;
}


party::party(const party &aCopy): partyName(nullptr), partyCount(0),
specialSeating(nullptr), email(nullptr), promos(false)
{
    *this = aCopy;
}


void party::setPartyName(char * pName)
{
    if(partyName)
        delete []partyName;
    partyName = new char[strlen(pName) + 1];
    strcpy(partyName,pName);

}


void party::setPartyCount(int &count)
{
    partyCount = count;

}


void party::setSpecialSeating(char *seating)
{
    if(specialSeating)
        delete []specialSeating;
    specialSeating = new char[strlen(seating) +  1];
    strcpy(specialSeating, seating);
}


void party::setEmail(char * pEmail)
{
    if(email)
        delete []email;
    email = new char[strlen(pEmail) + 1];
    strcpy(email, pEmail);

}


void party::setPromos(bool getPromos)
{
    promos = getPromos;
}


void party::getPartyName(char *pName)
{
    strcpy(pName, partyName);
}


int party::getPartyCount() const
{
    return partyCount;
}


void party::getSpecailSeating(char *seating)
{
    strcpy(seating, specialSeating);
}


bool party::getPromos() const
{
    return promos;
}


int party::getPartyNameLength() const
{
    return ((int)strlen(partyName));
}


party& party::operator=(const party &aCopy)
{
    if(this == &aCopy)
    {
        return *this;
    }

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

// why do I get an error when I use const ostream &out ?
ostream &operator<<(ostream &out, const party &aParty)
{

    out << "Name: " << aParty.partyName << " Party Size: " << aParty
    .partyCount << endl;



    return out;
}



