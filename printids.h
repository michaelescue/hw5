/**
 * @file printids.h
 * @author Michael Escue
 * @brief Header file created for the APUE program printids.c
 * @version 0.1
 * @date 2019-03-11
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef STDIO_H
#define STDIO_H
#include <Stdio.h>
#endif

#ifndef UNISTD_H
#define UNISTD_H
#include    <unistd.h>
#endif

#ifndef SYS_TYPES_H
#define SYS_TYPES_H
#include <sys/types.h>
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
#ifndef PRINTIDS_H
#define PRINTIDS_H
void printids(const char *s);
#endif