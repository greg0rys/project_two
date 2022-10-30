#pragma once
#include <cstring>
#include <cctype>
#include <iostream>

using namespace std;

class party
{
public:
    party(); // default
    party(char *, char *); // set up a party with info for the stack
    party(char *, char *, int);
    party(char *, int, char *, char *, bool);
    party(const party &); // copy constructor
    ~party(); // destructor
    void setPartyName(char *); // set the parties name
    void setPartyCount(int &); // set the parties count
    void setSpecialSeating(char *); // set special seating choice
    void setEmail(char *); // email for party
    void setPromos(bool ); // set true if user wants to get promos
    void getPartyName(char *); // get the parties name
    int getPartyCount() const; // get the parties count
    void getSpecailSeating(char *); // get parties special seating choice
    bool getPromos() const; // get promo choice for party
    int getPartyNameLength() const;
    party& operator =(const party &); // overloaded assignment operator
    friend bool operator==(const party &partA, const party &partyB);
    friend ostream& operator<<( ostream &out, const party &aParty);

private:
    char * partyName;
    int partyCount;
    char * specialSeating;
    char * email;
    bool promos;





};