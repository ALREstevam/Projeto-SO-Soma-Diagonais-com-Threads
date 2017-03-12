#ifndef global_C
#define global_C

#include <pthread.h>


//Coordenadas
typedef struct coordinates_x_y
{
	int x, y;
}CoordinatesXY;


//ELEMENTO DA MATRIZ
typedef struct matrix_elem
{
	double value;
	CoordinatesXY nextInMainDiagonal;
	//int pos;
	//XYCoordinates coord;
	
}MatrixElem;

//DESCRITOR DE MATRIZ
typedef struct matrix_describer
{
	MatrixElem **matrix;
	unsigned int m, n;
}MatrixDescriber;



typedef union variables{
	float flt; //resultado da soma de cada diagonal
	CoordinatesXY coords; //Indicadores de primeiro elemento da diagonal
 	pthread_t tid; //id da thread
	
}Var;

typedef struct variabledescriber{
	Var *var;
	unsigned int top;
	unsigned int size;
	char dataType[3];
}ArrayDescriber;



//Argumentos para uso de threads
typedef struct targs
{
	MatrixDescriber *mx;//Matriz
	ArrayDescriber *diagonals;//Diagonais a calcular
	ArrayDescriber *sums;//Onde o resultado será guardado
	
}TArgs;

#endif