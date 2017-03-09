#ifndef matrixDymnAlloc
#define matrixDymnAlloc
#include <stdlib.h>

//Coordenadas
typedef struct 
{
	int x, y;
}CoordinatesXY;

//ELEMENTO DA MATRIZ
typedef struct 
{
	double value;
	CoordinatesXY nextInMainDiagonal;
	//int pos;
	//XYCoordinates coord;
	
}MatrixElem;

//DESCRITOR DE MATRIZ
typedef struct 
{
	MatrixElem **matrix;
	int m, n;
}MatrixDescriber;




/*
Matrizes.   Matrizes (bidimensionais) são implementadas como vetores de vetores. Uma matriz com m linhas e n colunas é um vetor cada um de cujos m elementos é um vetor de n elementos. O seguinte fragmento de código faz a alocação dinâmica de uma tal matriz:

   int **M; 
   int i;
   M = malloc (m * sizeof (int *));
   for (i = 0; i < m; ++i)
      M[i] = malloc (n * sizeof (int));
O elemento de M que está no cruzamento da linha i com a coluna j é denotado por M[i][j].
*/


/*=================================================================================
							CRIAÇÃO DA MATRIZ
==================================================================================*/

//ALOCADOR DE MEMÓRIA E INICIALIZADOR DA MATRIZ
void createMatrix(MatrixDescriber *mxDesc){
	int count;
	mxDesc->matrix = malloc(mxDesc->m * sizeof(MatrixElem));
	
	for(count = 0; count < mxDesc->n; count++){
		mxDesc->matrix[count] = (MatrixElem * ) malloc(mxDesc->n * sizeof(MatrixElem));
	}
}

//Inicializando a matriz
void initializeMatrixElem(MatrixDescriber *mh){

}

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


/*=================================================================================
							EXIBIÇÃO DA MATRIZ
==================================================================================*/
void printMatrix(MatrixDescriber mxDesc){
	int countM, countN;
	
	printf("\n");
	printf("\tMATRIZ\n");
	
	for(countM = 0; countM < mxDesc.m; countM++){
		for(countN = 0; countN < mxDesc.n; countN++){
			printf("[%2.1f]\t", mxDesc.matrix[countM][countM].value);
		}
		printf("\n");
	}
	printf("\n");
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
			start += 1;
			
			setMatrixValue(mxDesc, countM, countN, 1.0);
			printf(" |(%d,%d)", countM, countN);
			printf("->%2.2f| ", start);			
		}
		printf("\n");
	}
	printf("\n");
	
}







#endif 


