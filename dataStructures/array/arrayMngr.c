//
// Created by andre on 02/05/2017.
//

#include <stdlib.h>
#include <stdbool.h>
#include "../../datadefine.h"

bool createArray(ArrayDescriber *arr, unsigned int size){
    arr->bottom = -1;
    arr->size = size;
    arr->top = -1;

    arr->data = malloc(size * sizeof(UData));

    if(arr->data == NULL){
        return false;
    }
    return true;
}

bool reallocArray(ArrayDescriber *arr, unsigned int newsize){
    arr->size = newsize;
    if(realloc(arr, newsize) == NULL){
		return false;
	}
    if(arr->data == NULL){
        return false;
    }
    return true;
}

bool arrayAddTop(ArrayDescriber *arr, UData info){
    if(arr->top+1 > arr->size){
        if(reallocArray(arr, arr->size + 10) == NULL){
            return false;
        }
    }
    arr->top++;
    arr->data[arr->top] = info;
    return true;
}

bool accessPosition(ArrayDescriber *arr, unsigned int pos, UData *rsp){
    if(pos < arr->top && pos > arr->bottom){
        *rsp = arr->data[1];
        return false;
    }
    return true;
}

void deleteArray(ArrayDescriber *arr){
    free(arr->data);
}



