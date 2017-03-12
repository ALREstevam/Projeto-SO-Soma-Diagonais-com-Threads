#ifndef matrixDymnAlloc_C
#define matrixDymnAlloc_C

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "../global.h"
#include "arrayDymnAlloc.h"


/*=================================================================================
							CRIAÇÃO DA MATRIZ
==================================================================================*/

//ALOCADOR DE MEMÓRIA E INICIALIZADOR DA MATRIZ
int createMatrix(MatrixDescriber *mxDesc){
	int count;
	
	if(mxDesc->m <= 0 || mxDesc->n <= 0){
		return -2;
	}
	
	
	//LINHAS
	
	//Alocando array de ponteiros para array de struct
	mxDesc->matrix = (MatrixElem ** ) malloc((mxDesc->m) * (sizeof(MatrixElem *)));
	
	//Verificando se alocado com sucesso
	if(mxDesc->matrix == NULL){
		return -1;
	}
	
	//COLUNAS
	
	for(count = 0; count < mxDesc->m; count++){
		//Alocando array que representa coluna
		mxDesc->matrix[count] = (MatrixElem * ) malloc((mxDesc->n) * (sizeof(MatrixElem)));
		
		//Verificando se foi alocado
		if(mxDesc->matrix[count] == NULL){
			return count * (-1);//Retorna: - <nº do elemento com erro>
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
			case 3:
				if(mxDesc.matrix[countM] == NULL){
					printf("Erro em: %d,%d \n", countM, countN);
				}
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
	printf("\n\n=================== INFORMACOES SOBRE MATRIZ ===================\n");
	printf("Size (elements):           %d\n", mxDesc.m * mxDesc.n);
	printf("Size (memory):             %d bytes\n", mxDesc.m * mxDesc.n * sizeof(MatrixElem));
	printf("Size (each element):       %d bytes\n", sizeof(MatrixElem));
	printf("m ou x (linhas):           %d\n", mxDesc.m);
	printf("n ou y (colunas):          %d\n", mxDesc.n);
	printf("================================================================\n\n");
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
	if(mxDesc->matrix == NULL){
		return;
	}
	
	for(countM = 0; countM < mxDesc->m; countM++){
		for(countN = 0; countN < mxDesc->n; countN++){
			
			mxDesc->matrix[countM][countN].value = rand()%100;
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

//Preencher todos os elementos com um mesmo valor
void setFillAll(MatrixDescriber *mxDesc, float value){
	int countM, countN;
	
	for(countM = 0; countM < mxDesc->m; countM++){
		for(countN = 0; (countN < mxDesc->n); countN++){
			setMatrixValue(mxDesc, countM, countN, value);	
		}
		printf("\n");
	}
	printf("\n");
	
}

/*=================================================================================
						CÁLCULO DA SOMA DE UMA DIAGONAL
==================================================================================*/
int mainDiagonalStartToStack(MatrixDescriber *mxDesc, ArrayDescriber *arrDesc){
	arrDesc->size = (mxDesc->m + mxDesc->n) - 1;
	strcpy(arrDesc->dataType, "cxy");
	
	if(createArray(arrDesc) < 0){
		return -1;
	}
	
	CoordinatesXY coord;
	Var vr;
	int count;

	//Processando linhas
	for(count = 0; (count < mxDesc->m) ; count++){
		coord.x = count;
		coord.y = 0;
		
		vr.coords = coord;
		
		//printf("(%d, %d)", coord.x, coord.y);
		
		addElementOnTop(arrDesc, vr);
	}
	
	//Processando colunas
	for(count = 1; (count < mxDesc->n); count++){
		coord.x = mxDesc->m -1;
		coord.y = count;
		//printf("(%d, %d);  ", coord.x, coord.y);
		vr.coords = coord;
		addElementOnTop(arrDesc, vr);
	}

	
	
	return 0;
}





#endif 


