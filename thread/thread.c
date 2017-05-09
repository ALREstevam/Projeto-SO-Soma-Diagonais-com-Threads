#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>

#include "thread.h"
#include "../datadefine.h"
#include "../dataStructures/array/arrayMngr.h"
#include "../dataStructures/matrix/matrixMngr.h"


//Thread de soma
void * threadSumFunc(void * args){
	int sumCount = 0;

    ThreadArgsInfo *targs = (ThreadArgsInfo*)args;//Convertendo os argumentos da thread
    
    if(printInfoProcess){printf("[Thread %d iniciando]\n", targs->threadNum);}
    
	MatrixDescriber mxa = *(targs->mx);//Colocando em uma variável para deixar mais curto
    unsigned int jmp;//Tamanho do pulo
    int numThreads = targs->totThreads;//Quantidade de threads
    int numDiag = mxa.diagNum;//Quantidade de diagonais
    Coords coordrsp;
	
    float sum, rsp;

    for(jmp = targs->threadNum; jmp <= numDiag; (jmp+=numThreads)){//Cada thread sempre processará diagonais alternadas com o mesmo tamanho
        
		if(!digaNumToCoord(mxa, jmp, &coordrsp)){//convertendo número da diagonal para o primeiro elemento
			continue;
		}
        //printf("DIAGNUMTOCOORD %d = (%d,%d) \n", jmp, coordrsp.mpos, coordrsp.npos);


        if(!getElement(mxa, coordrsp, &rsp)){//Acessando primeiro elemento
			continue;
		}
        sum = rsp;//colocando na soma


        while(getNextElementPositionMdiags(mxa, &coordrsp) == true){//enquanto existir um próximo elemento na diagonal
            if(getElement(mxa, coordrsp, &rsp) == true){//acessando elemento
                sum += rsp;//adicionando elemento na soma
            }
            else{
                break;
            }
        }

        targs->rspArr->data[jmp].dt.rsp = sum;//gravando resultado na matriz de resultado
        if(printInfoProcess){printf("T%d : [DG: %.2d, \tSM: %.2f]\n", targs->threadNum, jmp, sum);}
		sumCount++;
    }
    
    if(printInfoProcess){printf("[Thread %d terminou, fez %d somas]\n", targs->threadNum, sumCount);}
    pthread_exit(NULL);//terminando a thread
    return NULL;
}