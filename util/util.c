#include <stdio.h>
#include <string.h>
#include <time.h>
#include "../datadefine.h"
#include "../file/fileMngr.h"

void strsubstchar(char * source, char find, char replace){
	int i;
	for(i = 0; source[i] != '\0'; i++){
		if(source[i] == find){
			source[i] = replace;
		}
	}
}

//Fun��o que grava um tipo de dado com informa��es da execu��o do programa em um arquivo .csv
void executionDataToCSV(ExecutionData exd, char * fileName){
	FILE *csvData = fopen(fileName, "a+");
	
	if(csvData == NULL){
		return;
	}
	char str[10];
	sprintf(str, "%.2lf", exd.elapsedTime);
	strsubstchar(str, '.', ',');
	fprintf(csvData, "%s; %d; %d; %d; %d\n",str, exd.m, exd.n, exd.diags, exd.numThreads);
	fclose(csvData);
}


//Fun��o que calcula a diferen�a de tempo entre dois hor�rios
double timediff(clock_t t1, clock_t t2){
    double elapsed;
    elapsed = ((double)(t2 - t1)) / (CLOCKS_PER_SEC * 1000);
    return elapsed;
}

void pause(){
	printf("\nPressione enter para continuar...");
	getchar();
}


void appendToTExecutionFile(char * filename, ThreadExecutionData ted){
	FILE * fl = fopen(filename, "a+");
	
	fprintf(fl, "T%d;%d;%d\n",ted.tnum, ted.processedElems, ted.processedDiags);
	fclose(fl);
}

void putHeader(char * filename, char * csvheader){
	FILE * fl = fopen(filename, "a+");

	fprintf(fl, "%s",csvheader);
	fclose(fl);	
}

void setConfig(bool fllinrnd, bool fllinnum, float flelem, int qtd, char * definpath){
	if(fllinrnd){
		generateRandomFloatFile(definpath, qtd);
	}else if(fllinnum){
		fillFileWithValue(definpath, qtd, flelem);
	}
}






