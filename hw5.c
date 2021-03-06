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


#include "printids.h"
#include "randarray.h"
#include <pthread.h>

#define NUMBEROFTHREADS 5
#define WORKING_THREADS 4
#define NTHR 2
#define PARTITION_SIZE (ARRAY_SIZE / WORKING_THREADS)

//Debug Defines
// VERBOSE - main()
// VERBOSESORT - bubblesort()
// VERBOSEMERGE - merge()

pthread_barrier_t barrier, lbarrier, ubarrier;      // Barrier variable.
int merged1[ARRAY_SIZE] = {0};      // Array for first pairs of threads to sort to.
int merged2[ARRAY_SIZE] = {0};      // Array of final result from merging the two chunks of merged1 by thread 1.

pthread_t tid1 = 0;
pthread_t tid2 = 0;
pthread_t tid3 = 0;
pthread_t tid4 = 0;
pthread_t tid5 = 0;

/**
 * @brief the sorted merge section of code which merges based on thread id.
 * 
 * @param arg initially the randomly initialized array.
 * @return void* no interest in this return value.
 */
void *merge(void *arg){
    int *array = NULL;
    int *merged = NULL;
    int ai = 0;
    int bi = 0;
    int i = 0;
    int limit_size = PARTITION_SIZE;
    int offset;
    pthread_t tid = pthread_self();

    if(tid == tid1) tid = 1;
    if(tid == tid2) tid = 2;
    if(tid == tid3) tid = 3;
    if(tid == tid4) tid = 4;
    if(tid == tid5) tid = 5;

    array = (int*) arg;
    merged = merged1;

    if(tid == 1){
        limit_size = (PARTITION_SIZE * 2);
        array = merged1;
        merged = merged2;
    }
    else if(tid == 5){
        offset = 2;
        i = (limit_size * NTHR);
    }
    else 
        offset = 0;

    // Only threads 3 and 5 merge with the other eventhreads. Thread 1 merges the merged threads by itself.

    /**
     * This section of code is the comparison between elements of the upper and lower chunks,
     * determined by the thread id. 
     */
    do{
        #ifdef VERBOSEMERGE
        printf("do-while 1: array[ai-effective] = %d\n", array[ai + (offset * limit_size)]);
        printf("do-while 1: array[bi-effective] = %d\n", array[bi + limit_size + (offset * limit_size)]);
        printf("ai = %d\nbi = %d\noffset = %d\ni = %d\nlimit_size = %d\ntid = %ld\n", ai, bi, offset, i, limit_size, tid);
        #endif

        
        if(array[ai + (offset * limit_size)] <= array[bi + limit_size + (offset * limit_size)]){ 
            merged[i] = array[ai + (offset * limit_size)];
            if(ai < limit_size)
                ai++;
        }
        else{
            merged[i] = array[bi + limit_size + (offset * limit_size)];
            if(bi < limit_size)
                bi++;
        }
        i++;
    }while((ai < limit_size)&&(bi < limit_size));

    /**
     * This section of code is the logic used when one of the segments of the array have no more elements to compare. 
     */
    do{   
        #ifdef VERBOSEMERGE
        printf("do-while 2: array[ai-effective] = %d\n", array[ai + (offset * limit_size)]);
        printf("do-while 2: array[bi-effective] = %d\n", array[bi + limit_size + (offset * limit_size)]);
        printf("ai = %d\nbi = %d\noffset = %d\ni = %d\nlimit_size = %d\ntid = %ld\n", ai, bi, offset, i, limit_size, tid);
        #endif

        if(ai == limit_size){
            merged[i] = array[bi + limit_size + (offset * limit_size)];                      
            bi++;
        }
        else if(bi == limit_size){
            merged[i] = array[ai + (offset * limit_size)];
            ai++;
        }
        i++;
    }while((ai < limit_size) || (bi < limit_size));

     #ifdef VERBOSE
    printf("Merging done for thread %ld.\n", tid);
    printf("Post thread [%ld] merge:\n", tid);
    for (int a = 0; a < ( ARRAY_SIZE); a++){
        printf("Array[%d] = %d\n", a, merged[a]);
    }
    printids("Thread returning from merge =");
    #endif

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
    printids("New Thread:");
    tid = pthread_self();

    if(tid == tid1) tid = 1;
    if(tid == tid2) tid = 2;
    if(tid == tid3) tid = 3;
    if(tid == tid4) tid = 4;
    if(tid == tid5) tid = 5;

    if(tid)
    quarter_size = PARTITION_SIZE;
    int i = (tid - 2) * quarter_size;
    int n = ((tid-1) * quarter_size);

    #ifdef VERBOSESORT
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

        #ifdef VERBOSESORT
        printf("Pass %d:\n", x);
              for (int a = i; a < ( n ); a++){
        printf("Array[%d] = %d\n", a, array[a]);
        }
        #endif
    }
    #ifdef VERBOSESORT 
    printf("Sorting done for thread %ld.\n", tid);
    printf("Post thread [%ld] partition sort:\n", tid);
    for (int a = 0; a < ( ARRAY_SIZE); a++){
        printf("Array[%d] = %d\n", a, array[a]);
    }
    #endif


    /**
     * This block of code acts as a thread stopper, to allow threads still processing
     * to finish sorting their segments before moving on to merge. 
     */
    if(tid == 2){
        #ifdef VERBOSESORTWAIT
         printf("Thread %ld waiting.\n", tid);
        #endif
        pthread_barrier_wait(&lbarrier);
    }
    if(tid == 3){
         #ifdef VERBOSESORTWAIT
         printf("Thread %ld waiting.\n", tid);
        #endif
        pthread_barrier_wait(&lbarrier);
    }
    if(tid == 4){
         #ifdef VERBOSESORTWAIT
         printf("Thread %ld waiting.\n", tid);
        #endif
        pthread_barrier_wait(&ubarrier);
    }
    if(tid == 5){
         #ifdef VERBOSESORTWAIT
         printf("Thread %ld waiting.\n", tid);
        #endif
        pthread_barrier_wait(&ubarrier);
    }
    if((tid % 2) == 0){
         #ifdef VERBOSESORTWAIT
         printf("Thread %ld waiting for single thread merge.\n", tid);
        #endif
        pthread_barrier_wait(&barrier);
        return ((void *)0);
    }

    merge(arg);
    if(tid >= 2){
        #ifdef VERBOSEWAIT
            printf("Thread %ld waiting for single thread merge.\n", tid);
        #endif
        pthread_barrier_wait(&barrier);
    }
    return ((void *)0);
    
}

/**
 * @brief main section of code to generate threads and call code to generate random array.
 * 
 * @return int returns a result (not interested)
 */
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

    error = pthread_create(&tid2, NULL, bubblesort, array_ptr);
    if(error != 0)printf("error in thread creation.\n");

    error = pthread_create(&tid3, NULL, bubblesort, array_ptr);
    if(error != 0)printf("error in thread creation.\n");

    error = pthread_create(&tid4, NULL, bubblesort, array_ptr);
    if(error != 0)printf("error in thread creation.\n");

    error = pthread_create(&tid5, NULL, bubblesort, array_ptr);
    if(error != 0)printf("error in thread creation.\n");

    #ifdef VERBOSE
    printf("barrier = %ld\n", barrier);
    #endif

    pthread_barrier_wait(&barrier);
    merge(array_ptr);
     #ifdef VERBOSE
        printf("Post barrer wait post merge:\n");
              for (int a = 0; a < ( ARRAY_SIZE); a++){
        printf("Array[%d] = %d\n", a, merged2[a]);
        }
    #endif

    for (int a = 0; a < ( ARRAY_SIZE - 1); a++){
        if(merged2[a]>merged2[a+1]){
            printf("Sort & Merge FAILURE!\n");
            printf("Array[%d] = %d\n Array[%d +1] = %d\n", a, merged2[a],merged2[a+1]);
            free(array_ptr);
            return 0;
        }
    }
    
    free(array_ptr);

    printf("Check passed, Sort & Merge SUCCESS!\n");
    return 1;
}