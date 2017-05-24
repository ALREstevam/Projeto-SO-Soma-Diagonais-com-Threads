/*
*	Parte do programa responsável por gerenciar a criação, manipulação e exclusão
*	de matrizes
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../../datadefine.h"


//Função para criar uma matriz a partir dos valores das m linhas e n colunas
bool createMatrix(MatrixDescriber *matrix, unsigned int m, unsigned int n){

    matrix->diagNum = (m + n) -1;
    matrix->m = m;
    matrix->n = n;

    matrix->data = malloc(m * sizeof(float*));
    
    if(matrix->data == NULL){
		printf("Erro 1 ao alocar matriz\n");
		getchar();
		return false;
	}

    register int i;
    for(i = 0; i < m; i++){
        matrix->data[i] = malloc(n * sizeof(float));
        if(matrix->data[i] == NULL){
			printf("Erro 2 ao alocar matriz\n");
			getchar();
			return false;
		}
    }

    return true;
}

//Função para verificar se uma coordenada existe dentro de uma matriz
bool coordIsInsideMatrix(MatrixDescriber mx, Coords pos){
    if(pos.mpos < 0 || pos.npos < 0 || pos.mpos >= mx.m || pos.npos >= mx.n){
        return false;
    }
    return true;
}

//Função que dada uma matriz e uma coordenada retorna a coordenada do próximo elemento no sentido da diagonal principal
bool getNextElementPositionMdiags(MatrixDescriber mxd, Coords * excCoord){
    excCoord->npos++;
    excCoord->mpos++;

    if(!coordIsInsideMatrix(mxd, *excCoord)){
        excCoord->npos--;
        excCoord->mpos--;
        return false;
    }

    return true;
}

//Função que retorna um elemento da matriz dadas suas coordenadas
bool getElement(MatrixDescriber mxd, Coords coord, float *rsp){

    //printf("TESTANDO %d %d",coord.mpos, coord.npos);

    if(!coordIsInsideMatrix(mxd, coord)){
        //printf(" !FALSE! \n");
        *rsp = -500;
        return false;
    }

    *(rsp) = mxd.data[coord.mpos][coord.npos];
   // printf(" !TRUE! \n");
    return true;
}

//Função que converte o número de uma diagonal para suas coordenadas
bool diagNumToCoord(MatrixDescriber mxd, unsigned int coordNum, Coords *rsp){
    if(coordNum > mxd.diagNum-1 || coordNum < 0){
        return false;
    }

    if(coordNum <= mxd.m - 1){
        rsp->mpos = (mxd.m - 1) - coordNum;
        rsp->npos = 0;
    }
    else{
        rsp->mpos = 0;
        rsp->npos = coordNum - (mxd.m - 1);
    }

    return true;
}


//Função que preenche toda a matriz com um valor inserido
void fillMatrix(MatrixDescriber mx, float fillValue){
    register int i, j;
    for(i = 0; i < mx.m; i++){
        for(j = 0; j < mx.n; j++){
            mx.data[i][j] = fillValue;
        }

    }
}
//Função que preenche toda a matriz com valores aleatórios
void fillMatrixWithRandom(MatrixDescriber mx){
	register int i, j;
    for(i = 0; i < mx.m; i++){
        for(j = 0; j < mx.n; j++){
            mx.data[i][j] = rand();
        }
    }
}

//Função que grava numa matriz um valor dando suas coordenadas
bool setElement(MatrixDescriber mx, Coords pos, float value){
    if(!coordIsInsideMatrix(mx, pos)){
        return false;
    }
    
    mx.data[pos.mpos][pos.npos] = value;
    return true;
}

//Função que remove uma matriz da memória
void deleteMatrix(MatrixDescriber *mx){
    register int i;
    for(i = 0; i < mx->m; i++){
        free(mx->data[i]);
        mx->data[i] = NULL;
    }
    free(mx->data);
    mx->data = NULL;
    
    
}

//Função que imprime os valores guardados em uma matriz
void printMatrix(MatrixDescriber mx){
    register int i, j;
    for(i = 0; i < mx.m; i++){
        for(j = 0; j < mx.n; j++){
            //printf("[(%d,%d) %.2f] ",i,j,mx.data[i][j]);
            printf("[%4.3g]",mx.data[i][j]);
        }
        printf("\n");
    }
}