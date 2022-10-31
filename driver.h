#include "queue.h"
#include "stack.h"

using namespace std;


void menu();
void queueOperations(queue &, stack &, int);
void stackOperations(stack &, int);
void getChar(char &);
int main();
void getInput(char *&);
party  makeParty(); // should we make this take a party *? // no bc the
// local pointer will destruct when the function ends.
int getInteger() ;
