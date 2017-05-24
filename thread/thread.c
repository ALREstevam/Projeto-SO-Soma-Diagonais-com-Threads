#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>

#include "thread.h"
#include "../util/util.h"
#include "../datadefine.h"
#include "../dataStructures/array/arrayMngr.h"
#include "../dataStructures/matrix/matrixMngr.h"

void * threadSumFunc1(void * args){
	ThreadArgsInfo1 * tinfo = (ThreadArgsInfo1*) args;//Convertendo argumentos para argumentos de thread
	int diagProcess;//guardar número da diagonal atual
	float sum, rsp;//soma, auxiliar
	
	//printf("uma thread iniciando!\n");
	//PEGAR UMA DIAGONAL PARA PROCESSAR
	while(1){	
		pthread_mutex_lock(tinfo->lock);//down no mutex
		 /*Acessando a região crítica*/
			diagProcess = *(tinfo->contDiag);//pegando o número da diagonal a ser processada
			*(tinfo->contDiag) += 1;//incrementando a diagonal
		pthread_mutex_unlock(tinfo->lock);//up no mutex
		
		if(diagProcess >= tinfo->mx->diagNum){//Se a diagonal lida não pertencer à matriz
			break;//para terminar a thread
		}
		
		//PEGAR PRIMEIRO ELEMENTO PARA INICIAR PROCESSAMENTO
		Coords crds;//coordenadas
		/*if(!diagNumToCoord(*(tinfo->mx), diagProcess, &crds)){//converter o número da diagonal para a coordenada do primeiro elemento
			printf("\n!DIAGTOCOORD!\n");
			continue;
		}
		
		if(!getElement(*(tinfo->mx), crds, &rsp)){//acessar o primeiro elemento
			printf("\n!GETELEMENT!\n");
			continue;
		}*/
		
		diagNumToCoord(*(tinfo->mx), diagProcess, &crds);
		getElement(*(tinfo->mx), crds, &rsp);
		
		sum = rsp;//definir soma como primeiro
		
		
		
		
		//PERCORRENDO ELEMENTOS DA DIAGONAL
		while(getNextElementPositionMdiags(*(tinfo->mx), &crds) == true){//enquanto existir um próximo elemento na diagonal
				if(getElement(*(tinfo->mx), crds, &rsp) == true){//acessando elemento
	                sum += rsp;//adicionando elemento na soma
				}
		}
	//	printf("DIAG[%.3d]\t\tPOS[%.3d,%.3d]\tSUM[%.2f]\n", diagProcess,crds.mpos, crds.npos, sum);
	
		tinfo->rspArr->data[diagProcess].rsp = sum;//guardando soma da diagonal processada
	}
	
//	printf("thread terminando\n");
	
	pthread_exit(NULL);//terminando a thread
    return NULL;
}