#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "matrixDymnAlloc.h"


int main()
{
	MatrixDescriber mxDesc;
	
	mxDesc.m = 3;
	mxDesc.n = 3;
	
	
	createMatrix(&mxDesc);
	//printMatrix(mxDesc);

	return 0;
}


