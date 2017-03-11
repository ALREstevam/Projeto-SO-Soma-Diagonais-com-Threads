#ifndef arraydymnalloc_H
#define arraydymnalloc_H

/*=================================================================================
							CRIA��O DO ARRAY
==================================================================================*/
//Alocar mem�ria
int createArray(ArrayDescriber *arrDesc);
//Setar valores iniciais
void initializeArray(ArrayDescriber *arrDesc);
int resizeArray(ArrayDescriber *arrDesc, unsigned int newsize);
/*=================================================================================
							ACESSO AOS DADOS
==================================================================================*/
	/* TRATANDO O ARRAY COMO UMA PILHA */
	//Acidionar na pilha
void addElementArrayAsStack(ArrayDescriber *arrDesc, Var elem);
	//Remover da pilha
void removeElementArrayAsStack(ArrayDescriber *arrDesc);
	//Acessar o topo
Var getTopElement(ArrayDescriber *arrDesc);
	/* FUN��ES DE ACESSO DIRETO */
void setElement(ArrayDescriber *arrDesc, Var elem, unsigned int position);
/*=================================================================================
							Fun��es de impress�o
==================================================================================*/
void printArrayInfo(ArrayDescriber arrDesc);
void printArray(ArrayDescriber arrDesc);
void printVar(Var var, char dataType[3], int ident);

#endif