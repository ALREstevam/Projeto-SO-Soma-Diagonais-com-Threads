#ifndef UTIL_H
#define UTIL_H
	#include "../datadefine.h"

	//Protótipos
	void executionDataToCSV(ExecutionData exd, char * fileName);
	long timediff(clock_t t1, clock_t t2);
	void pause();
	void appendToMedFile(char * filename, int threads, double time);
	void appendToTExecutionFile(char * filename, ThreadExecutionData ted);
	void putHeader(char * filename, char * csvheader);
	
#endif