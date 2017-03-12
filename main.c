#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include "global.h"
#include "dataStructures/matrixDymnAlloc.h"
#include "dataStructures/arrayDymnAlloc.h"
#include "dataStructures/stackDymnAlloc.h"


void * sumDiagonals(void *arg){
	TArgs *infoData = (TArgs*) arg;
	
	float result;
	CoordinatesXY pos;
	Var vr, rsp;
	
	while(infoData->diagonals->top > 0){
		vr = removeElementOnTop(infoData->diagonals);
		pos = vr.coords;
		
		result = infoData->mx->matrix[pos.x][pos.y].value;
		
		do{
			pos.x =  infoData->mx->matrix[pos.x][pos.y].nextInMainDiagonal.x;
			pos.y =  infoData->mx->matrix[pos.x][pos.y].nextInMainDiagonal.y;
			
			result +=  infoData->mx->matrix[pos.x][pos.y].value;
		}while(pos.x < 0 || pos.y  < 0);	
		
			rsp.flt = result;
			addElementOnTop(infoData->sums, rsp);
	}
	
	
	
	pthread_exit(NULL);
	return NULL;
}



int main(){
	void clear(){
		int i;
		for(i = 0; i < 255; i++){
			printf("\n");	
		}
	}
	
	
	MatrixDescriber mxDesc;
	
	//Definindo tamanho da matriz
	
	
	int holder1, holder2, tAmount;
	
	printf("DEFININDO TAMANHO DA MATRIZ\n");
	/*printf("m (linhas): ");
	fscanf(stdin, "%d" ,&(holder1));
	
	getchar();
	
	printf("n (colunas): ");
	fscanf(stdin, "%d" ,&(holder2));
	getchar();
	*/
	
	printf("m (linhas): ");
	scanf("%d", &holder1);
	printf("n (colunas): ");
	scanf("%d", &holder2);
		
	mxDesc.m = holder1;
	mxDesc.n = holder2;
	
	printf("\n\n");
	printf("DEFININDO QUANTIDADE DE THREADS PARA FAZER A SOMA\n");
	printf("T (numero de threads): ");
	scanf("%d", &tAmount);
	
	clear();
	
	//Criando matriz
	int result;
	result = createMatrix(&mxDesc);
	
	printf("ALOCANDO MATRIZ.......: ");
	
	if(result < 0){
		printf("erro numero: %d.\n", result * -1);
		getchar();
		return 0;
	}else{
		setFillRandom(&mxDesc);
		//setFillOrder(&mxDesc, 1);
		//printMatrix(mxDesc, 1);
		printf("sucesso.\n");
		printMatrixInfo(mxDesc);
	}
	
	
	

	//Criando array para armazenar resultado das somas
	ArrayDescriber arr;
	arr.size = ((mxDesc.m) + (mxDesc.n)) - 1;	
	strcpy(arr.dataType, "flt");
	
	printf("ALOCANDO VETOR DE RESULTADOS...............: ");
	
	result = createArray(&arr);
	
	if(result < 0){
		printf("erro.\n");
		getchar();
		return 0;
	}else{
		printf("sucesso.\n");
		printArrayInfo(arr);
		
	}
	
	//Criando fila para armazenar os índices dos elementos da matriz que são início de diagonal
	ArrayDescriber resultStack;
	resultStack.size = ((mxDesc.m) + (mxDesc.n)) - 1;
	strcpy(resultStack.dataType, "cxy");
	printf("ALOCANDO PILHA DE OPERACOES...............: ");
	
	result = createArray(&resultStack);
	
	if(result < 0){
		printf("erro.\n");
		getchar();
		return 0;
	}else{
		mainDiagonalStartToStack(&mxDesc, &resultStack);
		printf("sucesso.\n");
		printArrayInfo(resultStack);
		printArray(resultStack);
	}
	
	
	//Criando arrays para armazenar informações sobre as threads
	ArrayDescriber tidArr;
	tidArr.
	
	
	
	TArgs args;
	args.mx = &mxDesc;
	args.diagonals = &arr;
	args.sums = &resultStack;
	
	pthread_attr_t = attr;
	
	int i;
	for(i = 0; i < tAmount; i++){
		pthread_attr_init(&attr);
		pthread_create(&tid, &attr, sumDiagonals, &args);
	}

	
	
	return 0;
}


