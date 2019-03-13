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
#define WORKING_THREADS 4
#define NTHR 2
#define PARTITION_SIZE (ARRAY_SIZE / WORKING_THREADS)

pthread_barrier_t barrier, lbarrier, ubarrier;      // Barrier variable.
int merged[ARRAY_SIZE] = {0};

/**
 * @brief Garbage routine to isolate threads. Used for debugging.
 * 
 * @param arg  NULL
 * @return void*  NULL
 */
void *debug(void *arg){
       pthread_barrier_wait(&barrier);

    return ((void *)0);
}

void *merge(void *arg){
    int *array = (int*) arg;
    int ai;
    int bi;
    int i;

    do{
        if(array[ai] < array[bi]){
            merged[i] = array[ai];
            if(ai < PARTITION_SIZE)
                ai++;
        }
        else{
            merged[i] = array[bi];
            if(bi < PARTITION_SIZE)
                bi++;
        }
        i++;
    }while((ai != (PARTITION_SIZE-1))||(bi != (PARTITION_SIZE-1)));

    do{
        if(ai == (PARTITION_SIZE-1)){
        merged[i] = array[bi];
        bi++
        }
        else if(bi == (PARTITION_SIZE-1)){
            merged[i] = array[ai];
            ai++
        }
    }while((ai != (PARTITION_SIZE))||(bi != (PARTITION_SIZE)));
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

        #ifdef VVERBOSE
        printf("Pass %d:\n", x);
              for (int a = i; a < ( n ); a++){
        printf("Array[%d] = %d\n", a, array[a]);
        }
        #endif
    }
    #ifdef VERBOSE2
    printf("Sorting done for thread %ld.\n", tid);
    printf("Post thread [%ld] partition sort:\n", tid);
    for (int a = 0; a < ( ARRAY_SIZE); a++){
        printf("Array[%d] = %d\n", a, array[a]);
    }
    #endif

    if(tid == 2){
        #ifdef VERBOSE
         printf("Thread %ld waiting.\n", tid);
        #endif
        pthread_barrier_wait(&lbarrier);
    }
    if(tid == 3){
         #ifdef VERBOSE
         printf("Thread %ld waiting.\n", tid);
        #endif
        pthread_barrier_wait(&lbarrier);
    }
    if(tid == 4){
         #ifdef VERBOSE
         printf("Thread %ld waiting.\n", tid);
        #endif
        pthread_barrier_wait(&ubarrier);
    }
    if(tid == 5){
         #ifdef VERBOSE
         printf("Thread %ld waiting.\n", tid);
        #endif
        pthread_barrier_wait(&ubarrier);
    }
    if((tid % 2) == 0){
         #ifdef VERBOSE
         printf("Thread %ld waiting for single thread merge.\n", tid);
        #endif
        pthread_barrier_wait(&barrier);
        return ((void *)0);
    }
    else{
        merge(arg);
        if(tid >= 2){
            #ifdef VERBOSE
             printf("Thread %ld waiting for single thread merge.\n", tid);
            #endif
            pthread_barrier_wait(&barrier);
        }
        else if(tid == 1){
        #ifdef VERBOSE
         printf("Thread %ld: Main thread merged.\n", tid);
        #endif
        }
        return ((void *)0);
    }
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
    pthread_barrier_init(&ubarrier, NULL, NTHR);      // Create a barrier for the threads.
    pthread_barrier_init(&lbarrier, NULL, NTHR);      // Create a barrier for the threads.

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
        printf("Post barrer wait post merge:\n");
              for (int a = 0; a < ( ARRAY_SIZE); a++){
        printf("Array[%d] = %d\n", a, snums[a]);
        }
    #endif

    printids("Main thread:");

    free(array_ptr);
    return 1;
}