/*
Write another program using fork(). The child process should print “hello”; the parent process should print “goodbye”. 
You should try to ensure that the child process always prints first; can you do this without calling wait() in the parent?

Answers - We can use wait for inter process communication. This will ensure determinism.
          It is quite difficult to achieve this without using WAITs, as there needs to be some sort of communication
          which needs to be done between the processes to ensure order. 
          Though there exists shared memory segment, and either condition variables or semaphores, to solve this problem. - Karthik Kolathumani
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[]){

  int rc = fork();
  if (rc < 0) {
    // fork failed
    fprintf(stderr, "fork failed\n");
    exit(1);
  }
  else if (rc == 0){
    // child (new process)
    printf("hello\n");
  }
  else{
    // parent goes down this path (main)
    int rc_child = wait(NULL);
    printf("Goodbye\n");
  }
  return 0;
}