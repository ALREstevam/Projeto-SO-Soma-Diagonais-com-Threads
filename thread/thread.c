#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>
#include "thread.h"
#include "../util/util.h"
#include "../datadefine.h"
#include "../dataStructures/array/arrayMngr.h"
#include "../dataStructures/matrix/matrixMngr.h"


//FUN��O PARA SOMA USANDO THREAD
/**
 * ENTRADA: essa fun��o recebe um struct de argumento contendo
 * 	-Um descritor da matriz a ser feito o c�lculo
 * 	-Um mutex
 * 	-Um ponteiro para vari�vel/regi�o cr�tica para controlar qual diagonal processar
 * 
 * SA�DA: essa fun��o retorna um unsigned int contendo o n�mero de somas feitas pela thread
 * 	-Somas feitas
 * 
 * 
 * Funcionamento:
 * 	Cada thread ir� entrar na fila para ter acesso � regi�o cr�tica dando down no mutex
 * 	ao entrar na regi�o cr�tica a thread far� uma c�pia da vari�vel que indica qual a pr�xima thread a 
 *	processar, como a thread processar� esta diagonal, soma um ao valor na regi�o cr�tica para a 
 *  pr�xima thread cacular a pr�xima diagonal que n�o foi processada ou que n�o est� sendo processada
 * 	por nenhuma thread.
 * 
 * 	Ao obter o n�mero da diagonal a ser processada, a thread ir� us�-lo numa fun��o que far� a convers�o
 * deste valor para as coordenadas do primeiro elemento dessa diagonal na matriz de entrada
 * ent�o enquanto o pr�ximo valor fizer parte da matriz, a thread ir�, sucessivamente somar os valores
 * de cada diagonal, salvando o resultado na posi��o vet[<n�mero da thread processada>]
 */

void * threadSumFunc_meth1(void * args){
	ThreadArgsInfo_m1 * tinfo = (ThreadArgsInfo_m1*) args;//Convertendo argumentos para argumentos de thread
	unsigned short int diagProcess;//guardar n�mero da diagonal atual
	Coords crds;//coordenadas (auxiliar)
	unsigned int * contProcess = (unsigned int *) malloc(sizeof(unsigned int));//Alocando valor de retorno
	
	*(contProcess) = 0;
	float sum, rsp;//soma, auxiliar
	
	//PEGAR UMA DIAGONAL PARA PROCESSAR
	while(1){
		
		///ACESSO � REGI�O CR�TICA
		pthread_mutex_lock(tinfo->lock);//down no mutex /*Acessando a regi�o cr�tica*/
		diagProcess = (*(tinfo->contDiag))++;//pegando o n�mero da diagonal a ser processada e somando 1
		pthread_mutex_unlock(tinfo->lock);//up no mutex
		///FIM DO ACESSO � REGI�O CR�TICA
		
		
		if(diagProcess >= tinfo->mx->diagNum)//Se a diagonal lida n�o pertencer � matriz
			break;//para terminar a thread
		
		//PEGAR PRIMEIRO ELEMENTO PARA INICIAR PROCESSAMENTO
		
		diagNumToCoord(*(tinfo->mx), diagProcess, &crds);
		getElement(*(tinfo->mx), crds, &sum);

		(*(contProcess))++;
		//PERCORRENDO ELEMENTOS DA DIAGONAL
		while(getNextElemPos(*(tinfo->mx), &crds)){//enquanto existir um pr�ximo elemento na diagonal
			getElement(*(tinfo->mx), crds, &rsp);//acessando elemento
			sum += rsp;//adicionando elemento na soma
			(*(contProcess))++;
		}
		tinfo->rspArr->data[diagProcess].rsp = sum;//guardando soma da diagonal processada
	}
	//printf("<%hu>\n", *contProcess);
	pthread_exit(contProcess);//terminando a thread
    return NULL;
}
////////////////////////////////////////////////////////////////////////////////


void * threadSumFunc_meth2(void * args){
	register int sumCount = 0, elementCount = 0;
	unsigned int * contProcess = (unsigned int *) malloc(sizeof(unsigned int));//Alocando valor de retorno
    ThreadArgsInfo_m2 *targs = (ThreadArgsInfo_m2*)args;//Convertendo os argumentos da thread
    
	MatrixDescriber mxa = *(targs->mx);//Colocando em uma vari�vel para deixar mais curto
    unsigned int jmp;//Tamanho do pulo
    int numThreads = targs->totThreads;//Quantidade de threads
    int numDiag = mxa.diagNum;//Quantidade de diagonais
    Coords coordrsp;
	
    float sum, rsp;

    for(jmp = targs->threadNum; jmp <= numDiag; (jmp+=numThreads)){//Cada thread sempre processar� diagonais alternadas com o mesmo tamanho
        printf(">%d \n", targs->threadNum);
        
		if(!diagNumToCoord(mxa, jmp, &coordrsp)){//convertendo n�mero da diagonal para o primeiro elemento
			getElement(mxa, coordrsp, &sum);
			continue;
			printf("#%d \n", targs->threadNum);
		}
        
        while(getNextElemPos(mxa, &coordrsp)){//enquanto existir um pr�ximo elemento na diagonal
            getElement(mxa, coordrsp, &rsp);//acessando elemento
			sum += rsp;//adicionando elemento na soma
			printf("*%d \n", targs->threadNum);
        }

        targs->rspArr->data[jmp].rsp = sum;//gravando resultado na matriz de resultado
		sumCount++;
    }
    *(contProcess) = sumCount;
    pthread_exit(contProcess);//terminando a thread
    return NULL;	
}

