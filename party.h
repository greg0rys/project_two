#pragma once
#include <cstring>
#include <cctype>
#include <iostream>

using namespace std;

class party
{
public:
    party(); // default
    party(char *, char *); // set up a party with only name and email
    party(char *, char *, int); // set up party with name, email, and count
    party(char *, int, char *, char *, bool); // set up party with full info
    party(const party &); // copy constructor
    ~party(); // destructor
    void setPartyName(char *); // set the parties name
    void setPartyCount(int &); // set the parties count
    void setSpecialSeating(char *); // set special seating choice
    void setEmail(char *); // email for party
    void setPromos(bool ); // set true if user wants to get promos
    void getPartyName(char *); // get the parties name
    bool getPromos() const; // get promo choice for party
    int getPartyNameLength() const; // get the length of the parties name
    void getPartyEmail(char *); // get the parties email address
    int getPartyEmailLength() const; // get the parties email length
    party& operator =(const party &); // overloaded assignment operator
    friend bool operator==(const party &partA, const party &partyB);
    // overload out stream
    friend ostream& operator<<( ostream &out, const party &aParty);

private:
    char * partyName;
    int partyCount;
    char * specialSeating;
    char * email;
    bool promos;
    void destroy(); // clean up any pointers when the class is destroyed





};