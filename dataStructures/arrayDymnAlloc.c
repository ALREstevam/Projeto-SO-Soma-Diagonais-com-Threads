#ifndef arraydymnalloc_C
#define arraydymnalloc_C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../global.h"

void initializeArray(ArrayDescriber *arrDesc);
void printVar(Var var, char dataType[3], int ident);

/*=================================================================================
							CRIAÇÃO DO ARRAY
==================================================================================*/
//Alocar memória
int createArray(ArrayDescriber *arrDesc){
	if(arrDesc->size <= 0){
		return -2;
	}
	arrDesc->var = (Var *) malloc(arrDesc->size * sizeof(Var));
	initializeArray(arrDesc);
	
	if(arrDesc->var != NULL){
		return arrDesc->size * sizeof(Var);
	}else{
		return -1;
	}	
	return 0;
}

//Setar valores iniciais
void initializeArray(ArrayDescriber *arrDesc){
	arrDesc->top = 0;
}

//Redimencionar
int resizeArray(ArrayDescriber *arrDesc, unsigned int newsize){
	if(arrDesc->size <= 0){
		return -2;
	}
	
	
	arrDesc->var = realloc(arrDesc->var, newsize * sizeof(Var));
	
	if(arrDesc->var != NULL){
		if(newsize < arrDesc->size){
			arrDesc->top = newsize - 1;
		}	
		arrDesc->size = newsize;
		return 0;
	}else{
		return -1;
	}
}

/*=================================================================================
							ACESSO AOS DADOS
==================================================================================*/
	/* TRATANDO O ARRAY COMO UMA PILHA */
	//Acidionar na pilha
void addElementArrayAsStack(ArrayDescriber *arrDesc, Var elem){
	if(arrDesc->top == arrDesc->size){
		resizeArray(arrDesc, arrDesc->size + 5);
	}
	
	arrDesc->var[arrDesc->top] = elem;
	arrDesc->top++;
}

	//Remover da pilha
void removeElementArrayAsStack(ArrayDescriber *arrDesc){
	arrDesc->top -= 1;
}	
	
	//Acessar o topo
Var getTopElement(ArrayDescriber *arrDesc){
	return arrDesc->var[arrDesc->top - 1];
}

	/* FUNÇÕES DE ACESSO DIRETO */
void setElement(ArrayDescriber *arrDesc, Var elem, unsigned int position){
	if(position > arrDesc->size){
		resizeArray(arrDesc, position);
	}
	arrDesc->var[arrDesc->top] = elem;
}



/*=================================================================================
							Funções de impressão
==================================================================================*/
void printArrayInfo(ArrayDescriber arrDesc){
	printf("\n\n================  ARRAY INFO =================\n");
	printf("Elementos:               %d\n", arrDesc.size);
	printf("Tamanho total:           %d bytes\n", sizeof(Var) * arrDesc.size);
	printf("Tamanho do elemento:     %d bytes\n", sizeof(Var));
	printf("Topo:                    %d\n", arrDesc.top);
	printf("Flag tipo de var:        %s\n", arrDesc.dataType);
	printf("==============================================\n\n");
}

void printArray(ArrayDescriber arrDesc){
	int count;
	for(count = 0; count <= arrDesc.top-1; count++){
	
		printVar(arrDesc.var[count], arrDesc.dataType, count);
		
		if(arrDesc.top-1 == count){
			printf(" <- [TOPO (virtual)]");
		}
		
		printf("\n");
	}
}
	
	
void printVar(Var var, char dataType[3], int ident){
		if(!strcmp(dataType, "flt")){
			   printf("{(%d)=[%.2f]}, ",ident, var.flt);	
		}
		if(!strcmp(dataType, "cxy")){
			   printf("{(%d)=[(%d, %d)]}, ",ident, var.coords.x, var.coords.y);	
		}
		if(!strcmp(dataType, "tid")){
			   printf("{(%d)=[%d]}, ",ident, var.tid.x);	
		}
		if(!strcmp(dataType, "int")){
			   printf("{(%d) flt=[%.2f], cxy=[(%d, %d)], tid=[%d]}, ",ident, var.flt, var.coords.x, var.coords.y,  var.tid.x );	
		}


}


#endif