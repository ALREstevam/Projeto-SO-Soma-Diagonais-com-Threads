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

int main(){
	time_t tStart, tEnd;
	double elapsedTime;
	int auxm, auxn;
	int numThreads;
	
	//Se variável ativada vai requerir dados do usuário, caso contrário vai rodar com os valores default
	if(getInputFromUser){
		printf("Digite os seguintes valores:\n<linhas> <colunas> <numero de threads>\n");
		
		scanf("%d %d %d",&auxm, &auxn, &numThreads);
		getchar();
	
		
			
	}else{
		auxm = default_M;
		auxn = default_N;
		numThreads = default_NumThreads;
	}
	
	printf("Sera criada uma matriz %d x %d.\nO processamento sera feito com %d threads\n", auxm, auxn, numThreads);
	
	if(getInputFromUser){pause();}
	
	
	tStart = clock();
	register int i;
	
	
	//Definindo vetores e matrizes
    MatrixDescriber matrix;
    ArrayDescriber rspArr;
    ArrayDescriber tidArr;

	//Criando vetores e matrizes
	createMatrix(&matrix, 200, 200);
    createArray(&rspArr, matrix.diagNum);
	createArray(&tidArr, numThreads);
	rspArr.top = matrix.diagNum-1;
	
	
    fillMatrixWithRandom(matrix);


	
	ThreadArgsInfo * tinfoptr = (ThreadArgsInfo*) malloc(numThreads * sizeof(ThreadArgsInfo));

    
    
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
	
    /*for(i = 0; i < matrix.diagNum; i++){
        printf("%d = [%.2f]\n",i, rspArr.data[i].dt.rsp);
    }*/
    	
    	
 	//Liberando memória utilizada
 	deleteMatrix(&matrix);
 	deleteArray(&rspArr);
 	deleteArray(&tidArr);
 	free(tinfoptr);

	 
	 elapsedTime = difftime(tEnd, tStart);
	 
	 
	 //Gerando estrutura com dados da execução para gravar num arquivo .csv
	 ExecutionData exdt;
	 exdt.elapsedTime 	= elapsedTime;
	 exdt.m 			= matrix.m;
	 exdt.n 			= matrix.n;
	 exdt.diags 		= matrix.diagNum;
	 exdt.numThreads 	= numThreads;
	 
	 executionDataToCSV(exdt, DEFAULTEXDATACSVFILE);
	 
	 printf("TEMPO GASTO: %.2lf s\n", elapsedTime);

    return 0;
}

