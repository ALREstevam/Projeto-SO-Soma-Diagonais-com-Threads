#include <stdio.h>
#include <string.h>
#include <time.h>
#include "../datadefine.h"
#include "../File/fileMngr.h"
#include <pthread.h>

void strsubstchar(char * source, char find, char replace){
	int i;
	for(i = 0; source[i] != '\0'; i++){
		if(source[i] == find){
			source[i] = replace;
		}
	}
}

char * dotToCommaFloat(float num){
	int i, part = (int)num, size;
	
	for(i = 0; part != 0; i++){
		part /= 10;
	}
	
	size = 1 + 5 + i;
	char * str  = (char*) malloc(size * sizeof(char));
	
	sprintf(str, "%.5f", num);
	
	for(i = 0; i < size; i++){
		if(str[i] == '.'){
			str[i] = ',';
		}
	}
	
	return str;
}

char * dotToCommaDouble(double num){
	int i, part = (int)num, size;
	
	for(i = 0; part != 0; i++){
		part /= 10;
	}
	
	size = 1 + 10 + i;
	char * str  = (char*) malloc(size * sizeof(char));
	
	sprintf(str, "%.10lf", num);
	
	for(i = 0; i < size; i++){
		if(str[i] == '.'){
			str[i] = ',';
		}
	}
	
	return str;
}


//Função que calcula a diferença de tempo entre dois horários
double timediff(clock_t t1, clock_t t2){
	if(t1 > t2){
		return ((double)(t1 - t2)) / (CLOCKS_PER_SEC * 1000);
	}else{
		return ((double)(t2 - t1)) / (CLOCKS_PER_SEC * 1000);
	}
}

void pauseMsg(){
	printf("\nPressione enter para continuar...");
	getchar();
	printf("\n");
}


void setConfig(bool fllinrnd, bool fllinnum, float flelem, int qtd, char * definpath){
	if(fllinrnd){
		generateRandomFloatFile(definpath, qtd);
	}else if(fllinnum){
		fillFileWithValue(definpath, qtd, flelem);
	}
}

Input inputFromUser(){
	Input rsp;
	
	printf("Numero de threads: ");
	fscanf(stdin,"%d",&rsp.numThreads);
	printf("Matriz (m linhas): ");
	fscanf(stdin, "\n%d", &rsp.matrixm);
	printf("Matriz (n colunas): ");
	fscanf(stdin, "\n%d", &rsp.matrixn);
	getchar();
	printf("\n[ VOCE ESCOLHEU ]\nTHREADS: %d\nMATRIZ(m X n): (%d X %d)\n", rsp.numThreads, rsp.matrixm, rsp.matrixn);
	
	pauseMsg();
	return rsp;
}

void OutputSumToUser(MatrixDescriber *matrix, ArrayDescriber *rspArr){
	register int i;
	printf("\t\tIMPRIMINDO RESULTADOS\n\n");
	printf("+---------------+---------------+------------------+\n");
	printf("%c  PRIM. ELEM.\t%c NUM. DA DIAG.\t%c       SOMA\t   %c\n",'|','|','|','|');
    for(i = 0; i < matrix->diagNum; i++){
    	Coords c;
    	diagNumToCoord(*matrix, i, &c);
        printf("%c(%3d,%3d)\t%c\t%4d\t%c\t%.7g\t   %c\n",'|',c.mpos, c.npos,'|', i,'|', rspArr->data[i].rsp,'|');
	}														   +						
	printf("+---------------+---------------+------------------+\n");
}


