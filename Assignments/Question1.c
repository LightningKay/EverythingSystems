/* Assignment 2 Question 1 - 
Write a program that calls fork().
Before calling fork(), have the main process access a variable (e.g., x) and set its value to something (e.g., 100). 
What value is the variable in the child process? What happens to the variable when both the child and parent change the value of x?
Answer - The child process is a copy of the parent process, so it has COPY (not reference) of all the variables that the parent process has.
Hence we see no change in the parent process when the sharedVaribale is altered at the child level.
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[]){

  printf("Parent process (pid:%d)\n", (int)getpid());
  fflush(stdout);
  int sharedVariable = 100;
  int rc = fork();
  if (rc < 0) {
    // fork failed
    fprintf(stderr, "fork failed\n");
    exit(1);
  }
  else if (rc == 0){
    // child (new process)
    printf("This is the value of the shared variable in child process before changing it - %d\n", sharedVariable);
    sharedVariable -= 1;
  }
  else{
    // parent goes down this path (main)
    int rc_wait = wait(NULL);
    printf("This is parent process and the value of the sharedVaribale here is - %d\n", sharedVariable);
  }
  return 0;
}