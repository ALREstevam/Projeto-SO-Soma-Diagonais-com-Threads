#ifndef CALLTHREAD_H
#define CALLTHREAD_H

#include "../Util/util.h"
#include "../datadefine.h"
/**
 * Fun��es para gerenciar a entrada de dados, processamento da soma das diagonais usando threads
 * e sa�da de dados para tela ou arquivo.
 */


void execMethod_a(Input in, DataCollector *rsp, bool printMatrix, bool printOutput, bool printThreadInfo);
void execMethod_b(Input in, DataCollector *rsp, bool printMatrix, bool printOutput, bool printThreadInfo);

#endif