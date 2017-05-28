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
	//printf("[ THREAD %d ]<(  Thread iniciando  )\n", pthread_self());	
	ThreadArgsInfo * tinfo = (ThreadArgsInfo*) args;//Convertendo argumentos para argumentos de thread
	unsigned short int diagProcess;//guardar número da diagonal atual
	float sum, rsp;//soma, auxiliar
	//PEGAR UMA DIAGONAL PARA PROCESSAR
	while(1){	
		Coords crds;//coordenadas
		pthread_mutex_lock(tinfo->lock);//down no mutex /*Acessando a região crítica*/
			diagProcess = (*(tinfo->contDiag))++;//pegando o número da diagonal a ser processada
			//*(tinfo->contDiag) ++;//incrementando a diagonal
		pthread_mutex_unlock(tinfo->lock);//up no mutex
		
		if(diagProcess >= tinfo->mx->diagNum)//Se a diagonal lida não pertencer à matriz
			break;//para terminar a thread
		
		//PEGAR PRIMEIRO ELEMENTO PARA INICIAR PROCESSAMENTO
		
		diagNumToCoord(*(tinfo->mx), diagProcess, &crds);
		getElement(*(tinfo->mx), crds, &rsp);
		
		sum = rsp;//definir soma como primeiro
		
		//PERCORRENDO ELEMENTOS DA DIAGONAL
		while(getNextElementPositionMdiags(*(tinfo->mx), &crds)){//enquanto existir um próximo elemento na diagonal
			getElement(*(tinfo->mx), crds, &rsp);//acessando elemento
			sum += rsp;//adicionando elemento na soma
					//printf("[ THREAD %d ]<(  Fazendo uma soma  )\n", pthread_self());	
		}
		tinfo->rspArr->data[diagProcess].rsp = sum;//guardando soma da diagonal processada
		
	}	
	//printf("[ THREAD %d ]<(  Thread terminando  )\n", pthread_self());	
	pthread_exit(NULL);//terminando a thread
    return NULL;
}