//Array é usado para
/*
Armazenar o resultado das somas
Armazenar o endereço (posição) de elemmentos de matriz
Armazenar informações sobre threads;

*/

#include "../global.h"
#include <pthread.h>



typedef struct multarrelem{
	 union variable{
		float sumResult;
		int sumDiagonal;
		CoordinatesXY coods;
		pthread_t t_id;
		pthread_attr_t t_attr; 
	};
	
	
	
}MultipleArrayElement;


int arrAlloc(MultipleArrayDescriber *arrDesc){
	arrDesc->arr.variable.sumResult = 10
	
		
}