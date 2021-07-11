/* The purpose of this simple program is to illustrate few things - 
   1) The system call fork() creates a new child process which is almost a copy of its calling process.
      The fork() is not an exact copy, as it comes to life as if it has called fork on itself.
      Means, the new process starts executing from the line - int rc = fork() and not from the main itself.
      This is an important distinction for the OS as the line int rc = fork() for the child process returns 0 while for 
      the parent process it returns the child PID.
   2) The non deterministic output -  Assuming that the program runs on a single core, we are able to unable to say which
      process runs first. It depends on the scheduling policy both in single core and multi core CUPs. - Karthik Kolathumani*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[]){

  printf("hello world (pid:%d)\n", (int)getpid());
  fflush(stdout);
  int rc = fork();
  if (rc < 0) {
    // fork failed
    fprintf(stderr, "fork failed\n");
    exit(1);
  }
  else if (rc == 0){
    // child (new process)
    printf("hello, I am child (pid:%d)\n", (int)getpid());
  }
  else{
    // parent goes down this path (main)
    printf("hello, I am parent of %d (pid:%d)\n", rc, (int)getpid());
  }
  return 0;
}