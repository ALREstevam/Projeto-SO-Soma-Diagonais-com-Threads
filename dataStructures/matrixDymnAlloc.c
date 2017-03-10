#ifndef matrixDymnAlloc_C
#define matrixDymnAlloc_C

#include <stdlib.h>
#include <stdio.h>
#include "../global.h"
#include "arrayDymnAlloc.h"




/*=================================================================================
							CRIA��O DA MATRIZ
==================================================================================*/

//ALOCADOR DE MEM�RIA E INICIALIZADOR DA MATRIZ
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
	//O elemento n�o tem pr�xmo pois est� fora da matriz
	if(x > coords->x || y > coords->y){
		coords->x = -2;
		coords->y = -2;

	//O elemento existe, portando deve existir pr�ximo se o elemento n�o for o �ltimo da diagonal
	}else if(x > coords->x || y > coords->y){
		coords->x = coords->x - 1;
		coords->y = coords->y + 1;
	}
	//O elemento n�o tem pr�ximo pois a posi��o do pr�ximo est� fora da matriz
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
							EXIBI��O DA MATRIZ
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
							FUN��ES DE SET
==================================================================================*/
//Inserir n�mero em uma posi��o 
int setMatrixValue(MatrixDescriber *mxDesc, int x, int y, float value){
	if(mxDesc->matrix == NULL || mxDesc->m < 0 || mxDesc-> n < 0 || x > mxDesc->m || y > mxDesc->n){
		return -1;
	}else{
		mxDesc->matrix[x][y].value = value;
		return 0;
	}
}

//Preencher com n�meros rand�micos
void setFillRandom(MatrixDescriber *mxDesc){
	int countM, countN;
	for(countM = 0; countM < mxDesc->m; countM++){
		for(countN = 0; countN < mxDesc->n; countN++){
			mxDesc->matrix[countM][countN].value = rand();
		}
	}
}

//Preencher com n�meros de forma ordenada
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
						C�LCULO DA SOMA DE UMA DIAGONAL
==================================================================================*/
void diagonalFirstPositionToArray(MatrixDescriber *mxDesc, ArrayDescriber *arrDesc){
	arrDesc->size = (mxDesc->m + mxDesc->n) - 1;
	createArray(arrDesc);
	
	int count;
	for(count = 0){
		
	}
	
	
	
}





#endif 


