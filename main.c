// Adicionar mais retorno para as threads!
// - Quantos elementos a thread processou
// - Quantas diagonais a thread processou
// - Testar se o free está funcionanando no linux
// - Fazer novos testes no linux


/*
Escrito por André L. R. Estevam 		como trabalho para a disciplina de Sistemas
Operacionais (1º Semestre de 2017) da Faculdade de Tecnologia da Unicamp
-------------------------------------------------------------------------------
Este é um programa que lê números com ponto flutuante a partir de um arquivo para
uma matriz m x n com m e n sendo inseridos pelo usuário, o programa usa de 1 a n
threads para processar a soma das diagonais principais armazenando o resultado em
um vetor, podendo ainda gerar dados sobre a execução do programa gravando em um
arquivo .csv que pode ser lido por algum software de panilha eletrônica 
*/

//Incluindo bibliotecas padrão
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <stdbool.h>
#include <time.h>

//Incluindo bibliotecas criadas
#include "util/util.h"//Biblioteca com funções de utilidades diversas
#include "datadefine.h"//Definição de dados (variáveis globais, defines e tipos de dados novos)
#include "dataStructures/array/arrayMngr.h"//Biblioteca para gerenciar o tipo de vetor usado
#include "dataStructures/matrix/matrixMngr.h"//Biblioteca para gerenciar o tipo de matriz usada
#include "thread/thread.h"//Biblioteca contendo funções executadas por threads
#include "file/fileMngr.h"//Bilioteca para definir gerenciamento dos arquivos usados

int main(){
	
	time_t tStart, tEnd;
	double elapsedTime;
	int auxm, auxn;
	int numThreads;
	
	putHeader(DEFAULTEXDATACSVFILE,"tempo;m;n;diagonais;threads\n");
	putHeader(DELAULTTHREADEXCSVFILE,"tnum;elementos_processados;diagonais_processadas\n");
	
	//generateRandomFloatFile("in.txt", 5000000);

	//Se variável ativada vai requerir dados do usuário, caso contrário vai rodar com os valores default
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
    
	//Alocando na memória espaço para o argumento das threads
	ThreadArgsInfo * tinfoptr = (ThreadArgsInfo*) malloc(numThreads * sizeof(ThreadArgsInfo));
	if(tinfoptr == NULL){
		printf("Erro ao alocar argumentos de threads\n");
		return -1;
	}

	//Para cada thread
    for(i = 0; i < numThreads; i++){

		//Inicializando os argumentos das threads
		tinfoptr[i].threadNum = (unsigned short int)i;
        tinfoptr[i].mx = &matrix;
    	tinfoptr[i].rspArr = &rspArr;
    	tinfoptr[i].totThreads = (unsigned int)numThreads;
        
        //Criando thread
		pthread_create(&(tidArr.data[i].dt.tid), NULL, threadSumFunc, &tinfoptr[i]);
	
    }
    
    for(i = 0; i < numThreads; i++){
		pthread_join(tidArr.data[i].dt.tid, NULL);
	}

	
	tEnd = clock();
	if(printInfoProcess){
		printf("Relogio foi parado\n");
	}
	
	//printf("\n--------------------------------------------\n");
	
	printf("\t\tIMPRIMINDO RESULTADOS\n\n");
    for(i = 0; i < matrix.diagNum; i++){
        printf("Diagonal: [%d]\t|\tSoma: %.3f\n",i, rspArr.data[i].dt.rsp);
    }
    

    arrayFloatToFile(rspArr, "out.txt");
 
    
 	//Liberando memória utilizada
 	deleteMatrix(&matrix);
 	deleteArray(&rspArr);
	deleteArray(&tidArr);
 	free(tinfoptr);

	 
	 elapsedTime = difftime(tEnd, tStart);
	 if(generateExecutionData){
		 //Gerando estrutura com dados da execução para gravar num arquivo .csv
		 ExecutionData exdt;
		 exdt.elapsedTime 	= elapsedTime;
		 exdt.m 			= matrix.m;
		 exdt.n 			= matrix.n;
		 exdt.diags 		= matrix.diagNum;
		 exdt.numThreads 	= numThreads;
		 executionDataToCSV(exdt, DEFAULTEXDATACSVFILE);
	 }
	 
	 
	 printf("\nTEMPO GASTO: [%.2lf s]\n", elapsedTime);

    return 0;
}


/*=========================================================================================================*/

	int nomain(){
		int maxthread = 100;
		int loopPerThread = 50;
		double med = 0.0;
		int cont1, cont2;
		
		time_t tStart, tEnd;
		double elapsedTime;
		int auxm, auxn;
		int numThreads;
		
		putHeader(DEFAULTEXDATACSVFILE,"tempo;m;n;diagonais;threads\n");
		putHeader(DELAULTTHREADEXCSVFILE,"tnum;elementos_processados;diagonais_processadas\n");
		
		//generateRandomFloatFile("in.txt", 5000000);
	
		//Se variável ativada vai requerir dados do usuário, caso contrário vai rodar com os valores default
		
		for(cont1 = 0; cont1 < maxthread; cont1++){
			for(cont2 = 0; cont2 < loopPerThread; cont2++){
				
			
			auxm = 900;
			auxn = 900;
			numThreads = cont1;
	
		
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
	    
		//Alocando na memória espaço para o argumento das threads
		ThreadArgsInfo * tinfoptr = (ThreadArgsInfo*) malloc(numThreads * sizeof(ThreadArgsInfo));
		if(tinfoptr == NULL){
			printf("Erro ao alocar argumentos de threads\n");
			return -1;
		}
	
		//Para cada thread
	    for(i = 0; i < numThreads; i++){
	
			//Inicializando os argumentos das threads
			tinfoptr[i].threadNum = (unsigned short int)i;
	        tinfoptr[i].mx = &matrix;
	    	tinfoptr[i].rspArr = &rspArr;
	    	tinfoptr[i].totThreads = (unsigned int)numThreads;
	        
	        //Criando thread
			pthread_create(&(tidArr.data[i].dt.tid), NULL, threadSumFunc, &tinfoptr[i]);
		
	    }
	    
	    for(i = 0; i < numThreads; i++){
			pthread_join(tidArr.data[i].dt.tid, NULL);
		}
	
		
		tEnd = clock();
		if(printInfoProcess){
			printf("Relogio foi parado\n");
		}
		
		//printf("\n--------------------------------------------\n");
		
		printf("\t\tIMPRIMINDO RESULTADOS\n\n");
	    for(i = 0; i < matrix.diagNum; i++){
	        printf("Diagonal: [%d]\t|\tSoma: %.3f\n",i, rspArr.data[i].dt.rsp);
	    }
	    
	
	    arrayFloatToFile(rspArr, "out.txt");
	 
	    
	 	//Liberando memória utilizada
	 	deleteMatrix(&matrix);
	 	deleteArray(&rspArr);
		deleteArray(&tidArr);
	 	free(tinfoptr);
	
		 
		 elapsedTime = difftime(tEnd, tStart);
		 if(generateExecutionData){
			 //Gerando estrutura com dados da execução para gravar num arquivo .csv
			 ExecutionData exdt;
			 exdt.elapsedTime 	= elapsedTime;
			 exdt.m 			= matrix.m;
			 exdt.n 			= matrix.n;
			 exdt.diags 		= matrix.diagNum;
			 exdt.numThreads 	= numThreads;
			 executionDataToCSV(exdt, DEFAULTEXDATACSVFILE);
		 }
		 
		 
		 printf("\nTEMPO GASTO: [%.2lf s]\n", elapsedTime);
		 
		 med+=elapsedTime;
		 
		 
		 }
		 med /= loopPerThread;
		 printf("%lf\n", med);
		 med = 0;
		 }
	
	    return 0;
	}



