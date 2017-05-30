#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>
#include "thread.h"
#include "../util/util.h"
#include "../datadefine.h"
#include "../dataStructures/array/arrayMngr.h"
#include "../dataStructures/matrix/matrixMngr.h"
#include "../file/fileMngr.h"


void execMethod_a(Input in, DataCollector *rsp){
	rsp->requiredThreads = 0;
	rsp->usedThreads = 0;
	rsp->createdTheads = 0;
	
	pthread_mutex_t lock;//Declarando mutex
	pthread_mutex_init(&lock, NULL);//Iniciando mutex
	unsigned short int diagNum = 0;//Definindo área crítica
	
	unsigned short int register i, j;
	unsigned short int *proc = 0, createdThreads = 0;
	
	
	//Definindo vetores e matrizes
    MatrixDescriber matrix;
    ArrayDescriber rspArr;
    ArrayDescriber tidArr;

	//Criando vetores e matrizes
	createMatrix(&matrix, in.matrixm, in.matrixn);
    createArray(&rspArr, (int)matrix.diagNum);
	createArray(&tidArr, in.numThreads);
	rspArr.top = matrix.diagNum-1;
	
	//Lendo arquivo de entrada
    fileToMatrix(matrix, defaultInputPath);
	
	ThreadArgsInfo_m1 targs;
	targs.mx = &matrix;
	targs.rspArr = &rspArr;
	targs.lock = &lock;
	targs.contDiag = &diagNum;
		
	
	
	for(i = 0; i < in.numThreads; i++){
		createdThreads++;
		pthread_create(&(tidArr.data[i].tid), NULL, threadSumFunc_meth1, &targs);	
	}
	
	for(i = 0; i < createdThreads; i++){
		pthread_join(tidArr.data[i].tid, (void**)&proc);
		
		printf("[ THREAD  %3d ][SOMAS: %6d]", i, *(proc));
		for(j = 0; j < ( 100*(*(proc)/ (in.matrixm*in.matrixn))); j++){
			printf("#");
		}
		
		printf("\n");
		
		if(*(proc)!= 0){
			(rsp->usedThreads) += 1.0;
		}
		
		free(proc);
	}
	pthread_mutex_destroy(&lock);//destruindo o mutex	
	arrayFloatToFile(rspArr, defaultOutputPath);
	
	OutputSum(&matrix, &rspArr);
	
 	//Liberando memória utilizada
 	deleteMatrix(&matrix);
 	deleteArray(&rspArr);
	deleteArray(&tidArr);
	
	rsp->requiredThreads = in.numThreads;
	rsp->createdTheads = createdThreads;
	rsp->m = in.matrixm;
	rsp->n = in.matrixn;
}


void execMethod_b(Input in, DataCollector *rsp){	
	unsigned short register int i, j;
	unsigned short int *proc = 0;
	
	//Definindo vetores e matrizes
    MatrixDescriber matrix;
    ArrayDescriber rspArr;
    ArrayDescriber tidArr;

	//Criando vetores e matrizes
	createMatrix(&matrix, in.matrixm, in.matrixn);
    createArray(&rspArr, matrix.diagNum);
	createArray(&tidArr, in.numThreads);
	rspArr.top = matrix.diagNum-1;
	
	//Lendo arquivo de entrada
    fileToMatrix(matrix, defaultInputPath);

    
	//Alocando na memória espaço para o argumento das threads
	ThreadArgsInfo_m2 * tinfoptr = (ThreadArgsInfo_m2*) malloc(in.numThreads * sizeof(ThreadArgsInfo_m2));
	if(tinfoptr == NULL){
		fprintf(stderr,"Erro ao alocar argumentos de threads\n");
		exit(-1);
	}

	//Para cada thread
    for(i = 0; i < in.numThreads; i++){
		//Inicializando os argumentos das threads
		tinfoptr[i].threadNum = (unsigned short int)i;
        tinfoptr[i].mx = &matrix;
    	tinfoptr[i].rspArr = &rspArr;
    	tinfoptr[i].totThreads = (unsigned int)in.numThreads;
        
        //Criando thread
		pthread_create(&(tidArr.data[i].tid), NULL, threadSumFunc_meth2, &tinfoptr[i]);
		printf("CREATE: %ld\n", tidArr.data[i].tid);
	
    }

	for(i = 0; i < in.numThreads; i++){
		pthread_join(tidArr.data[i].tid, (void**)proc);		
		/*printf("[ THREAD  %3d ][SOMAS: %6d]", i, *(proc));
		for(j = 0; j < ( 100*(*(proc)/ (in.matrixm*in.matrixn))); j++){
			printf("#");
		}
		printf("\n");
		
		if(*(proc)!= 0){
			(rsp->usedThreads) += 1.0;
		}*/
		
		free(proc);
	}
	

	OutputSum(&matrix, &rspArr);
	
	
    arrayFloatToFile(rspArr, defaultOutputPath);
 
    
 	//Liberando memória utilizada
 	deleteMatrix(&matrix);
 	deleteArray(&rspArr);
	deleteArray(&tidArr);
 	free(tinfoptr);
}