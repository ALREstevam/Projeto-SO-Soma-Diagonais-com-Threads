#ifndef matrixDymnAlloc_C
#define matrixDymnAlloc_C

#include <stdlib.h>
#include <stdio.h>
#include "../global.h"
#include "arrayDymnAlloc.h"




/*=================================================================================
							CRIAÇÃO DA MATRIZ
==================================================================================*/

//ALOCADOR DE MEMÓRIA E INICIALIZADOR DA MATRIZ
int createMatrix(MatrixDescriber *mxDesc){
	int count;
	mxDesc->matrix = malloc(mxDesc->m * sizeof(MatrixElem));
	
	if(mxDesc->matrix == NULL){
		return -1;
	}
	
	for(count = 0; count < mxDesc->n; count++){
		mxDesc->matrix[count] = (MatrixElem * ) malloc(mxDesc->n * sizeof(MatrixElem));
		if(mxDesc->matrix[count] == NULL){
			return -1;
		}
	}
	return 0;
}

//Inicializando a matriz


void getNextElemInMainDiagonal(MatrixDescriber *mxDesc, CoordinatesXY *coords, int x, int y){
	//O elemento não tem próxmo pois está fora da matriz
	if(x > coords->x || y > coords->y){
		coords->x = -2;
		coords->y = -2;

	//O elemento existe, portando deve existir próximo se o elemento não for o último da diagonal
	}else if(x > coords->x || y > coords->y){
		coords->x = coords->x - 1;
		coords->y = coords->y + 1;
	}
	//O elemento não tem próximo pois a posição do próximo está fora da matriz
	else{
		coords->x = -1;
		coords->y = -1;
	}
}

void initializeMatrixElem(MatrixDescriber *mxDesc){
    int countM, countN;

    for(countM = 0; countM < mxDesc->m; countM++){
        for(countN = 0; countN < mxDesc->n; countN++){

            //Setando valores como 0
            mxDesc->matrix[countM][countN].value = 0;

            //Setando coordenadas do elemento da diagonal (RETIRAR ?)
            CoordinatesXY coord;
            getNextElemInMainDiagonal(mxDesc, &coord, countM, countN);
            mxDesc->matrix[countM][countN].nextInMainDiagonal.x = coord.x;
            mxDesc->matrix[countM][countN].nextInMainDiagonal.y = coord.y;
		}
	}
}


/*=================================================================================
							EXIBIÇÃO DA MATRIZ
==================================================================================*/
void printMatrix(MatrixDescriber mxDesc, int flag_mode){
	int countM, countN;
	
	printf("\n");
	printf("\tMATRIZ\n");
	
	for(countM = 0; countM < mxDesc.m; countM++){
		for(countN = 0; countN < mxDesc.n; countN++){
			switch(flag_mode)
			{
			case 0:
				printf("[%2.1f]\t",mxDesc.matrix[countM][countN].value);
				break;
			case 1:
				printf("{(%d,%d):[%2.1f]}\t",countM, countN, mxDesc.matrix[countM][countN].value);
				break;
			case 2:
				printf("(%d,%d)\t",countM, countN);
				break;
			default:
				printf("[%2.1f]\t",mxDesc.matrix[countM][countN].value);
				break;
			}
		}
		printf("\n");
	}
	printf("\n");
}

void printMatrixInfo(MatrixDescriber mxDesc){
	printf("Size (elements): %d\n", mxDesc.m * mxDesc.n);
	printf("Size (bytes in memory): %d\n", mxDesc.m * mxDesc.n * sizeof(MatrixElem));
	printf("m: %d\n", mxDesc.m);
	printf("n: %d\n", mxDesc.n);
}

/*=================================================================================
							FUNÇÕES DE SET
==================================================================================*/
//Inserir número em uma posição 
int setMatrixValue(MatrixDescriber *mxDesc, int x, int y, float value){
	if(mxDesc->matrix == NULL || mxDesc->m < 0 || mxDesc-> n < 0 || x > mxDesc->m || y > mxDesc->n){
		return -1;
	}else{
		mxDesc->matrix[x][y].value = value;
		return 0;
	}
}

//Preencher com números randômicos
void setFillRandom(MatrixDescriber *mxDesc){
	int countM, countN;
	for(countM = 0; countM < mxDesc->m; countM++){
		for(countN = 0; countN < mxDesc->n; countN++){
			mxDesc->matrix[countM][countN].value = rand();
		}
	}
}

//Preencher com números de forma ordenada
void setFillOrder(MatrixDescriber *mxDesc, float start){
	int countM, countN;
	
	for(countM = 0; countM < mxDesc->m; countM++){
		for(countN = 0; (countN < mxDesc->n); countN++){
			setMatrixValue(mxDesc, countM, countN, start);
			start += 1;		
		}
		printf("\n");
	}
	printf("\n");
	
}


/*=================================================================================
						CÁLCULO DA SOMA DE UMA DIAGONAL
==================================================================================*/
void diagonalFirstPositionToArray(MatrixDescriber *mxDesc, ArrayDescriber *arrDesc){
	arrDesc->size = (mxDesc->m + mxDesc->n) - 1;
	createArray(arrDesc);
	
	int count;
	for(count = 0){
		
	}
	
	
	
}





#endif 


