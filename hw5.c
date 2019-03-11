/**
 * @Assignment 5
 * @ECE 362
 * @Michael Escue
 * 
 * @This program:
 * @ 1.  Prints out the thread Id of 4 seperate threads.
 * @ 2.  Breaks an array into 4 partitions.
 * @ 3.  Uses one thread to sort the partition using "Bubble Sort".
 * @ 4.  Merges 4 threads to 2 threads of the sorted partitions.
 * @ 5.  Merges the 2 remaining partitions into one sorted array.
 * @ 6.  Checks the result to ensure it is sorted.
 */


#include "printids.c"
#include "randarray.h"
#include <pthread.h>

/**
 * @brief bubblesort function which sorts quarter sizes of an array.
 * 
 * @param arg is the structure containing the arguments for the routine
 * @return void* 
 */
void *bubblesort(void *arg){

    #ifdef VERBOSE
    printf("Entering new thread.\n");
    #endif
    
    pthread_t tid;
    int quarter_size = 0;
    int *array = (int*) arg;
    int temp = 0;
    printids("This thread id =");
    tid = pthread_self();

    quarter_size = (ARRAY_SIZE/4);
    int x = (tid - 2) * quarter_size;
    int n = ((tid-1)*quarter_size);
    int y = x;

    #ifdef VERBOSE
    printf("quart_size calculation: tid = %lx\n", tid);
    printf("quarter_size = %d\n", quarter_size);
    printf("x = %d\n", x);
    printf("n = %d\n", n);
    printf("y = %d\n", y);
    printf("Test array access: Array[0] = %d", array[0]);
    #endif
    
    for (x = 0 ; x < ( n- 1 ); x++){
            for (y = 0 ; y < n - x - 1; y++){
                if (array[y] > array[y+1]){
                    temp = array[y];
                    array[y] = array[y+1];
                    array[y+1] = temp;
            }
            #ifdef VERBOSE
            printf("array[%d] = %d", x, array[x]);
            #endif
        }
    }

return 0;
}

int main(void){

    int error;      // Error checking
    pthread_t ntid; // Thread ID
    int *array_ptr = NULL; // Array pointer
    int array_size; // Array Size.
  

    array_size = randarray(array_ptr);   // Create a random int array.

    #ifdef VERBOSE
    printf("Array Size = %d\n", array_size);
    #endif

    printids("Main Thread:");

    error = pthread_create(&ntid, NULL, bubblesort, NULL);
     if(error != 0)printf("error in thread creation.\n");

    printids("Main thread:");

    free(array_ptr);
    return 1;
}