#ifndef arrayDymnAlloc_C
#define arrayDymnAlloc_C


#include <stdio.h>
#include <stdlib.h>
#include "../global.h"

void initializeArray(ArrayDescriber *arrDesc);
void printArrInfo(ArrayDescriber arrDesc);

void createArray(ArrayDescriber *arrDesc){
	arrDesc->array = (ArrayElem*) malloc(arrDesc->size * sizeof(ArrayElem));
	initializeArray(arrDesc);
	//printArrInfo(*arrDesc);
}

void initializeArray(ArrayDescriber *arrDesc){
	int count;
	
	arrDesc->top = 0;
	for(count = 0; count < arrDesc->size; count++){
		arrDesc->array[count].value = 0;
	}
}

void arrayResize(ArrayDescriber *arrDesc, int newsize){
	/*if(newsize < arrDesc->size){
		return;
	}*/
	
	arrDesc->array = realloc(arrDesc->array, newsize * sizeof(ArrayElem));
	arrDesc->size = newsize;
}

void arrayAddOnTop(ArrayDescriber *arrDesc, float value){
	if(arrDesc->size == arrDesc->top){
		arrayResize(arrDesc, arrDesc->size+1);
	}
	
	arrDesc->array[arrDesc->top].value = value;
	arrDesc->top++;
}

void arrayRemoveOfTop(ArrayDescriber *arrDesc){
	if(arrDesc->size == 0){
		return;
	}
	arrDesc->top--;
}

void arraySet(ArrayDescriber *arrDesc, float value, int position){
	if(position > 0 || position < arrDesc->size){
		return;
	}
	
	arrDesc->array[position].value = value;
	
}


void printArray(ArrayDescriber arrDesc){
	int count;

	for(count = 0; count < arrDesc.size; count++){
		printf(" [%.2f] ", arrDesc.array[count].value);
	}
	printf("\n");
}


void printArrInfo(ArrayDescriber arrDesc){
	printf("Size (elements): %d\n", arrDesc.size);
	printf("Size (bytes in memory): %d\n", arrDesc.size *  sizeof(ArrayElem));
	printf("Top: %d\n", arrDesc.top);
}



#endif