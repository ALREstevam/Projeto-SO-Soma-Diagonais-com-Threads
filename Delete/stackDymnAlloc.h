#ifndef stackDymnAlloc_H
#define stackDymnAlloc_H

/*=================================================================================
							CRIA��O DO STACK
==================================================================================*/
//Alocar mem�ria para o stack
int createStack(StackDescriber *stkDesc);

//Inicializar stack
void initializeStack(StackDescriber *stkDesc);

//Redimencionar stack
void stackResize(StackDescriber *stkDesc, int newsize);


/*=================================================================================
							MANIPULA��O DE DADOS
==================================================================================*/
//Adicionar no topo
void stackAdd(StackDescriber *stkDesc, CoordinatesXY coords);

//Removendo no topo
void stackRemove(StackDescriber *stkDesc);
CoordinatesXY stackGet(StackDescriber *stkDesc);

/*=================================================================================
							EXIBI��O DO STACK
==================================================================================*/
//Imprimir stack
void printStack(StackDescriber stkDesc);

//Imprimir informa��es sobre stack
void printStkInfo(StackDescriber stkDesc);


#endif