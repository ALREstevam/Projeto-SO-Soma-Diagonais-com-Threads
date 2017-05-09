#include <stdio.h>
#include <string.h>
#include <time.h>
#include "../datadefine.h"




void strsubstchar(char * source, char find, char replace){
	int i;
	for(i = 0; source[i] != '\0'; i++){
		if(source[i] == find){
			source[i] = replace;
		}
	}
}

//Função que grava um tipo de dado com informações da execução do programa em um arquivo .csv
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

void appendToMedFile(char * filename, int threads, double time){
	FILE * fl = fopen(filename, "a+");
	
	char str[10];
	sprintf(str, "%.2lf", time);
	strsubstchar(str, '.', ',');
	fprintf(fl, "%d;%s\n",threads, str);
	
	fclose(fl);
	
}






