#ifndef arraydymnalloc_H
#define arraydymnalloc_H

/*=================================================================================
							CRIAÇÃO DO ARRAY
==================================================================================*/
//Alocar memória
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
	/* FUNÇÕES DE ACESSO DIRETO */
void setElement(ArrayDescriber *arrDesc, Var elem, unsigned int position);
/*=================================================================================
							Funções de impressão
==================================================================================*/
void printArrayInfo(ArrayDescriber arrDesc);
void printArray(ArrayDescriber arrDesc);
void printVar(Var var, char dataType[3], int ident);

#endif