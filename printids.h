/**
 * @file printids.h
 * @Michael Escue
 * @brief Header file created for the APUE program printids.c
 * @version 0.1
 * @date 2019-03-11
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef PRINTIDS_C
#define PRINTIDS_C
#include    "printids.c"
#endif

#ifndef PTHREAD_H
#define PTHREAD_H
#include    <pthread.h>
#endif


/**
 * @brief This function prints the thread ID of the process running it.
 * 
 * @param s A constant char. A string to preface the printed IDs.
 */
void printids(const char *s);