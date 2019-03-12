/**
 * @file randarray.c
 * @author Michael Escue
 * @brief Source code to generator an array of number "array_size" int variables of random value. Returns a pointer to the start of the allocated array.
 * @version 0.1
 * @date 2019-03-11
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "randarray.h"

#define ARRAY_SIZE 20

int *randarray(void){

    int *array_p = NULL;
    int array_size = ARRAY_SIZE;
    int temp = 0;

    if( (array_p = malloc(sizeof(int) * array_size)) == NULL)
        fprintf(stderr, "Error in malloc.");
    for(int i = 0; i < array_size; i++){
        temp = rand();
        temp = (temp % 100000);
        *(array_p + i) = temp;
        #ifdef VERBOSE
        printf("%d:%d ", i, *(array_p + i));
        #endif
    }
    
    #ifdef VERBOSE
    printf("\n");
    #endif

    return array_p;

}