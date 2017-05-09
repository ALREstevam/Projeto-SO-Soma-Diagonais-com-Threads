#ifndef PROJSOTEST_DATADEFINE_H
#define PROJSOTEST_DATADEFINE_H
#include <pthread.h>
#include <stdbool.h>

#define DEFAULTINPUT "in.txt"
#define DEFAULTOUTPUT "out.txt"
#define DEFAULTEXDATACSVFILE "infoData.csv"

//Valores de configuração
static const bool getInputFromUser = false; //Usar dados do usuário = true, dados default = false
static const bool generateExecutionData = true;//Gerar csv com dados de execução = true, não gerar = false
static const bool printInfoProcess = false;//Fazer prints durante o processamento = true, não fazer = false

//Valores default
static const int default_M = 500;
static const int default_N = 500;
static const int default_NumThreads = 500;



//Tipo de dado que reune diferentes dados
typedef struct udt{
    union{
        pthread_t tid;
        float rsp;
        int value;
    }dt;
}UData;


//Descritor de matriz
typedef struct mxdccb{
    float ** data;
    int m, n, diagNum;
}MatrixDescriber;

//Descritor de vetor
typedef struct{
	UData * data;
    int top, bottom;
    unsigned int size;
}ArrayDescriber;

//Argumentos para thread de soma
typedef struct{
    MatrixDescriber * mx;
    unsigned short int threadNum;
    unsigned int totThreads;
    ArrayDescriber *rspArr;
}ThreadArgsInfo;


//Informações sobre a execução do programa
typedef struct 
{
	double elapsedTime;
	int m, n, diags, numThreads;
}ExecutionData;

//Tipo de dado para guardar coordenadas de uma matriz
typedef struct {
    int mpos, npos;
}Coords;




#endif //PROJSOTEST_DATADEFINE_H
