#ifndef arrayDymnAlloc_H
#define arrayDymnAlloc_H

int createArray(ArrayDescriber *arrDesc);
void initializeArray(ArrayDescriber *arrDesc);
void arrayResize(ArrayDescriber *arrDesc, int newsize);
void arrayAdd(ArrayDescriber *arrDesc, float value);
void printArray(ArrayDescriber arrDesc);
void printArrInfo(ArrayDescriber arrDesc);

#endif