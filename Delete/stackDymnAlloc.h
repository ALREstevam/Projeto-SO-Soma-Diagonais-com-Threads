#ifndef stackDymnAlloc_H
#define stackDymnAlloc_H

/*=================================================================================
							CRIAÇÃO DO STACK
==================================================================================*/
//Alocar memória para o stack
int createStack(StackDescriber *stkDesc);

//Inicializar stack
void initializeStack(StackDescriber *stkDesc);

//Redimencionar stack
void stackResize(StackDescriber *stkDesc, int newsize);


/*=================================================================================
							MANIPULAÇÃO DE DADOS
==================================================================================*/
//Adicionar no topo
void stackAdd(StackDescriber *stkDesc, CoordinatesXY coords);

//Removendo no topo
void stackRemove(StackDescriber *stkDesc);
CoordinatesXY stackGet(StackDescriber *stkDesc);

/*=================================================================================
							EXIBIÇÃO DO STACK
==================================================================================*/
//Imprimir stack
void printStack(StackDescriber stkDesc);

//Imprimir informações sobre stack
void printStkInfo(StackDescriber stkDesc);


#endif