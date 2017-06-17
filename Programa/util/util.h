#ifndef UTIL_H
#define UTIL_H
	#include "../datadefine.h"

	//Protótipos
	double timediff(clock_t t1, clock_t t2);//Calcula tempo entre dois intervalos
	void pauseMsg();//Mostra uma mensagem de pausa
	char * dotToCommaDouble(double num);//recebe um double e retorna uma string trocano "." por ","
	char * dotToCommaFloat(float num);//recebe um floar e retorna uma string trocano "." por ","
	bool inputFromUser(Input *in);
	void OutputSumToUser(MatrixDescriber *matrix, ArrayDescriber *rspArr);
	void putDefaultTitle(char * title, int h);
	void printThreadWork(ArrayDescriber rspArr, ArrayDescriber tidArr, MatrixDescriber mx, unsigned int numt);
#endif