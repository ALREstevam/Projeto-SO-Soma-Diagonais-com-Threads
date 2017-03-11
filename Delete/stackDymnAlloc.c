#ifndef stackDymnAlloc_C
#define stackDymnAlloc_C


#include <stdio.h>
#include <stdlib.h>
#include "../global.h"

void initializeStack(StackDescriber *stkDesc);
void printArrInfo(StackDescriber stkDesc);


/*=================================================================================
							CRIAÇÃO DO STACK
==================================================================================*/
//Alocar memória para o stack
int createStack(StackDescriber *stkDesc){
	stkDesc->stack = (StackElem*) malloc(stkDesc->size * sizeof(StackElem));
	if(stkDesc->stack == NULL){
		return -1;
	}else{
		initializeStack(stkDesc);
	}
	return 0;
}

//Inicializar stack
void initializeStack(StackDescriber *stkDesc){
	int count;
	
	stkDesc->top = 0;
	for(count = 0; count < stkDesc->size; count++){
		stkDesc->stack[count].coords.x = -1;
		stkDesc->stack[count].coords.y = -1;
	}
}

//Redimencionar stack
void stackResize(StackDescriber *stkDesc, int newsize){
	/*if(newsize < stkDesc->size){
		return;
	}*/
	
	stkDesc->stack = realloc(stkDesc->stack, newsize * sizeof(StackElem));
	stkDesc->size = newsize;
	
	
	if(newsize < stkDesc->size){
		stkDesc->top = newsize - 1;
	}
}


/*=================================================================================
							MANIPULAÇÃO DE DADOS
==================================================================================*/
//Adicionar no topo
void stackAdd(StackDescriber *stkDesc, CoordinatesXY coords){
	if(stkDesc->size == stkDesc->top){
		stackResize(stkDesc, stkDesc->size+1);
	}
	
	stkDesc->stack[stkDesc->top].coords.x = coords.x;
	stkDesc->stack[stkDesc->top].coords.y = coords.y;
	stkDesc->top++;
}

//Removendo no topo
void stackRemove(StackDescriber *stkDesc){
	if(stkDesc->size == 0){
		return;
	}
	stkDesc->top--;
}

//Consultando o topo
CoordinatesXY stackGet(StackDescriber *stkDesc){
	return stkDesc->stack[stkDesc->top- 1].coords;
}

/*=================================================================================
							EXIBIÇÃO DO STACK
==================================================================================*/
//Imprimir stack
void printStack(StackDescriber stkDesc){
	int count;

	for(count = 0; count < stkDesc.top; count++){
		printf("(%d,%d) \t", stkDesc.stack[count].coords.x, stkDesc.stack[count].coords.y);
	}
	printf("\n");
}

//Imprimir informações sobre stack
void printStkInfo(StackDescriber stkDesc){
	printf("\n\n=================== INFORMACOES SOBRE STACK ===================\n");
	printf("Size (elements): %d\n", stkDesc.size);
	printf("Size (memory): %d bytes\n", stkDesc.size *  sizeof(StackElem));
	printf("Size (each element): %d bytes\n", sizeof(StackElem));
	printf("Top: %d\n", stkDesc.top);
	printf("================================================================\n\n");
}



#endif