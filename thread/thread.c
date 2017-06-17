#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>
#include "thread.h"
#include "../Util/util.h"
#include "../datadefine.h"
#include "../dataStructures/Matrix/matrixMngr.h"
#include "../dataStructures/Array/arrayMngr.h"


//FUN��O PARA SOMA USANDO THREAD

void * threadSumFunc_meth1(void * args){
	ThreadArgsInfo_m1 * tinfo = (ThreadArgsInfo_m1*) args;//Convertendo argumentos para argumentos de thread
	unsigned short int diagProcess;//guardar n�mero da diagonal atual
	Coords crds;//coordenadas (auxiliar)
	unsigned int * contProcess = (unsigned int *) malloc(sizeof(unsigned int));//Alocando valor de retorno
	*contProcess = 0;
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
	pthread_exit(contProcess);//terminando a thread
    return NULL;
}


//#############################################################################################


void * threadSumFunc_meth2(void * args){
	unsigned int * contProcess = (unsigned int *) malloc(sizeof(unsigned int));//Alocando valor de retorno
    *contProcess = 0;
	ThreadArgsInfo_m2 *targs = (ThreadArgsInfo_m2*)args;//Convertendo os argumentos da thread
    unsigned int jmp;//Tamanho do pulo

    Coords coordrsp;
    float sum, rsp;

    for(jmp = targs->threadNum; jmp <= targs->mx->diagNum; (jmp += targs->totThreads)){//Cada thread sempre processar� diagonais alternadas com o mesmo tamanho
   	   
		if(!diagNumToCoord(*targs->mx, jmp, &coordrsp)){//convertendo n�mero da diagonal para o primeiro elemento
			continue;
		}
		getElement(*targs->mx, coordrsp, &sum);
		*contProcess++;
        while(getNextElemPos(*targs->mx, &coordrsp)){//enquanto existir um pr�ximo elemento na diagonal
            getElement(*targs->mx, coordrsp, &rsp);//acessando elemento
			sum += rsp;//adicionando elemento na soma
			*(contProcess)++;
        }

        targs->rspArr->data[jmp].rsp = sum;//gravando resultado na matriz de resultado
    }
    pthread_exit(contProcess);//terminando a thread
    return NULL;	
}