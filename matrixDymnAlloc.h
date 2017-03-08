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

//APONTADOR PARA MATRIZ
typedef struct 
{
	MatrixElem **matrix;
	int m, n;
}MatrixDescriber;




/*
Matrizes.   Matrizes (bidimensionais) s�o implementadas como vetores de vetores. Uma matriz com m linhas e n colunas � um vetor cada um de cujos m elementos � um vetor de n elementos. O seguinte fragmento de c�digo faz a aloca��o din�mica de uma tal matriz:

   int **M; 
   int i;
   M = malloc (m * sizeof (int *));
   for (i = 0; i < m; ++i)
      M[i] = malloc (n * sizeof (int));
O elemento de M que est� no cruzamento da linha i com a coluna j � denotado por M[i][j].
*/




//ALOCADOR DE MEM�RIA E INICIALIZADOR DA MATRIZ
void createMatrix(MatrixDescriber *mxDesc){
	int count;
	mxDesc->matrix = /*(MatrixElem * )*/ malloc(mxDesc->m * sizeof(MatrixElem));
	
	for(count = 0; count < mxDesc->n; count++){
		mxDesc->matrix[count] = (MatrixElem * ) malloc(mxDesc->n * sizeof(MatrixElem));
	}
	
	mxDesc->matrix[5][5].value = 10;
	
	printf("%f", mxDesc->matrix[5][5].value);
}

//Inicializando a matriz
void initializeMatrixElem(MatrixDescriber *mh){

}

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


void printMatrix(MatrixDescriber mxDesc){
	int countM, countN;
	int countBrakeRow = 0;
	for(countM = 0; countM < mxDesc.m; countM++){
		if(countBrakeRow == mxDesc.n){
			countBrakeRow = 0;
			printf("\n");
		}
		
		for(countN = 0; countN < mxDesc.n; countN++){
			printf("[%.2f]\t", mxDesc.matrix[countM][countM].value);
		}

	}
	
}





#endif 


