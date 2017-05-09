#ifndef UTIL_H
#define UTIL_H
	#include "../datadefine.h"

	//Protótipos
	void executionDataToCSV(ExecutionData exd, char * fileName);
	long timediff(clock_t t1, clock_t t2);
	void pause();
	bool verifyIsGreaterThanZero(int num, char * msgFalse);
#endif