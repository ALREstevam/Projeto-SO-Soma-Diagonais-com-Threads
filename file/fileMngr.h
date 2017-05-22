#ifndef PROJSOTEST_FILEMNGR_H
#define PROJSOTEST_FILEMNGR_H

#include <stdio.h>
#include <stdlib.h>
#include "fileMngr.h"
#include "../datadefine.h"
#include "../dataStructures/matrix/matrixMngr.h"

void fileToMatrix(MatrixDescriber mx, char * filename);
void arrayFloatToFile(ArrayDescriber arr, char * filename);
void generateRandomFloatFile(char * filename, int qtd);
void fillFileWithValue(char * filename, int qtd, float value);

#endif //PROJSOTEST_FILEMNGR_H
