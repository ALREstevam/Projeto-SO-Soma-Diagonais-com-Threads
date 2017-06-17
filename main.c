/**
Escrito por André L. R. Estevam 		como trabalho para a disciplina de Sistemas
Operacionais (1º Semestre de 2017) da Faculdade de Tecnologia da Unicamp
-------------------------------------------------------------------------------
Este é um programa que lê números com ponto flutuante a partir de um arquivo para
uma matriz m x n com m e n sendo inseridos pelo usuário, o programa usa de 1 a n
threads para processar a soma das diagonais principais armazenando o resultado em
um vetor, podendo ainda gerar dados sobre a execução do programa gravando em um
arquivo .csv que pode ser lido por algum software de panilha eletrônica. 

DETALHES SOBRE O FUNCIONAMENTO:
-Configurações: as constantes de configuração estão no arquivo "datadefine.h"

-Booleanos
getInputFromUser       se ativado o programa perguntará ao usuário as dimensões da matriz e a quantidade de threads a usar		
printInfoProcess 	   se ativado o programa irá imprimir informações sobre o processamento
fillInputWithRandom	   se ativado o programa irá preencher a entrada padrão com valores aleatórios
fillInputWithNum 	   se ativado o programa irá preencher a entrada padrão com um determinado valor

//Parâmetros
float fillElement 	    elementos a gravar na entrada padrão  		
int fileElementsAmount  quantidade de elementos a gravar na entrada padrão
												

//Valores default
int default_M 		     Valor padrão de linhas da matriz (caso entrada de dados pelo usuário seja desativada)	
int default_N 		     Valor padrão de colunas da matriz (caso entrada de dados pelo usuário seja desativada)
int default_NumThreads 	 Quantidade padrão de threads (caso entrada de dados pelo usuário seja desativada)


-Arquivos:
	Se os arquivos de entrada e saída não existirem, serão criados.
	Se o arquivo de entrada estiver vazio ou incompleto, os elementos da matriz sem valor
	correspondente serão preenchidos com 0;
	É possível usar as configurações para fazer o programa gerar o arquivo de entrada com
	n repetições de um valor definido ou valores randômicos
	
-Threads:
Cada thread irá acessar uma região crítica que indica o número da próxima diagonal a ser processada
copiar o valor da região e incrementar seu valor.

A thread converte o número da diagonal para a coordenada do primeiro elemento dessa diagonal, acessa
esse valor e soma sucessivamente os valores dessa diagonal. Ao finalizar o processamento a soma é 
armazenada num vetor, se a diagonal processada foi x, a soma é armazenada em vet[x].

O processo é repetido até que a thread leia da região crítica um número de diagonal que não
pertence à matriz.

*/

//Incluindo bibliotecas padrão
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <stdbool.h>
#include <time.h>

//Incluindo bibliotecas criadas
#include "Util/util.h"//Biblioteca com funções de utilidades diversas
#include "datadefine.h"//Definição de dados (variáveis globais, defines e tipos de dados novos)
#include "dataStructures/Array/arrayMngr.h"//Biblioteca para gerenciar o tipo de vetor usado
#include "dataStructures/Matrix/matrixMngr.h"//Biblioteca para gerenciar o tipo de matriz usada
#include "Thread/thread.h"//Biblioteca contendo funções executadas por threads
#include "File/fileMngr.h"//Bilioteca para definir gerenciamento dos arquivos usados
#include "Thread/callThread.h"





int nomain(){
	Input in /*= inputFromUser()*/;
	DataCollector dc;
	time_t tstart, tend;
	double timeTaken, med;
	unsigned int option, tmin, tmax, loop;
	register int i, j;
	
	
	do{
		printf("DIAGONAIS PRINCIPAIS DE UMA MATRIZ\n");
		printf("1. Inserir m, n e quantidade de threads\n");
		printf("2. Coleta de dados: repetir x vezes para 1, 2, 4, 8, 16, 32, 64 ... t threas e guardar média em arquivo\n");
		scanf("%d", &option);
	}while(option <= 0 || option > 2);

	switch(option)
	{
	case 1:
		do{
			printf("1. Usar método 1: uma thread, ao finalizar o processamento irá procurar uma diagonal para processar\n");
			printf("2. Usar método 2: a quantidade de trabalho a fazer será préviamente dividida entre as threads\n");
			scanf("%d", &option);
		}while(option <= 0 || option > 2);
		
		in = inputFromUser();
		
		if(option == 1){
			tstart = clock();
			execMethod_a(in, &dc, false, true, true);
			tend = clock();
			timeTaken = difftime(tstart, tend);
		}else{
			tstart = clock();
			execMethod_b(in, &dc, false, true, true);
			tend = clock();
			timeTaken = difftime(tstart, tend);
		}
		
		printf("Tempo gasto: %lf ms\n", timeTaken);
		
		
		break;
	case 2:
		do{
			printf("1. Usar método 1: uma thread, ao finalizar o processamento irá procurar uma diagonal para processar\n");
			printf("2. Usar método 2: a quantidade de trabalho a fazer será préviamente dividida entre as threads\n");
			scanf("%d", &option);
		}while(option <= 0 || option > 2);
		
		printf("Quantidade inicial de threads: ");
		scanf("%d", &tmin);
		
		printf("Quantidade final de threads: ");
		scanf("%d", &tmax);
		
		printf("Loops por thread: ");
		scanf("%d", &loop);
		
		printf("Matriz m: ");
		scanf("%d", &in.matrixm);
		
		printf("Matriz n: ");
		scanf("%d", &in.matrixn);
		
		
		
		FILE * data = fopen("data.csv", "w");
		fprintf(data, "TEMPO MÉDIO; THREADS; LOOPS; M; N\n");
		
		for(i = tmin; i < tmax; i*=2){
			med = 0;
			for(j = 0; j < loop; j++){
				
				in.numThreads = i;
				
				if(option == 1){
					tstart = clock();
					execMethod_a(in, &dc, true, true, true);
					tend = clock();
					timeTaken = difftime(tstart, tend);
				}else{
					tstart = clock();
					execMethod_b(in, &dc, true, true, true);
					tend = clock();
					timeTaken = difftime(tstart, tend);
				}
				med += timeTaken;
			}
			
			fprintf(data,"%s; %d; %d; %d %d\n", dotToCommaDouble(med/loop), in.numThreads, loop, in.matrixm, in.matrixn);
		}
		

		break;
	}
	return 0;
}

	
	
int main(){
	Input in = inputFromUser();
	DataCollector dc;
	double timeTaken;
	time_t tstart, tend;
	
	tstart = clock();
	execMethod_a(in, &dc, false, true, true);
	tend = clock();
	timeTaken = timediff(tstart, tend);
					
	printf("%f\n", timeTaken);

	return 0;
		
}

