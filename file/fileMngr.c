
#include <stdio.h>
#include <stdlib.h>
#include "fileMngr.h"
#include "../datadefine.h"
#include "../dataStructures/matrix/matrixMngr.h"


//Função que faz leitura a partir de um arquivo coloca os valores lidos em uma matriz
void fileToMatrix(MatrixDescriber mx,char * filename) {
	FILE * in = fopen(filename, "r");
	float value;
	register int i, j;

	if(in == NULL) {
		return;
	}

	for(i = 0; i < mx.m; i++) {
		for(j = 0; j < mx.n; j++) {
			if(!feof(in)) {
				fscanf(in, "%f ", &value);
			} else {
				//value = (float)(((rand() % 60) / 10.0) * 5);
				value = 0.0;
			}
			Coords crd;
			crd.mpos = i;
			crd.npos = j;

			setElement(mx, crd, value);
		}
	}
	fclose(in);
}

//Função que passa os valores float de um array para um arquivo
void arrayFloatToFile(ArrayDescriber arr, char * filename) {
	FILE * out = fopen(filename, "w+");

	if(out == NULL) {
		return;
	}

	int register i;
	for(i = 0; i < arr.top+1; i++) {
		fprintf(out, "%f\n", arr.data[i].rsp);
	}

	fclose(out);
}

void generateRandomFloatFile(char * filename, int qtd) {
	FILE * fl = fopen(filename, "w");
	if(fl == NULL) {
		return;
	}
	register int i;
	for(i = 0; i < qtd; i++) {
		fprintf(fl, "%f ",  ((float)(rand() % 60) / 10.0) * 5);
	}
}

void fillFileWithValue(char * filename, int qtd, float value) {
	FILE * fl = fopen(filename, "w");
	
	if(fl == NULL) {
		return;
	}
	register int i;
	for(i = 0; i < qtd; i++) {
		fprintf(fl, "%f ", value);
	}
}


