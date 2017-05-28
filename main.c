/*
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

double exec(unsigned int thrdqtd, unsigned int matrixM, unsigned int matrixN){	
	

	
	//DECLARA��O DE VARI�VEIS
	time_t tStart = 0, tEnd = 0;//Declarando rel�gios
	pthread_mutex_t lock;//Declarando mutex
	pthread_mutex_init(&lock, NULL);//Iniciando mutex
	unsigned short int diagNum = 0;//Definindo �rea cr�tica
	int auxm, auxn;//Auxiliares
	unsigned short int numThreads;
	double elapsedTime;//Armazenamento do tempo gasto
	register int i;
	
	auxm = matrixM;
	auxn = matrixN;
	numThreads = thrdqtd;
	
	tStart = clock();//Disparando rel�gio
	
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
	tEnd = clock();//Parando rel�gio
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
    
 	//Liberando mem�ria utilizada
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
	
	//Se requerir entrada do usu�rio estiver ativado
	if(getInputFromUser){
		printf("Digite os valores:\n<linhas> <colunas> <qtd. de threads>\n");
		scanf("%d %d %d",&auxm, &auxn, &numThreads);
		printf("\nMATRIX m x n: [%d,%d]\nTHREADS: %d\n\n",auxm,auxn, numThreads);	
		pause();
	}else{//Defini��o dos valores default
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

	//Se requerir entrada do usu�rio estiver ativado
	if(getInputFromUser){
		printf("Digite os valores:\n<linhas> <colunas> <qtd. de threads>\n");
		scanf("%d %d %d",&auxm, &auxn, &numThreads);
		printf("\nMATRIZ m x n: [%d,%d]\nTHREADS: %d\n\n",auxm,auxn, numThreads);
		getchar();
		pause();
	}else{//Defini��o dos valores default
		auxm = default_M;
		auxn = default_N;
		numThreads = default_NumThreads;
	}	
	
	exec(numThreads, auxm, auxn);
return 0;
}

