#ifndef PROJSOTEST_ARRAYMNGR_H
#define PROJSOTEST_ARRAYMNGR_H

#include <stdbool.h>

//Protótipos
bool createArray(ArrayDescriber *arr, unsigned int size);
bool reallocArray(ArrayDescriber *arr, unsigned int newsize);
bool arrayAddTop(ArrayDescriber *arr, UData info);
bool accessPosition(ArrayDescriber *arr, unsigned int pos, UData *rsp);
void deleteArray(ArrayDescriber *arr);


#endif 