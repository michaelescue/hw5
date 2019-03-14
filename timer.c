/* timer.c 
Program that executes another program (and any arguments)
and the prints out the amout of time the program executed.

For example: after compiling and naming it "timer" try it 
with the command "./timer sleep 3"
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/time.h>
#include <sys/wait.h>

#define BADINPUTS "Invalid inputs\n\tuse: timer program <arguments> ...\n"

struct timeval startTime, endTime;

void err_sys(char *msg)
{ fprintf(stderr, "%s %s\n",msg, strerror(errno));
  exit(-1);
}


printTimeDiff()
{
  int sec_diff, msec_diff;

     gettimeofday(&endTime, NULL);

     sec_diff = endTime.tv_sec - startTime.tv_sec;

     msec_diff = endTime.tv_usec - startTime.tv_usec;
     if (msec_diff < 0 ) { msec_diff += 1000000; sec_diff--;}

     printf("\ntime elapsed: \n\t%4d sec\n\t%4d usec\n", sec_diff, msec_diff);
}



int main(int argc, char *argv[])
{
  int sec_diff, msec_diff, rc;


  if( argc < 2 ) {fprintf(stderr, BADINPUTS); exit(-1);}

  gettimeofday(&startTime, NULL);

  rc = fork();
  if (rc < 0) { fprintf(stderr, "fork failed\n"); exit(1); }

  if (rc == 0) 
    { 
      execvp(argv[1], &argv[1]);
      fprintf(stderr, "exec failed\n"); exit(1);
    } 
 
  // parent 
     rc = wait(NULL);
     printTimeDiff();


return 0;

}

