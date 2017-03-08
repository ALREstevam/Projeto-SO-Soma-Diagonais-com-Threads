#ifndef matrixDymnAlloc
#define matrixDymnAlloc
#include <stdlib.h>

//ELEMENTO DA MATRIZ
typedef struct 
{
	int value;
	int coordX;
	int coordY;
	int pos;
	
}MatrixElem;

//APONTADOR PARA MATRIZ
typedef struct 
{
	MatrixElem *matrix;
	int m, n;
}MatrixHead;


//Coordenadas
typedef struct 
{
	int x, y;
}Coordinates;


//ALOCADOR DE MEMÓRIA E INICIALIZADOR DA MATRIZ
void createMatrix(MatrixHead *mh){
	int count;
	MatrixElem *head = (MatrixElem *)malloc((mh->m * mh->n) * sizeof(MatrixElem));// ALOCANDO (m * n) * sizeof(<elemento da matriz>)
	mh->matrix = head;
}

//Inicializando a matriz
void initializeMatrix(MatrixHead *mh){
	int i;
	for(i = 0; i < (mh->m * mh->n); i ++){
		
	}
}

//
MatrixElem* getElemByPos(MatrixHead *mx, int pos){
	if(pos <= (mx->m * mx->n)){
		return MatrixHead->matrix[pos];
	}else{
		return ;
	}
	
}

getElemByCoord(MatrixHead *mx; int row, int column){
	
}

setElemByPos(MatrixHead *mx, int pos, int value){
	
}

setElemByCoord(MatrixHead *mx, int row, int column, int value){
	
}


//Funções de apoio
int matrixElementAmount(MatrixHead *mx){
	return mx->m * mx->n;
}

posToCoord(MatrixHead *mx, Coordinates *coord, int pos){
	
}

int coordToPos(MatrixHead *mx, int x, int y){
	if(x > mx->m || y > mx->n){
		return -1;
	}
	return (x * mx->m) + mx->n;
}

MatrixElem* getMainDiagonalNextElem(MatrixHead *mx, int *rsp){
	
}


#endif 


