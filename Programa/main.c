/**
Escrito por Andr� L. R. Estevam 		como trabalho para a disciplina de Sistemas
Operacionais (1� Semestre de 2017) da Faculdade de Tecnologia da Unicamp

#################################################################################
Este � um programa que l� n�meros com ponto flutuante a partir de um arquivo para
uma matriz (m x n) com m e n sendo inseridos pelo usu�rio, o programa usa de 1 a n
threads para processar a soma das diagonais principais armazenando o resultado em
arquivo e exibindo-o na tela, podendo ainda gerar dados sobre a execu��o do programa 
gravados em arquivo. 
#################################################################################
*/

//Incluindo bibliotecas padr�o
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <stdbool.h>
#include <time.h>
#include <strings.h>
#include <unistd.h>

//Incluindo bibliotecas criadas
#include "util/util.h"							//Biblioteca com fun��es de utilidades diversas
#include "datadefine.h"							//Defini��o de dados (vari�veis globais, defines e tipos de dados novos)
#include "dataStructures/array/arrayMngr.h"		//Biblioteca para gerenciar o tipo de vetor usado
#include "dataStructures/matrix/matrixMngr.h"	//Biblioteca para gerenciar o tipo de matriz usada
#include "thread/thread.h"						//Biblioteca contendo fun��es executadas por threads
#include "file/fileMngr.h"						//Bilioteca para definir gerenciamento dos arquivos usados


void repeatmethod(char * dataPath, Input in, char method, int inisize, int addmxfactor);
void exec(Input in, char method, bool printResult, bool printMx);


//////////////////// DEFAULT/CONFIGURATION VALUES ///////////////////////////
const bool generateDataMode 				= false; //<true: ativa modo de gera��o de dados|false: ativa modo de entrada de dados pelo usu�rio>

//Dimens�es padr�o da matriz
static const int default_M 					= 1000; 
static const int default_N 					= 1000;

//M�TODO UTILIZADO <a: m�todo a|b: m�todo b|outro: se generateDataMode ativado, ambos>
const char defaultMethod 					= 'c';

#define DEFAULT_INPUT_PATH "in.txt"
#define DEFAULT_OUTPUT_PATH_A "out_method_A.txt"
#define DEFAULT_OUTPUT_PATH_B "out_method_B.txt"
#define DEFAULT_GENERATED_DATA_PATH "data.csv"
///////////////////////////////////////////////////////////////////////////


/*==================================================================================
								MAIN
===================================================================================*/
int main(){	
	Input in;
	in.inputPath = DEFAULT_INPUT_PATH;
	
	if(generateDataMode){
		in.matrixM = default_M;
		in.matrixN = default_N;
		/*in.outputPath = DEFAULT_OUTPUT_PATH_A;
		repeatmethod(DEFAULT_GENERATED_DATA_PATH, in, 'a', 100, 200);*/
		in.outputPath = DEFAULT_OUTPUT_PATH_B;
		repeatmethod(DEFAULT_GENERATED_DATA_PATH, in, 'b', 100, 200);
		return 0;
	}else{
		while(inputFromUser(&in)){
			if(defaultMethod == 'a'){
				in.outputPath = DEFAULT_OUTPUT_PATH_A;
			}else{
				in.outputPath = DEFAULT_OUTPUT_PATH_B;
			}
			 exec(in, defaultMethod, true, (in.matrixN <= 20 ? true : false) );
			 printf("\n\n\n\n");
		}
		return 0;
	}
}

double execmethodB(Input in, bool printResult, bool printMx);
double execmethodA(Input in, bool printResult, bool printMx);
/*==================================================================================
					FUN��O PARA GERAR E SALVAR DADOS
===================================================================================*/
void repeatmethod(char * dataPath, Input in, char method, int inisize, int addmxfactor){
	register int threadCount, loopCount, szCount;
	int threadMax = 16, loopMax = 30, maxMxSz = 1500;
	
	fillFileWithValue(in.inputPath, maxMxSz*maxMxSz, 1.1);
	
	double elapsed;
	char * aux;
	
	FILE *fl = fopen(dataPath ,"a+");
	if(fl == NULL){
		fprintf(stderr, "Erro ao abrir arquivo\n");
		exit(-2);
	}
	
	fprintf(fl, "THREADS;TIME;M;N;LOOPS;metodo: %c\n", method);
	
	
	for(szCount = inisize; szCount <= maxMxSz; szCount += addmxfactor){
		in.matrixM = szCount;
		in.matrixN = szCount;
		
		for(threadCount = 1; threadCount <= threadMax; threadCount *= 2){
			elapsed = 0;
			for(loopCount = 0; loopCount < loopMax; loopCount++){
				in.numThreads = threadCount;
			    
			    switch(method)
				{
				case 'a':
					elapsed += execmethodA(in, false, false);	
					break;
				default:
					elapsed += execmethodB(in, false, false);	
					break;
				}
	
				printf("#%3d [ THREADS: %3d | method: %c] : ( %lf )\n", loopCount, threadCount, method, elapsed);
			}
			aux = dotToCommaDouble(elapsed/loopCount);
			fprintf(fl, "%d;%s;%d;%d;%d;*\n",threadCount, aux, in.matrixM, in.matrixN, loopCount);
			printf("========================================\n");	
			printf("###[%d | %c]::[ %lf ] MATRIZ(%d x %d)\n", threadCount, method, elapsed/(loopCount+1), in.matrixM, in.matrixN);
			printf("========================================\n\n\a");	
			free(aux);
		}
	}
	fclose(fl);
}


void exec(Input in, char method, bool printResult, bool printMx){
	switch(method)
	{
	case 'a':
		putDefaultTitle("METODO A", 4);
		printf("METODO [A] | Tempo gasto: %.3lf\n", execmethodA(in, printResult, printMx));
		break;
	case 'b':
		putDefaultTitle("METODO B", 4);
		printf("METODO [B] | Tempo gasto: %.3lf\n", execmethodB(in, printResult, printMx));
		break;
	default:
		in.outputPath = DEFAULT_OUTPUT_PATH_A;
		putDefaultTitle("METODO A", 4);
		printf("METODO [A] | Tempo gasto: %.3lf\n", execmethodA(in, printResult, printMx));
		in.outputPath = DEFAULT_OUTPUT_PATH_B;
		putDefaultTitle("METODO B", 4);
		printf("METODO [B] | Tempo gasto: %.3lf\n", execmethodB(in, printResult, printMx));
		break;
	}
}

/*==================================================================================
								M�TODO A
===================================================================================*/
double execmethodA(Input in, bool printResult, bool printMx){	
	//DECLARA��O DE VARI�VEIS
	time_t tStart = 0, tEnd = 0;//Declarando rel�gios
	
	tStart = clock();//DISPARANDO REL�GIO
	
	pthread_mutex_t lock;//Declarando mutex
	pthread_mutex_init(&lock, NULL);//Iniciando mutex
	double elapsedTime;//Armazenamento do tempo gasto
	register int i;
	
	unsigned short int contDiag = 0;

	//Definindo vetores e matrizes
    MatrixDescriber matrix;
    ArrayDescriber rspArr;
    ArrayDescriber tidArr;

	//Criando vetores e matrizes
	createMatrix(&matrix, in.matrixM, in.matrixN);
    createArray(&rspArr, matrix.diagNum);
	createArray(&tidArr, in.numThreads);
	rspArr.top = matrix.diagNum-1;
	
	//Lendo arquivo de entrada
    if(!fileToMatrix(matrix, in.inputPath)){
		printf("ATENCAO!\nO arquivo de entrada era muito pequeno,\nposicoes vazias foram preenchidas com: -1\n");
	}
	
	if(printMx){
		printMatrix(matrix);
	}
	
	ThreadArgsInfo_A targs;
	targs.mx = &matrix;
	targs.rspArr = &rspArr;
	targs.lock = &lock;
	targs.contDiag = &contDiag;

	
	for(i = 0; i < in.numThreads; i++){
		pthread_create(&(tidArr.data[i].tid), NULL, threadSumFunc_A, &targs);
	}
	for(i = 0; i < in.numThreads; i++){
		pthread_join(tidArr.data[i].tid, NULL);
	}
	
	pthread_mutex_destroy(&lock);//destruindo o mutex
	
	//arrayFloatToFile(rspArr, in.outputPath);
	arrayFloatToFileWithBuffer(rspArr, in.outputPath);
	
	if(printResult){
		printf("\n");
		OutputSumToUser(&matrix, &rspArr);
		printf("\n");
		printThreadWork(rspArr, tidArr, matrix, in.numThreads);
		printf("\n");
	}
	
	
	
 	//Liberando mem�ria utilizada
 	deleteMatrix(&matrix);
 	deleteArray(&rspArr);
	deleteArray(&tidArr);
	
	tEnd = clock();//PARANDO REL�GIO
	elapsedTime = timediff(tStart, tEnd);
	return elapsedTime;
}
/*==================================================================================
								M�TODO B
===================================================================================*/
double execmethodB(Input in, bool printResult, bool printMx){
	time_t tStart, tEnd;
	
	tStart = clock();//DISPARANDO REL�GIO
	register int i;

	//Definindo vetores e matrizes
    MatrixDescriber matrix;
    ArrayDescriber rspArr;
    ArrayDescriber tidArr;

	//Criando vetores e matrizes
	createMatrix(&matrix, in.matrixM, in.matrixN);
    createArray(&rspArr, matrix.diagNum);
	createArray(&tidArr, in.numThreads);
	rspArr.top = matrix.diagNum-1;
	
	//Lendo arquivo de entrada
    if(!fileToMatrix(matrix, in.inputPath)){
		printf("ATENCAO!\nO arquivo de entrada era muito pequeno,\n posicoes vazias foram preenchidas com algum numero\n");
	}
	
	if(printMx){
		printMatrix(matrix);
	}
	
	//Alocando na mem�ria espa�o para o argumento das threads
	ThreadArgsInfo_B * tinfoptr = (ThreadArgsInfo_B*) malloc(in.numThreads * sizeof(ThreadArgsInfo_B));
	if(tinfoptr == NULL){
		fprintf(stderr,"Erro ao alocar argumentos de threads\n");
		exit(-1);
	}

	//Para cada thread
    for(i = 0; i < in.numThreads; i++){

		//Inicializando os argumentos das threads
		tinfoptr[i].threadNum = (unsigned short int)i;
        tinfoptr[i].mx = &matrix;
    	tinfoptr[i].rspArr = &rspArr;
    	tinfoptr[i].totThreads = (unsigned int)in.numThreads;
        
        //Criando thread
		pthread_create(&(tidArr.data[i].tid), NULL, threadSumFunc_B, &tinfoptr[i]);
    }
    
    for(i = 0; i < in.numThreads; i++){
		pthread_join(tidArr.data[i].tid, NULL);
	}
	
	if(printResult){
		printf("\n");
		OutputSumToUser(&matrix, &rspArr);
		printf("\n");
		printThreadWork(rspArr, tidArr, matrix, in.numThreads);
		printf("\n");
	}
    

    //arrayFloatToFile(rspArr, in.outputPath);
    arrayFloatToFileWithBuffer(rspArr, in.outputPath);
    
 	//Liberando mem�ria utilizada
 	deleteMatrix(&matrix);
 	deleteArray(&rspArr);
	deleteArray(&tidArr);
 	free(tinfoptr);

    tEnd = clock();//PARANDO REL�GIO
    return timediff(tStart, tEnd);
}



