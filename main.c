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

double exec(int nt){	
	time_t tStart = 0, tEnd = 0;
	pthread_mutex_t lock;
	pthread_mutex_init(&lock, NULL);
	unsigned int diagNum = 0;
	int auxm, auxn, numThreads;
	double elapsedTime;
	
	
	//Se requerir entrada do usuário estiver ativado
	if(getInputFromUser){
		printf("Digite os valores:\n<linhas> <colunas> <qtd. de threads>\n");
		
		scanf("%d %d %d",&auxm, &auxn, &numThreads);
		getchar();	
	}else{//Definição dos valores default
		auxm = default_M;
		auxn = default_N;
		//numThreads = default_NumThreads;
		numThreads = nt;
	}

	//Definindo vetores e matrizes
    MatrixDescriber matrix;
    ArrayDescriber rspArr;
    ArrayDescriber tidArr;

	//Criando vetores e matrizes
	createMatrix(&matrix, auxm, auxn);
    createArray(&rspArr, matrix.diagNum);
	createArray(&tidArr, numThreads);
	rspArr.top = matrix.diagNum-1;
	
	//Lendo arquivo de entrada
    fileToMatrix(matrix, defaultInputPath);
	
	ThreadArgsInfo1 targs;
	targs.mx = &matrix;
	targs.rspArr = &rspArr;
	targs.lock = &lock;
	targs.contDiag = &diagNum;
		
	register int i;
	
	tStart = clock();//Disparando relógio
	for(i = 0; i < numThreads; i++){
		pthread_create(&(tidArr.data[i].tid), NULL, threadSumFunc1, &targs);
	}

	for(i = 0; i < numThreads; i++){
		pthread_join(tidArr.data[i].tid, NULL);
	}
	tEnd = clock();//Parando relógio
	pthread_mutex_destroy(&lock);//destruindo o mutex
	
	arrayFloatToFile(rspArr, defaultOutputPath);
	
	/*printf("\t\tIMPRIMINDO RESULTADOS\n\n");
    for(i = 0; i < matrix.diagNum; i++){
        printf("Diagonal: [%d]\t|\tSoma: %.3f\n",i, rspArr.data[i].rsp);
	}*/
    
 	//Liberando memória utilizada
 	deleteMatrix(&matrix);
 	
 	deleteArray(&rspArr);
	deleteArray(&tidArr);

	elapsedTime = difftime(tEnd, tStart);//Calculando tempo gasto
	//printf("TEMPO GASTO: %.2lf s\n", elapsedTime);
	
	/*FILE *fl = fopen("data.csv","a+");
	fprintf(fl, "%d; %f\n", numThreads, elapsedTime);*/
	return elapsedTime;
}

int main(){
	int tcount, loopcount, maxt = 10, maxloop = 40;
	double med = 0;
	FILE *fl = fopen("data1.csv", "w");
	
	for(tcount = 1; tcount < maxt; tcount++){
		for(loopcount = 0; loopcount < maxloop; loopcount++){
			med += exec(tcount);
		}
		fprintf(fl, "%d; %lf\n",tcount, (med/loopcount));
		med = 0;
	}
	return 0;
}
