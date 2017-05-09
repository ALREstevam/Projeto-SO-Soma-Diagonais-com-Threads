#ifndef matrixDymnAlloc_H
#define matrixDymnAlloc_H

int createMatrix					(MatrixDescriber *mxDesc);
void initializeMatrixElem			(MatrixDescriber *mxDesc);
void getNextElemInMainDiagonal		(MatrixDescriber *mxDesc, CoordinatesXY *coords, int x, int y);
void printMatrix					(MatrixDescriber mxDesc, int flag_mode);
void printMatrixInfo				(MatrixDescriber mxDesc);
int setMatrixValue					(MatrixDescriber *mxDesc, int x, int y, float value);
void setFillRandom					(MatrixDescriber *mxDesc);
void setFillOrder					(MatrixDescriber *mxDesc, float start);
void setFillAll						(MatrixDescriber *mxDesc, float value);
int mainDiagonalStartToStack		(MatrixDescriber *mxDesc, ArrayDescriber *arrDesc);

#endif