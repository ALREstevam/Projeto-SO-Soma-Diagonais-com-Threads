#ifndef PROJSOTEST_DATADEFINE_H
#define PROJSOTEST_DATADEFINE_H
#include <pthread.h>
#include <stdbool.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

//Valores de configuração
static const bool getInputFromUser 			= true; //Usar dados do usuário = true, dados default = false
static const bool printInfoProcess 			= true;//Fazer prints durante o processamento = true, não fazer = false
static const bool fillInputWithRandom	 	= false;
static const bool fillInputWithNum 			= false;

//Parâmetros
static const float fillElement 				= 1;
static const int fileElementsAmount 		= 99999;
												

//Valores default
static const int default_M 					= 500;
static const int default_N 					= 500;

static const int default_NumThreads 		= 4;


#define defaultInputPath "in.txt"
#define defaultOutputPath "out.txt"


//Tipo de dado que reune diferentes dados
typedef
    union{
        pthread_t tid;
        float rsp;
        int value;
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
    ArrayDescriber *rspArr;
    pthread_mutex_t *lock;
    unsigned short int *contDiag;
}ThreadArgsInfo;

//Tipo de dado para guardar coordenadas de uma matriz
typedef struct {
    unsigned short int mpos, npos;
}Coords;

typedef struct{
	double elapsedTime;
	unsigned short int requiredThreads;
	int usedThreads;
	int createdTheads;
	unsigned short int m;
	unsigned short int n;
	unsigned int diagonals;
}DataCollector;





#endif //PROJSOTEST_DATADEFINE_H
