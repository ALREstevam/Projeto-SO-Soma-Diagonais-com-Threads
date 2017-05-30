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


//FUNÇÃO PARA SOMA USANDO THREAD
/**
 * ENTRADA: essa função recebe um struct de argumento contendo
 * 	-Um descritor da matriz a ser feito o cálculo
 * 	-Um mutex
 * 	-Um ponteiro para variável/região crítica para controlar qual diagonal processar
 * 
 * SAÍDA: essa função retorna um unsigned int contendo o número de somas feitas pela thread
 * 	-Somas feitas
 * 
 * 
 * Funcionamento:
 * 	Cada thread irá entrar na fila para ter acesso à região crítica dando down no mutex
 * 	ao entrar na região crítica a thread fará uma cópia da variável que indica qual a próxima thread a 
 *	processar, como a thread processará esta diagonal, soma um ao valor na região crítica para a 
 *  próxima thread cacular a próxima diagonal que não foi processada ou que não está sendo processada
 * 	por nenhuma thread.
 * 
 * 	Ao obter o número da diagonal a ser processada, a thread irá usá-lo numa função que fará a conversão
 * deste valor para as coordenadas do primeiro elemento dessa diagonal na matriz de entrada
 * então enquanto o próximo valor fizer parte da matriz, a thread irá, sucessivamente somar os valores
 * de cada diagonal, salvando o resultado na posição vet[<número da thread processada>]
 */

void * threadSumFunc_meth1(void * args){
	ThreadArgsInfo_m1 * tinfo = (ThreadArgsInfo_m1*) args;//Convertendo argumentos para argumentos de thread
	unsigned short int diagProcess;//guardar número da diagonal atual
	Coords crds;//coordenadas (auxiliar)
	unsigned int * contProcess = (unsigned int *) malloc(sizeof(unsigned int));//Alocando valor de retorno
	
	*(contProcess) = 0;
	float sum, rsp;//soma, auxiliar
	
	//PEGAR UMA DIAGONAL PARA PROCESSAR
	while(1){
		
		///ACESSO À REGIÃO CRÍTICA
		pthread_mutex_lock(tinfo->lock);//down no mutex /*Acessando a região crítica*/
		diagProcess = (*(tinfo->contDiag))++;//pegando o número da diagonal a ser processada e somando 1
		pthread_mutex_unlock(tinfo->lock);//up no mutex
		///FIM DO ACESSO À REGIÃO CRÍTICA
		
		
		if(diagProcess >= tinfo->mx->diagNum)//Se a diagonal lida não pertencer à matriz
			break;//para terminar a thread
		
		//PEGAR PRIMEIRO ELEMENTO PARA INICIAR PROCESSAMENTO
		
		diagNumToCoord(*(tinfo->mx), diagProcess, &crds);
		getElement(*(tinfo->mx), crds, &sum);

		(*(contProcess))++;
		//PERCORRENDO ELEMENTOS DA DIAGONAL
		while(getNextElemPos(*(tinfo->mx), &crds)){//enquanto existir um próximo elemento na diagonal
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
    
	MatrixDescriber mxa = *(targs->mx);//Colocando em uma variável para deixar mais curto
    unsigned int jmp;//Tamanho do pulo
    int numThreads = targs->totThreads;//Quantidade de threads
    int numDiag = mxa.diagNum;//Quantidade de diagonais
    Coords coordrsp;
	
    float sum, rsp;

    for(jmp = targs->threadNum; jmp <= numDiag; (jmp+=numThreads)){//Cada thread sempre processará diagonais alternadas com o mesmo tamanho
        printf(">%d \n", targs->threadNum);
        
		if(!diagNumToCoord(mxa, jmp, &coordrsp)){//convertendo número da diagonal para o primeiro elemento
			getElement(mxa, coordrsp, &sum);
			continue;
			printf("#%d \n", targs->threadNum);
		}
        
        while(getNextElemPos(mxa, &coordrsp)){//enquanto existir um próximo elemento na diagonal
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

