/**
 * @file bubblesort.c
 * @author Michael Escue
 * @brief A biref bubblesort program to compare times with hw5.c
 * @version 0.1
 * @date 2019-03-13
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include "randarray.h"

int main(void){

int *array = NULL;
int x = 0;
int n = ARRAY_SIZE;
int y = 0;
int temp = 0;

array = randarray();

for (x = 0 ; x < ( n - 1 ); x++){
    for (y = 0 ; y < n - x - 1; y++){
        if (array[y] > array[y+1]){
            temp = array[y];
            array[y] = array[y+1];
            array[y+1] = temp;
        }
    }
}

// Check for successful sort.    
for (int a = 0; a < ( ARRAY_SIZE - 1); a++){
    if(array[a]>array[a+1]){
        printf("Sort & Merge FAILURE!\n");
        printf("Array[%d] = %d\n Array[%d +1] = %d\n", a, array[a], array[a+1]);
        free(array);
        return 0;
    }
}

free(array);
printf("Check passed, bubblesort SUCCESS!\n");

return 1;
}