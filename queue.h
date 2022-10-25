#include <cstring>
#include <cctype>
#include <iostream>
#include "party.h"

using namespace std;

class queue
{
public:
    queue();
    queue(const queue &);
    ~queue();

    bool isEmpty();
    bool enqueue(const party &);
    bool dequeue();
    party& peekFron();

private:
    struct node
    {
        party * aParty;
        node * next;

        node():aParty(nullptr), next(nullptr)
        {}

        node(const party &aCopy)
        {
            aParty = new party(aCopy);
            next = nullptr;
        }

        ~node()
        {
            if(aParty)
                delete aParty;
            aParty = nullptr;
            next = nullptr;
        }
    };

    node *top, *tail;
    void destroy (node *&);
    node * append(node *&, const party &);


};