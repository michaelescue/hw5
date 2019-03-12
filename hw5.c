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

#define NUMBEROFTHREADS 5

pthread_barrier_t barrier;      // Barrier variable.

void *debug(void *arg){
       pthread_barrier_wait(&barrier);

    return ((void *)0);
}

/**
 * @brief bubblesort function which sorts quarter sizes of an array.
 * 
 * @param arg is the structure containing the arguments for the routine
 * @return void* 
 */
void * bubblesort(void *arg){
 
    pthread_t tid;
    int quarter_size = 0;
    int *array = (int*) arg;
    int temp = 0;
    int x = 0;
    int y = 0;
    printids("This thread id =");
    tid = pthread_self();

    quarter_size = (ARRAY_SIZE/4);
    int i = (tid - 2) * quarter_size;
    int n = ((tid-1)*quarter_size);

    #ifdef VERBOSE
    printf("quart_size calculation: tid = %lx\n", tid);
    printf("quarter_size = %d\n", quarter_size);
    printf("i = %d\n", i);
    printf("n = %d\n", n);
      for (x = i; x < ( n ); x++){
        printf("Array[%d] = %d\n", x, array[x]);
        }
    #endif
    
   for (x = i ; x < ( n ); x++){
       for (y = i ; y < n - x - 1 + i; y++){
           if (array[y] > array[y+1]){         

               temp = array[y];
                array[y] = array[y+1];
                array[y+1] = temp;
            }
        }

        #ifdef VERBOSE
        printf("Pass %d:\n", x);
              for (int a = i; a < ( n ); a++){
        printf("Array[%d] = %d\n", a, array[a]);
        }
        #endif
    }
    #ifdef VERBOSE
    printf("Sorting done.\n");
    #endif
    pthread_barrier_wait(&barrier);

    return ((void *)0);
}

int main(void){

    pthread_t ntid;     // Thread ID

    int error;      // Error checking
    int *array_ptr = NULL;      // Array pointer
  
    array_ptr = randarray();   // Create a random int array.

    #ifdef VERBOSE
    printf("Array Size = %d\n", ARRAY_SIZE);
    printf("Array element 0 = %d\n", *(array_ptr+0));
    #endif

    printids("Main Thread:");

    pthread_barrier_init(&barrier, NULL, NUMBEROFTHREADS);      // Create a barrier for the threads.

    error = pthread_create(&ntid, NULL, bubblesort, array_ptr);
    if(error != 0)printf("error in thread creation.\n");

    error = pthread_create(&ntid, NULL, bubblesort, array_ptr);
    if(error != 0)printf("error in thread creation.\n");

    error = pthread_create(&ntid, NULL, bubblesort, array_ptr);
    if(error != 0)printf("error in thread creation.\n");

    error = pthread_create(&ntid, NULL, bubblesort, array_ptr);
    if(error != 0)printf("error in thread creation.\n");

    #ifdef VERBOSE
    printf("barrier = %ld\n", barrier);
    #endif

    pthread_barrier_wait(&barrier);

     #ifdef VERBOSE
        printf("Post barrer wait:\n");
              for (int a = 0; a < ( ARRAY_SIZE); a++){
        printf("Array[%d] = %d\n", a, array_ptr[a]);
        }
    #endif

    printids("Main thread:");

    free(array_ptr);
    return 1;
}