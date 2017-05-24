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
generateExecutionData  se ativado o programa ir� gerar e armazenar em arquivo dados sobre a execu��o
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

double exec(int nt){	
	time_t tStart = 0, tEnd = 0;//Declarando rel�gios
	pthread_mutex_t lock;//Declarando mutex
	pthread_mutex_init(&lock, NULL);//Iniciando mutex
	unsigned int diagNum = 0;//Definindo �rea cr�tica
	int auxm, auxn, numThreads;//Auxiliares
	double elapsedTime;//Armazenamento do tempo gasto
	
	
	//Se requerir entrada do usu�rio estiver ativado
	if(getInputFromUser){
		printf("Digite os valores:\n<linhas> <colunas> <qtd. de threads>\n");
		
		scanf("%d %d %d",&auxm, &auxn, &numThreads);
		getchar();	
	}else{//Defini��o dos valores default
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
	
	tStart = clock();//Disparando rel�gio
	for(i = 0; i < numThreads; i++){
		pthread_create(&(tidArr.data[i].tid), NULL, threadSumFunc1, &targs);
	}

	for(i = 0; i < numThreads; i++){
		pthread_join(tidArr.data[i].tid, NULL);
	}
	tEnd = clock();//Parando rel�gio
	pthread_mutex_destroy(&lock);//destruindo o mutex
	
	arrayFloatToFile(rspArr, defaultOutputPath);
	
	printMatrix(matrix);
	
	printf("\t\tIMPRIMINDO RESULTADOS\n\n");
	printf("%c  PRIM. ELEM.\t%c NUM. DA DIAG.\t%c       SOMA\t   %c\n",179,179,179,179);
    for(i = 0; i < matrix.diagNum; i++){
    	Coords c;
    	diagNumToCoord(matrix, i, &c);
        printf("%c(%3d,%3d)\t%c\t%4d\t%c\t%.7g\t   %c\n",179,c.mpos, c.npos,179, i,179, rspArr.data[i].rsp,179);
	}
    
 	//Liberando mem�ria utilizada
 	deleteMatrix(&matrix);
 	
 	deleteArray(&rspArr);
	deleteArray(&tidArr);

	elapsedTime = difftime(tEnd, tStart);//Calculando tempo gasto
	printf("\n[TEMPO GASTO: %.2lf s]\n", elapsedTime);
	
	/*FILE *fl = fopen("data.csv","a+");
	fprintf(fl, "%d; %f\n", numThreads, elapsedTime);*/
	return elapsedTime;
}

int nomain(){
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

int anomain(){
	int tcount, loopcount, maxt = 4000, maxloop = 40;
	double med = 0;
	FILE *fl = fopen("data1.csv", "w");
	
	for(tcount = 1; tcount < maxt; tcount *= 2){
		for(loopcount = 0; loopcount < maxloop; loopcount++){
			med += exec(tcount);
		}
		printf("%d\n",tcount);
		fprintf(fl, "%d; %lf\n",tcount, (med/loopcount));
		med = 0;
	}
	return 0;
}

int main(){
	exec(5);
	
	return 0;
}
