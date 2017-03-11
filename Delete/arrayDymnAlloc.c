#ifndef arrayDymnAlloc_C
#define arrayDymnAlloc_C


#include <stdio.h>
#include <stdlib.h>
#include "../global.h"

void initializeArray(ArrayDescriber *arrDesc);
void printArrInfo(ArrayDescriber arrDesc);


/*=================================================================================
							CRIAÇÃO DO ARRAY
==================================================================================*/
//Alocar memória para o array
int createArray(ArrayDescriber *arrDesc){
	arrDesc->array = (ArrayElem*) malloc(arrDesc->size * sizeof(ArrayElem));
	if(arrDesc->array == NULL){
		return -1;
	}else{
		initializeArray(arrDesc);
	}
	return 0;
}

//Inicializar array
void initializeArray(ArrayDescriber *arrDesc){
	int count;
	
	arrDesc->top = 0;
	for(count = 0; count < arrDesc->size; count++){
		arrDesc->array[count].value = 0;
	}
}

//Redimencionar array
void arrayResize(ArrayDescriber *arrDesc, int newsize){
	/*if(newsize < arrDesc->size){
		return;
	}*/
	
	arrDesc->array = realloc(arrDesc->array, newsize * sizeof(ArrayElem));
	arrDesc->size = newsize;
}


/*=================================================================================
							MANIPULAÇÃO DE DADOS
==================================================================================*/
//Adicionar no topo
void arrayAddOnTop(ArrayDescriber *arrDesc, float value){
	if(arrDesc->size == arrDesc->top){
		arrayResize(arrDesc, arrDesc->size+1);
	}
	
	arrDesc->array[arrDesc->top + 1].value = value;
	arrDesc->top++;
}

//Removendo no topo
void arrayRemoveOfTop(ArrayDescriber *arrDesc){
	if(arrDesc->size == 0){
		return;
	}
	arrDesc->top--;
}

//Setando por posição
void arraySet(ArrayDescriber *arrDesc, float value, int position){
	if(position > 0 || position < arrDesc->size){
		return;
	}
	arrDesc->array[position].value = value;
}

/*=================================================================================
							EXIBIÇÃO DO ARRAY
==================================================================================*/
//Imprimir array
void printArray(ArrayDescriber arrDesc){
	int count;

	for(count = 0; count < arrDesc.size; count++){
		printf(" [%.2f] ", arrDesc.array[count].value);
	}
	printf("\n");
}

//Imprimir informações sobre array
void printArrInfo(ArrayDescriber arrDesc){
	printf("\n\n=================== INFORMACOES SOBRE ARRAY ===================\n");
	printf("Size (elements): %d\n", arrDesc.size);
	printf("Size (memory): %d bytes\n", arrDesc.size *  sizeof(ArrayElem));
	printf("Size (each element): %d bytes\n", sizeof(ArrayElem));
	printf("Top: %d\n", arrDesc.top);
	printf("================================================================\n\n");
}



#endif