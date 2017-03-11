#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* sum_runner(void* arg){
	long long *limit_ptr;
	long long limit = *limit_ptr;
	free(arg);
	
	long long sum = 0;
	long long i;
	for( i = 0; i <= limit; i++){
		sum += 1;
	}
	
	//Pass back data in dynamcally allocate memory
	long long *answer = malloc(sizeof(*answer));
	*answer = sum;
	
	pthread_exit(answer);
	return;
}

int main(int argc, char **argv){
	if(argc < 2){
		printf("Usage: %s <num>\n", argv[0]);
	}
	
	long long *limit = malloc(sizeof(*limit));
	*limit = atoll(argv[1]);
	
	//Thread ID
	pthread_t tid;
	
	//Thread Attributes
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	
	pthread_create(&tid, &attr, sum_runner, limit);
	 
 	 long long *result;
	 
	pthread_join(tid, (void**)&result);
	
	
	printf("Sum is: %lld\n", *result);
	free(result);
	
	
	getchar();
	return 0;
}










































