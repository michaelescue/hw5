/**
 * @file printids.c
 * @W. Richard Stevens, Stephen A. Rago
 * @brief From the Text, "Advanced Programming in the UNIX Environment": A Thread ID printing program.
 * @ Argument *s of the function is a string prefacing the printed thread ID's.
 * 
 */

#include "printids.h"

pthread_t ntid;

void printids(const char *s){
    pid_t       pid;
    pthread_t   tid;

    pid = getpid();
    tid = pthread_self();
    printf("%s pid: %lu tid: %lu (0x%lx)\n", s, (unsigned long)pid, (unsigned long)tid, (unsigned long)tid);
}

