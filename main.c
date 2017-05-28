/*
Escrito por André L. R. Estevam 		como trabalho para a disciplina de Sistemas
Operacionais (1º Semestre de 2017) da Faculdade de Tecnologia da Unicamp
-------------------------------------------------------------------------------
Este é um programa que lê números com ponto flutuante a partir de um arquivo para
uma matriz m x n com m e n sendo inseridos pelo usuário, o programa usa de 1 a n
threads para processar a soma das diagonais principais armazenando o resultado em
um vetor, podendo ainda gerar dados sobre a execução do programa gravando em um
arquivo .csv que pode ser lido por algum software de panilha eletrônica. 

DETALHES SOBRE O FUNCIONAMENTO:
-Configurações: as constantes de configuração estão no arquivo "datadefine.h"

-Booleanos
getInputFromUser       se ativado o programa perguntará ao usuário as dimensões da matriz e a quantidade de threads a usar		
printInfoProcess 	   se ativado o programa irá imprimir informações sobre o processamento
fillInputWithRandom	   se ativado o programa irá preencher a entrada padrão com valores aleatórios
fillInputWithNum 	   se ativado o programa irá preencher a entrada padrão com um determinado valor

//Parâmetros
float fillElement 	    elementos a gravar na entrada padrão  		
int fileElementsAmount  quantidade de elementos a gravar na entrada padrão
												

//Valores default
int default_M 		     Valor padrão de linhas da matriz (caso entrada de dados pelo usuário seja desativada)	
int default_N 		     Valor padrão de colunas da matriz (caso entrada de dados pelo usuário seja desativada)
int default_NumThreads 	 Quantidade padrão de threads (caso entrada de dados pelo usuário seja desativada)


-Arquivos:
	Se os arquivos de entrada e saída não existirem, serão criados.
	Se o arquivo de entrada estiver vazio ou incompleto, os elementos da matriz sem valor
	correspondente serão preenchidos com 0;
	É possível usar as configurações para fazer o programa gerar o arquivo de entrada com
	n repetições de um valor definido ou valores randômicos
	
-Threads:
Cada thread irá acessar uma região crítica que indica o número da próxima diagonal a ser processada
copiar o valor da região e incrementar seu valor.

A thread converte o número da diagonal para a coordenada do primeiro elemento dessa diagonal, acessa
esse valor e soma sucessivamente os valores dessa diagonal. Ao finalizar o processamento a soma é 
armazenada num vetor, se a diagonal processada foi x, a soma é armazenada em vet[x].

O processo é repetido até que a thread leia da região crítica um número de diagonal que não
pertence à matriz.

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

double exec(unsigned int thrdqtd, unsigned int matrixM, unsigned int matrixN){	
	

	
	//DECLARAÇÃO DE VARIÁVEIS
	time_t tStart = 0, tEnd = 0;//Declarando relógios
	pthread_mutex_t lock;//Declarando mutex
	pthread_mutex_init(&lock, NULL);//Iniciando mutex
	unsigned short int diagNum = 0;//Definindo área crítica
	int auxm, auxn;//Auxiliares
	unsigned short int numThreads;
	double elapsedTime;//Armazenamento do tempo gasto
	register int i;
	
	auxm = matrixM;
	auxn = matrixN;
	numThreads = thrdqtd;
	
	tStart = clock();//Disparando relógio
	
	//Definindo vetores e matrizes
    MatrixDescriber matrix;
    ArrayDescriber rspArr;
    ArrayDescriber tidArr;

	//Criando vetores e matrizes
	createMatrix(&matrix, auxm, auxn);
    createArray(&rspArr, (int)matrix.diagNum);
	createArray(&tidArr, numThreads);
	rspArr.top = matrix.diagNum-1;
	
	//Lendo arquivo de entrada
    fileToMatrix(matrix, defaultInputPath);
	
	ThreadArgsInfo targs;
	targs.mx = &matrix;
	targs.rspArr = &rspArr;
	targs.lock = &lock;
	targs.contDiag = &diagNum;
		
	
	for(i = 0; i < numThreads; i++){
		pthread_create(&(tidArr.data[i].tid), NULL, threadSumFunc, &targs);
	}
	for(i = 0; i < numThreads; i++){
		pthread_join(tidArr.data[i].tid, NULL);
	}
	tEnd = clock();//Parando relógio
	pthread_mutex_destroy(&lock);//destruindo o mutex
	
	arrayFloatToFile(rspArr, defaultOutputPath);
	
	
	printf("\t\tIMPRIMINDO RESULTADOS\n\n");
	printf("%c  PRIM. ELEM.\t%c NUM. DA DIAG.\t%c       SOMA\t   %c\n",179,179,179,179);
    for(i = 0; i < matrix.diagNum; i++){
    	Coords c;
    	diagNumToCoord(matrix, i, &c);
        printf("%c(%3d,%3d)\t%c\t%4d\t%c\t%.7g\t   %c\n",179,c.mpos, c.npos,179, i,179, rspArr.data[i].rsp,179);
	}
	printf("---------------------------------------------------------\n");
    
    elapsedTime = difftime(tEnd, tStart);//Calculando tempo gasto
    printf("[TEMPO GASTO: %.2lf ms  | \tTHREADS: %d]\n", elapsedTime, numThreads);
    
 	//Liberando memória utilizada
 	deleteMatrix(&matrix);
 	deleteArray(&rspArr);
	deleteArray(&tidArr);
	
	return elapsedTime;
}

int nomain(){
	unsigned int auxm, auxn, numThreads, threadCount;
	unsigned short register int i;
	int loops = 100;
	double med;
	
	//Se requerir entrada do usuário estiver ativado
	if(getInputFromUser){
		printf("Digite os valores:\n<linhas> <colunas> <qtd. de threads>\n");
		scanf("%d %d %d",&auxm, &auxn, &numThreads);
		printf("\nMATRIX m x n: [%d,%d]\nTHREADS: %d\n\n",auxm,auxn, numThreads);	
		pause();
	}else{//Definição dos valores default
		auxm = default_M;
		auxn = default_N;
		numThreads = default_NumThreads;
	}
	
	//for(threadCount = 1; threadCount < 4096; threadCount *= 2){
	for(threadCount = 1; threadCount < 16; threadCount++){
		for(i = 1; i < loops; i++){
			printf("[ %03d | ",i);
			med = exec(threadCount, auxm, auxn);
		}
		med /= loops;
		printf("\n----------------------------------------------------\n");
		printf("TEMPO MEDIO: %s ms | \tTHREADS: %03d ]", dotToCommaDouble(med), threadCount);
		printf("\n----------------------------------------------------\n");
		FILE * fl = fopen("time.csv", "a+");
		fprintf(fl,"THREADS;%d;TEMPO;%s;LOOPS;%d\n",threadCount, dotToCommaDouble(med),loops);
	}
return 0;
}

int main(){
	unsigned int auxm, auxn, numThreads;

	//Se requerir entrada do usuário estiver ativado
	if(getInputFromUser){
		printf("Digite os valores:\n<linhas> <colunas> <qtd. de threads>\n");
		scanf("%d %d %d",&auxm, &auxn, &numThreads);
		printf("\nMATRIZ m x n: [%d,%d]\nTHREADS: %d\n\n",auxm,auxn, numThreads);
		getchar();
		pause();
	}else{//Definição dos valores default
		auxm = default_M;
		auxn = default_N;
		numThreads = default_NumThreads;
	}	
	
	exec(numThreads, auxm, auxn);
return 0;
}

