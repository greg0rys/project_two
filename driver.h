#include "queue.h"
#include "stack.h"

using namespace std;


void menu();
void workInQueue(queue &);
void workInStack(stack &);
int main();
void getInput(char *&);
party  makeParty(); // should we make this take a party *? // no bc the
// local pointer will destruct when the function ends.
int getInteger() ;
