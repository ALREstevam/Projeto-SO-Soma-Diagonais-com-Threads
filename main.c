/*
Escrito por Andr� L. R. Estevam 		como trabalho para a disciplina de Sistemas
Operacionais (1� Semestre de 2017) da Faculdade de Tecnologia da Unicamp
-------------------------------------------------------------------------------
Este � um programa que l� n�meros com ponto flutuante a partir de um arquivo para
uma matriz m x n com m e n sendo inseridos pelo usu�rio, o programa usa de 1 a n
threads para processar a soma das diagonais principais armazenando o resultado em
um vetor, podendo ainda gerar dados sobre a execu��o do programa gravando em um
arquivo .csv que pode ser lido por algum software de panilha eletr�nica 
*/

//Incluindo bibliotecas padr�o
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <stdbool.h>
#include <time.h>

//Incluindo bibliotecas criadas
#include "util/util.h"//Biblioteca com fun��es de utilidades diversas
#include "datadefine.h"//Defini��o de dados (vari�veis globais, defines e tipos de dados novos)
#include "dataStructures/array/arrayMngr.h"//Biblioteca para gerenciar o tipo de vetor usado
#include "dataStructures/matrix/matrixMngr.h"//Biblioteca para gerenciar o tipo de matriz usada
#include "thread/thread.h"//Biblioteca contendo fun��es executadas por threads
#include "file/fileMngr.h"//Bilioteca para definir gerenciamento dos arquivos usados

int nomain(){
	time_t tStart, tEnd;
	double elapsedTime;
	int auxm, auxn;
	int numThreads;
	
	//generateRandomFloatFile("in.txt", 5000000);

	//Se vari�vel ativada vai requerir dados do usu�rio, caso contr�rio vai rodar com os valores default
	if(getInputFromUser){
		printf("Digite os valores:\n<linhas> <colunas> <qtd. de threads>\n");
		
		scanf("%d %d %d",&auxm, &auxn, &numThreads);
		getchar();	
	}else{
		auxm = default_M;
		auxn = default_N;
		numThreads = default_NumThreads;
	}
	
	printf("Matriz: (%d X %d)\nThreads: %d\n", auxm, auxn, numThreads);
	if(getInputFromUser){pause();}
	
	tStart = clock();
	register int i;
	
	
	//Definindo vetores e matrizes
    MatrixDescriber matrix;
    ArrayDescriber rspArr;
    ArrayDescriber tidArr;

	//Criando vetores e matrizes
	createMatrix(&matrix, auxm, auxn);
    createArray(&rspArr, matrix.diagNum);
	createArray(&tidArr, numThreads);
	rspArr.top = matrix.diagNum-1;
	
	
    //fillMatrixWithRandom(matrix);
    fillMatrix(matrix, 1);
    //fileToMatrix(matrix, "in.txt");
    //printMatrix(matrix);
    
	ThreadArgsInfo * tinfoptr = (ThreadArgsInfo*) malloc(numThreads * sizeof(ThreadArgsInfo));
	if(tinfoptr == NULL){
		printf("Erro ao alocar");
		return -1;
	}

    
    
    for(i = 0; i < numThreads; i++){
        
		tinfoptr[i].threadNum = (unsigned short int)i;
        tinfoptr[i].mx = &matrix;
    	tinfoptr[i].rspArr = &rspArr;
    	tinfoptr[i].totThreads = (unsigned int)numThreads;
        
        
        pthread_create(&(tidArr.data[i].dt.tid), NULL, threadSumFunc, &tinfoptr[i]);
        
    }
    
    for(i = 0; i < numThreads; i++){
		pthread_join(tidArr.data[i].dt.tid, NULL);
	}

	
	tEnd = clock();
	
	//printf("\n--------------------------------------------\n");
	
    for(i = 0; i < matrix.diagNum; i++){
        printf("Soma da diagonal %d = [%.2f]\n",i, rspArr.data[i].dt.rsp);
    }
    
    printf("*");
    arrayFloatToFile(rspArr, "out.txt");
    	printf("*");
 	//Liberando mem�ria utilizada
 	deleteMatrix(&matrix);
 	printf("*");
 	deleteArray(&rspArr);
 	
	deleteArray(&tidArr);
 	free(tinfoptr);

	 
	 elapsedTime = difftime(tEnd, tStart);
	 if(generateExecutionData){
		 //Gerando estrutura com dados da execu��o para gravar num arquivo .csv
		 ExecutionData exdt;
		 exdt.elapsedTime 	= elapsedTime;
		 exdt.m 			= matrix.m;
		 exdt.n 			= matrix.n;
		 exdt.diags 		= matrix.diagNum;
		 exdt.numThreads 	= numThreads;
		 executionDataToCSV(exdt, DEFAULTEXDATACSVFILE);
	 }
	 
	 
	 printf("TEMPO GASTO: %.2lf s\n", elapsedTime);

    return 0;
}

