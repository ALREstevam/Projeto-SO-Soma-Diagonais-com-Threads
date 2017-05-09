#ifndef PROJSOTEST_DATADEFINE_H
#define PROJSOTEST_DATADEFINE_H
#include <pthread.h>
#include <stdbool.h>

#define DEFAULTINPUT "in.txt"
#define DEFAULTOUTPUT "out.txt"
#define DEFAULTEXDATACSVFILE "infoData.csv"

static const bool getInputFromUser = true;
static const bool generateExecutionData = true;
static const int default_M = 200;
static const int default_N = 200;
static const int default_NumThreads = 2;



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


//Informa��es sobre a execu��o do programa
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
