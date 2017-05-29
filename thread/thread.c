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

void * threadSumFunc(void * args){
	ThreadArgsInfo * tinfo = (ThreadArgsInfo*) args;//Convertendo argumentos para argumentos de thread
	unsigned short int diagProcess;//guardar n�mero da diagonal atual
	unsigned int * contProcess = (unsigned int *) malloc(sizeof(unsigned int));
	*(contProcess) = 0;
	float sum, rsp;//soma, auxiliar
	//PEGAR UMA DIAGONAL PARA PROCESSAR
	while(1){	
		Coords crds;//coordenadas
		pthread_mutex_lock(tinfo->lock);//down no mutex /*Acessando a regi�o cr�tica*/
			diagProcess = (*(tinfo->contDiag))++;//pegando o n�mero da diagonal a ser processada
			//*(tinfo->contDiag) ++;//incrementando a diagonal
		pthread_mutex_unlock(tinfo->lock);//up no mutex
		
		if(diagProcess >= tinfo->mx->diagNum)//Se a diagonal lida n�o pertencer � matriz
			break;//para terminar a thread
		
		//PEGAR PRIMEIRO ELEMENTO PARA INICIAR PROCESSAMENTO
		
		diagNumToCoord(*(tinfo->mx), diagProcess, &crds);
		getElement(*(tinfo->mx), crds, &rsp);
		
		sum = rsp;//definir soma como primeiro
		(*(contProcess))++;
		//PERCORRENDO ELEMENTOS DA DIAGONAL
		while(getNextElementPositionMdiags(*(tinfo->mx), &crds)){//enquanto existir um pr�ximo elemento na diagonal
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