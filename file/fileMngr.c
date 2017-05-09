
#include <stdio.h>
#include "fileMngr.h"
#include "../datadefine.h"
#include "../dataStructures/matrix/matrixMngr.h"


//Função que faz leitura a partir de um arquivo coloca os valores lidos em uma matriz
void fileToMatrix(MatrixDescriber mx, char * filename){
	FILE *in = fopen(filename, "r");
	double value;
	register int i, j;
	
	if(in == NULL){
		return;
	}
	
	while(!feof(in)){
		value = fscanf(in,"%lf ", &value);
		
		for(i = 0; i < mx.m; i++){
			for(j = 0; j < mx.n; j++){
				Coords crd;
				crd.mpos = i;
				crd.npos = j;
			 
			    setElement(mx, crd, value);
				
			}
		}
		
	}
	fclose(in);
}


//Função que passa os valores float de um array para um arquivo
void arrayFloatToFile(ArrayDescriber arr, char * filename){
	FILE * out = fopen(filename, "w+");
	
	if(out == NULL){
		return;
	}
	
	int register i;
	for(i = 0; i < arr.top; i++){
		fprintf(out, "%f\n", arr.data[i].dt.rsp);
	}
	
	fclose(out);
}


