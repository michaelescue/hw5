/**
 * @file printids.c
 * @W. Richard Stevens, Stephen A. Rago
 * @brief From the Text, "Advanced Programming in the UNIX Environment": A Thread ID printing program.
 * @ Argument *s of the function is a string prefacing the printed thread ID's.
 * 
 */

pthread_t ntid;

void printids(const char *s){
    pid_t       pid;
    pthread_t   tid;

    pid = getpid();
    tid = pthread_self();
    printf("%s pid %lu tide %lu (ox%lx)\n", s, (unsigned long)pid, (unsigned long)tid, (unsigned long)tid);
}

