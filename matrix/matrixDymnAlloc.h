#ifndef matrixDymnAlloc_H
#define matrixDymnAlloc_H

void test();


void createMatrix					(MatrixDescriber *mxDesc);
void initializeMatrixElem			(MatrixDescriber *mxDesc);
void getNextElemInMainDiagonal		(MatrixDescriber *mxDesc, CoordinatesXY *coords, int x, int y);
void printMatrix					(MatrixDescriber mxDesc, int flag_mode);
int setMatrixValue					(MatrixDescriber *mxDesc, int x, int y, float value);
void setFillRandom					(MatrixDescriber *mxDesc);
void setFillOrder					(MatrixDescriber *mxDesc, float start);

#endif