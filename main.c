#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "global.h"
#include "dataStructures/matrixDymnAlloc.h"
#include "dataStructures/arrayDymnAlloc.h"


int main()
{
	MatrixDescriber mxDesc;
	
	//Definindo tamanho da matriz
	
	
	
	printf("DEFININDO TAMANHO DA MATRIZ\n");
	printf("m: ");
	fscanf(stdin, "%d" ,&(mxDesc.m));
	
	getchar();
	
	printf("n: ");
	fscanf(stdin, "%d" ,&(mxDesc.n));
	getchar();
	
	mxDesc.m = 3;
	mxDesc.n = 4;
	

	
	
	//Criando matriz
	createMatrix(&mxDesc);
	setFillRandom(&mxDesc);
	printMatrix(mxDesc, 0);
	printMatrixInfo(mxDesc);

	//Criando array para armazenar resultado das somas
	ArrayDescriber arr;
	arr.size = (mxDesc.m) * (mxDesc.n);	
	createArray(&arr);
	
	//
	
	

	
	
	
	return 0;
}


