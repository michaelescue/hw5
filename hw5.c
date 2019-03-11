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

void * thread_func(void *arg){
    printids("This thread id =");
}


int main(int argc, char * argv){

    int error;
    pthread_t ntid;

    int *array_ptr = NULL;

    randarray(array_ptr);   // Create a random int array.

    printids("Main Thread:");

    error = pthread_create(&ntid, NULL, thread_func, NULL);
    if(error != 0)printf("error in thread creation.");
    error = pthread_create(&ntid, NULL, thread_func, NULL);
    if(error != 0)printf("error in thread creation.");
    error = pthread_create(&ntid, NULL, thread_func, NULL);
    if(error != 0)printf("error in thread creation.");
    error = pthread_create(&ntid, NULL, thread_func, NULL);
    if(error != 0)printf("error in thread creation.");

    printids("Main thread:");

    free(array_ptr);
    return 1;
}