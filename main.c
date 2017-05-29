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

void exec(unsigned int thrdqtd, unsigned int matrixM, unsigned int matrixN, DataCollector *rsp){	
	//DECLARAÇÃO DE VARIÁVEIS
	rsp->requiredThreads = 0;
	rsp->usedThreads = 0;
	rsp->createdTheads = 0;
	
	time_t tStart = 0, tEnd = 0;//Declarando relógios
	
	pthread_mutex_t lock;//Declarando mutex
	pthread_mutex_init(&lock, NULL);//Iniciando mutex
	unsigned short int diagNum = 0;//Definindo área crítica
	
	int auxm, auxn;//Auxiliares
	unsigned short int numThreads;
	double elapsedTime;//Armazenamento do tempo gasto
	register int i;
	unsigned short int j;
	
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
		
	unsigned short int *proc = 0, createdThreads = 0;
	
	for(i = 0; i < numThreads; i++){
		pthread_mutex_lock(&lock);
			if(diagNum >= matrix.diagNum){
				//printf("Processamento terminou antes da criacao de todas as threads!\n");
				pthread_mutex_unlock(&lock);
				break;
			}
		pthread_mutex_unlock(&lock);
		
		//printf("Criando thread %d \n", createdThreads);
		createdThreads++;
		pthread_create(&(tidArr.data[i].tid), NULL, threadSumFunc, &targs);
		
		
	}
	
	for(i = 0; i < createdThreads; i++){
		pthread_join(tidArr.data[i].tid, (void**)&proc);
		
		/*printf("[ THREAD  %3d ][SOMAS: %6d]", i, *(proc));
		for(j = 0; j < ( *(proc)/ (auxm*auxn))*100; j++){
			printf("#");
		}
		
		printf("\n");*/
		
		if(*(proc)!= 0){
			(rsp->usedThreads) += 1.0;
		}
		
		free(proc);
	}
	
	
	tEnd = clock();//Parando relógio
	pthread_mutex_destroy(&lock);//destruindo o mutex	
	arrayFloatToFile(rspArr, defaultOutputPath);
	
	
	/*
	printf("\t\tIMPRIMINDO RESULTADOS\n\n");
	printf("+---------------+---------------+------------------+\n");
	printf("%c  PRIM. ELEM.\t%c NUM. DA DIAG.\t%c       SOMA\t   %c\n",'|','|','|','|');
    for(i = 0; i < matrix.diagNum; i++){
    	Coords c;
    	diagNumToCoord(matrix, i, &c);
        printf("%c(%3d,%3d)\t%c\t%4d\t%c\t%.7g\t   %c\n",'|',c.mpos, c.npos,'|', i,'|', rspArr.data[i].rsp,'|');
	}														   +						
	printf("+---------------+---------------+------------------+\n");
	
    */
    
    elapsedTime = difftime(tEnd, tStart);//Calculando tempo gasto
    //printf("[ TEMPO GASTO: %.2lf ms  |  THREADS REQUIRIDAS: %4d  |  THREADS USADAS: %4d ]\n", elapsedTime, numThreads, createdThreads);
    //printf("O processamento terminou antes da criacao de todas as threads: %s \n",  (numThreads != createdThreads) ? "Sim" : "Nao"   );
    
 	//Liberando memória utilizada
 	deleteMatrix(&matrix);
 	deleteArray(&rspArr);
	deleteArray(&tidArr);
	
	rsp->elapsedTime = elapsedTime;
	rsp->requiredThreads = numThreads;
	rsp->createdTheads = createdThreads;
	rsp->m = auxm;
	rsp->n = auxn;
}
/*
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
*/

int main(){
	unsigned int auxm, auxn, numThreads, threadCount;
	unsigned short register int i;
	int loops = 150;
	double med =0, medUsedThrd=0, medCreatedThrd=0;
	DataCollector rsp;
	
	FILE * fl1 = fopen("med.csv", "w");
	FILE * fl2 = fopen("thrd.csv", "w");

	auxm = 500;
	auxn = 500;
	numThreads = default_NumThreads;
	
	//for(threadCount = 1; threadCount < 4096; threadCount *= 2){
	for(threadCount = 1; threadCount < 65; threadCount *= 2){
		for(i = 1; i < loops; i++){
			printf("| %03d |\n",i);
			exec(threadCount, auxm, auxn, &rsp);
			//fprintf(fl2,"TEMPO;%d;M;%d;N;%d;REQ_THRD;%d;USD_THRD;%s\n",dotToCommaDouble(rsp.elapsedTime),rsp.m, rsp.n, rsp.requiredThreads, rsp.usedThreads);
			fprintf(fl2,"MxN;%dx%d;TIME;%s;REQ_T;%d;CREA_T;%d;USED_T;%d\n",rsp.m,rsp.n,dotToCommaDouble(rsp.elapsedTime), rsp.requiredThreads, rsp.createdTheads, rsp.usedThreads);
			med += rsp.elapsedTime;
			medUsedThrd = (double) rsp.usedThreads + medUsedThrd;
			medCreatedThrd = (double) rsp.createdTheads + medCreatedThrd;
	   }
		
		med = med/ loops;
		medUsedThrd = medUsedThrd/ loops;
		medCreatedThrd = medCreatedThrd / loops;
		printf("\n----------------------------------------------------\n");
		printf("[ TEMPO MEDIO: %s ms | THREADS: %03d | CREATED_T %s USED_T %s]", dotToCommaDouble(med), threadCount, dotToCommaDouble(medCreatedThrd), dotToCommaDouble(medUsedThrd));
		printf("\n----------------------------------------------------\n");
		
		fprintf(fl1,"THREADS;%d;TEMPO;%s;LOOPS;%d;AVG_THRD_C;%s;AVG_THRD_U;%s\n",threadCount, dotToCommaDouble(med),loops,dotToCommaDouble(medCreatedThrd),dotToCommaDouble(medUsedThrd) );
		med = 0;
		medUsedThrd = 0;
		medCreatedThrd = 0;
		
	}
	return 0;
}

