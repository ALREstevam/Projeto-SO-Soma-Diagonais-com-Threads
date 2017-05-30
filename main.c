/**
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
#include "thread/callThread.h"




int main(){
	
	Input in = inputFromUser();
	DataCollector dt;
	time_t tstart, tend;
	double timeTaken;
	
	tstart = clock();
	//
		//execMethod_b(in, &dt);
		execMethod_a(in, &dt);
	//
	tend = clock();
	timeTaken = difftime(tend, tstart);
	
	printf("Tempo: %lf\n", timeTaken);
	
	
	
	
	
	
	
	
	
	/*unsigned int auxm, auxn, numThreads, threadCount;
	unsigned short register int i;
	int loops = 2;
	double med =0, medUsedThrd=0, medCreatedThrd=0;
	DataCollector rsp;
	
	FILE * fl1 = fopen("med.csv", "w");
	FILE * fl2 = fopen("thrd.csv", "w");

	auxm = 50;
	auxn = 50;
	numThreads = default_NumThreads;
	
	//for(threadCount = 1; threadCount < 4096; threadCount *= 2){
	for(threadCount = 10; threadCount < 11; threadCount *= 2){
		for(i = 1; i < loops; i++){
			
			exec(threadCount, auxm, auxn, &rsp);
			//fprintf(fl2,"TEMPO;%d;M;%d;N;%d;REQ_THRD;%d;USD_THRD;%s\n",dotToCommaDouble(rsp.elapsedTime),rsp.m, rsp.n, rsp.requiredThreads, rsp.usedThreads);
			fprintf(fl2,"MxN;%dx%d;TIME;%s;REQ_T;%d;CREA_T;%d;USED_T;%d\n",rsp.m,rsp.n,dotToCommaDouble(rsp.elapsedTime), rsp.requiredThreads, rsp.createdTheads, rsp.usedThreads);
			med += rsp.elapsedTime;
			medUsedThrd = (double) rsp.usedThreads + medUsedThrd;
			medCreatedThrd = (double) rsp.createdTheads + medCreatedThrd;
			printf("| %03d |\n",i);
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
		
	}*/
	return 0;
}

