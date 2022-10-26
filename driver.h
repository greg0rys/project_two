#include "queue.h"
#include "stack.h"

using namespace std;


void menu();
int main();
void getInput(char *&);
void  makeParty(party &); // should we make this take a party *? // no bc the
// local pointer will destruct when the function ends.
int getInteger() ;
