#include <stdio.h>
#include <string.h>
#include <time.h>
#include "../datadefine.h"


//Função que grava um tipo de dado com informações da execução do programa em um arquivo .csv
void executionDataToCSV(ExecutionData exd, char * fileName){
	FILE *csvData = fopen(fileName, "a+");
	
	if(csvData == NULL){
		return;
	}
	fprintf(csvData, "%lf; %d; %d; %d; %d\n",exd.elapsedTime, exd.m, exd.n, exd.
	diags, exd.numThreads);
	fclose(csvData);
}


//Função que calcula a diferença de tempo entre dois horários
double timediff(clock_t t1, clock_t t2){
    double elapsed;
    elapsed = ((double)(t2 - t1)) / (CLOCKS_PER_SEC * 1000);
    return elapsed;
}

void pause(){
	printf("\nPressione enter para continuar...");
	getchar();
}

bool verifyIsGreaterThanZero(int num, char * msgFalse){
	if(num > 0){
		return true;
	}
	printf("%s\n", msgFalse);
	return false;
}








