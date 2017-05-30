/**
Escrito por Andr� L. R. Estevam 		como trabalho para a disciplina de Sistemas
Operacionais (1� Semestre de 2017) da Faculdade de Tecnologia da Unicamp
-------------------------------------------------------------------------------
Este � um programa que l� n�meros com ponto flutuante a partir de um arquivo para
uma matriz m x n com m e n sendo inseridos pelo usu�rio, o programa usa de 1 a n
threads para processar a soma das diagonais principais armazenando o resultado em
um vetor, podendo ainda gerar dados sobre a execu��o do programa gravando em um
arquivo .csv que pode ser lido por algum software de panilha eletr�nica. 

DETALHES SOBRE O FUNCIONAMENTO:
-Configura��es: as constantes de configura��o est�o no arquivo "datadefine.h"

-Booleanos
getInputFromUser       se ativado o programa perguntar� ao usu�rio as dimens�es da matriz e a quantidade de threads a usar		
printInfoProcess 	   se ativado o programa ir� imprimir informa��es sobre o processamento
fillInputWithRandom	   se ativado o programa ir� preencher a entrada padr�o com valores aleat�rios
fillInputWithNum 	   se ativado o programa ir� preencher a entrada padr�o com um determinado valor

//Par�metros
float fillElement 	    elementos a gravar na entrada padr�o  		
int fileElementsAmount  quantidade de elementos a gravar na entrada padr�o
												

//Valores default
int default_M 		     Valor padr�o de linhas da matriz (caso entrada de dados pelo usu�rio seja desativada)	
int default_N 		     Valor padr�o de colunas da matriz (caso entrada de dados pelo usu�rio seja desativada)
int default_NumThreads 	 Quantidade padr�o de threads (caso entrada de dados pelo usu�rio seja desativada)


-Arquivos:
	Se os arquivos de entrada e sa�da n�o existirem, ser�o criados.
	Se o arquivo de entrada estiver vazio ou incompleto, os elementos da matriz sem valor
	correspondente ser�o preenchidos com 0;
	� poss�vel usar as configura��es para fazer o programa gerar o arquivo de entrada com
	n repeti��es de um valor definido ou valores rand�micos
	
-Threads:
Cada thread ir� acessar uma regi�o cr�tica que indica o n�mero da pr�xima diagonal a ser processada
copiar o valor da regi�o e incrementar seu valor.

A thread converte o n�mero da diagonal para a coordenada do primeiro elemento dessa diagonal, acessa
esse valor e soma sucessivamente os valores dessa diagonal. Ao finalizar o processamento a soma � 
armazenada num vetor, se a diagonal processada foi x, a soma � armazenada em vet[x].

O processo � repetido at� que a thread leia da regi�o cr�tica um n�mero de diagonal que n�o
pertence � matriz.

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

