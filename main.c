#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "global.h"
#include "matrix/matrixDymnAlloc.h"


int main()
{
	MatrixDescriber mxDesc;
	mxDesc.matrix = NULL;
	mxDesc.m = 3;
	mxDesc.n = 3;
	
	createMatrix(&mxDesc);
	
	
	//setFillRandom(&mxDesc);
	setFillOrder(&mxDesc, 1.0);
	printMatrix(mxDesc, 2);

	
	return 0;
}


