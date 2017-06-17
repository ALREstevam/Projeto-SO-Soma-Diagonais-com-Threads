#ifndef PROJSOTEST_MATRIXMNGR_H
#define PROJSOTEST_MATRIXMNGR_H

/**
*	Biblioteca respons�vel por gerenciar a cria��o, manipul��o e exclus�o
*	de matrizes
*/

#include <stdbool.h>
#include "../../datadefine.h"

//Prot�tipos de fun��es para gerenciar matrizes
bool createMatrix(MatrixDescriber *matrix, unsigned int m, unsigned int n);
bool getNextElemPos(MatrixDescriber mxd, Coords * excCoord);
bool getElement(MatrixDescriber mxd, Coords coord, float *rsp);
bool diagNumToCoord(MatrixDescriber mxd, unsigned int coordNum, Coords *rsp);
void fillMatrix(MatrixDescriber mx, float fillValue);
void fillMatrixWithRandom(MatrixDescriber mx);
bool setElement(MatrixDescriber mx, Coords pos, float value);
void deleteMatrix(MatrixDescriber *mx);
void printMatrixOnScreen(MatrixDescriber mx);

#endif
