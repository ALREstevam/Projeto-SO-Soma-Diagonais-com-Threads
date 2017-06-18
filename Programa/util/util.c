#include <stdio.h>
#include <string.h>
#include <time.h>
#include "../datadefine.h"
#include "../file/fileMngr.h"
#include "../dataStructures/array/arrayMngr.h"
#include "../dataStructures/matrix/matrixMngr.h"
#include <pthread.h>


//Recebe uma string e substitui um caractere por outro
void strsubstchar(char * source, char find, char replace){
	int i;
	for(i = 0; source[i] != '\0'; i++){
		if(source[i] == find){
			source[i] = replace;
		}
	}
}

//Recebe um float e retorna o n�mero como uma string trocando a v�rgula por ponto (�til para gravar dados em um arquivo csv)
char * dotToCommaFloat(float num){
	int i, part = (int)num, size;
	
	for(i = 0; part != 0; i++){
		part /= 10;
	}
	
	size = 1 + 5 + i;
	char * str  = (char*) malloc(size * sizeof(char));
	
	sprintf(str, "%.5f", num);
	
	for(i = 0; i < size; i++){
		if(str[i] == '.'){
			str[i] = ',';
		}
	}
	
	return str;
}

//Recebe um double e retorna o n�mero como uma string trocando a v�rgula por ponto (�til para gravar dados em um arquivo csv)
char * dotToCommaDouble(double num){
	int i, part = (int)num, size;
	
	for(i = 0; part != 0; i++){
		part /= 10;
	}
	
	size = 1 + 10 + i;
	char * str  = (char*) malloc(size * sizeof(char));
	
	sprintf(str, "%.10lf", num);
	
	for(i = 0; i < size; i++){
		if(str[i] == '.'){
			str[i] = ',';
		}
	}
	
	return str;
}


//Fun��o que calcula a diferen�a de tempo entre dois hor�rios
double timediff(clock_t t1, clock_t t2){
	if(t1 > t2){
		return((double)(t1 - t2)) / (CLOCKS_PER_SEC * 1000);
	}else{
		return((double)(t2 - t1)) / (CLOCKS_PER_SEC * 1000);
	}
}

//Imprime uma mensagem de pausa na tela 
void pauseMsg(){
	printf("\nPressione enter para continuar...\n");
	getchar();
}

void putDefaultTitle(char * title, int h){
	char ch;
	if(h < 3)
		ch = '-';
	else
		ch = '#';
	int i;
	puts("\n");
	for(i = 0; i < h*10; i++){
		putchar(ch);
	}
	printf(" [  %s  ]  ", title);
	for(i = 0; i < h*10; i++){
		putchar(ch);
	}
	printf("\n\n");
}

//Gerencia a entrada de dados do usu�rio e informa quando sa�da foi requerida
bool inputFromUser(Input *rsp){

	putDefaultTitle("ENTRADA DE DADOS", 3);
	printf("Numero de threads:  ");
	fscanf(stdin,"%d", &rsp->numThreads);
	printf("Matriz (m linhas):  ");
	fscanf(stdin, "\n%d", &rsp->matrixM);
	printf("Matriz (n colunas): ");
	fscanf(stdin, "\n%d", &rsp->matrixN);
	getchar();
	
	putDefaultTitle("Voce escolheu", 1);
	
	printf("Processar uma matriz: \t[%d x %d]\n", rsp->matrixM, rsp->matrixN);
	printf("Usando:\t\t\t%d threads\n", rsp->numThreads);

	
	pauseMsg();

	if(rsp->numThreads <= 0 || rsp->matrixM <= 0 || rsp->matrixN <= 0){
		return false;
	}
	return true;
	
}

//Auxiliar para tabela
void tblHSep(){
	printf("\t+---------------+---------------+------------------+------------------+------------------+\n");
}

//Imprime uma tabela com os resultados da soma
void OutputSumToUser(MatrixDescriber *matrix, ArrayDescriber *rspArr){
	register int i;
	char vertSepChar = '|';
	
	putDefaultTitle("IMPRIMINDO RESULTADOS", 2);
	tblHSep();
	printf("\t%c COORDENADAS DO%c NUMERO DA\t%c  RESULTADO DA\t   %c    THREAD        %c  SOMAS FEITAS    %c\n",vertSepChar,vertSepChar,vertSepChar,vertSepChar,vertSepChar,vertSepChar);
    printf("\t%c PRIMEIRO ELEM.%c DIAGONAL \t%c       SOMA\t   %c  RESPONSAVEL     %c   NA DIAGONAL    %c\n",vertSepChar,vertSepChar,vertSepChar,vertSepChar,vertSepChar,vertSepChar);
	tblHSep();
	for(i = 0; i < matrix->diagNum; i++){
    	Coords c;
    	diagNumToCoord(*matrix, i, &c);
        printf("\t%c  (%4d,%4d)  %c     %5d     %c %10.5g  \t   %c    %11lu   %c    %9d     %c",vertSepChar,c.mpos, c.npos,vertSepChar, i,vertSepChar, rspArr->data[i].rspi.rsp,vertSepChar, (unsigned long)rspArr->data[i].rspi.tid, vertSepChar, rspArr->data[i].rspi.countDiagElem, vertSepChar);
	
		puts("");
	}					
	tblHSep();
}

//Fun��o que gera um gr�fico com a execu��o feita por cada thread
void printThreadWork(ArrayDescriber rspArr, ArrayDescriber tidArr, MatrixDescriber mx, unsigned int numt){
	register int i, j, totSum;
	
	//Vetor auxiliar
	ArrayDescriber twork;
	createArray(&twork, numt);
	
	//Vetor auxiliar
	ArrayDescriber tdiags;
	createArray(&tdiags, numt);
	
	//Limpando vetores auxiliares j� que ser�o usados como contadores
	cleanArray(twork);
	cleanArray(tdiags);
	
	totSum = mx.m * mx.n;
	
	for(i = 0; i < mx.diagNum; i++){//Percorrer vetor de resposta
		for(j = 0; j < numt; j++){//Percorrer vetor de threads
			if(pthread_equal(rspArr.data[i].rspi.tid, tidArr.data[j].tid)){
				twork.data[j].value += rspArr.data[i].rspi.countDiagElem;  //Soma da quantidade de somas
				tdiags.data[j].value ++;//Soma das diagonais processadas
			}
		}
	}
	
	for(i = 0; i < numt; i++){
		printf("THREAD [%3d]|", i);
		for(j = 0; j < (twork.data[i].value *80 / totSum); j++){
			putchar('*');
		}
		printf("   [ %d somas ]",twork.data[i].value);
		printf(" [ %d diagonais ]\n",tdiags.data[i].value);
	}
	
	deleteArray(&twork);
	deleteArray(&tidArr);
}


