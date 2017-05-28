#include <stdio.h>
#include <string.h>
#include <time.h>
#include "../datadefine.h"
#include "../file/fileMngr.h"
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
    double elapsed;
    elapsed = ((double)(t2 - t1)) / (CLOCKS_PER_SEC * 1000);
    return elapsed;
}

void pause(){
	printf("\nPressione enter para continuar...\n");
	getchar();
}


void setConfig(bool fllinrnd, bool fllinnum, float flelem, int qtd, char * definpath){
	if(fllinrnd){
		generateRandomFloatFile(definpath, qtd);
	}else if(fllinnum){
		fillFileWithValue(definpath, qtd, flelem);
	}
}



