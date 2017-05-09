
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

    ThreadArgsInfo *targs = (ThreadArgsInfo*)args;//Convertendo os argumentos da thread
    
    printf("THREAD %d INICIANDO...\n", targs->threadNum);
    
	MatrixDescriber mxa = *(targs->mx);//Colocando em uma variável para deixar mais curto
    unsigned int jmp;//Tamanho do pulo
    int numThreads = targs->totThreads;//Quantidade de threads
    int numDiag = mxa.diagNum;//Quantidade de diagonais
    Coords coordrsp;
	
    //deleteArray(targs->rspArr);
    //createArray(targs->rspArr, (unsigned int)(targs->mxa->diagNum / targs->threadNum) + 1);

    float sum, rsp;

    for(jmp = targs->threadNum; jmp <= numDiag; (jmp+=numThreads)){//Cada thread sempre processará diagonais alternadas com o mesmo tamanho
        digaNumToCoord(mxa, jmp, &coordrsp);//convertendo número da diagonal para o primeiro elemento
        //printf("DIAGNUMTOCOORD %d = (%d,%d) \n", jmp, coordrsp.mpos, coordrsp.npos);
        
        //Coords crdaux = coordrsp;

        getElement(mxa, coordrsp, &rsp);//Acessando primeiro elemento
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
        //printf("T%d : [DG: %.2d, \tSM: %.2f, \tINCRD: (%d, %d)]\n", targs->threadNum, jmp, sum, crdaux.mpos, crdaux.npos);

    }
    pthread_exit(NULL);//terminando a thread
    return NULL;
}