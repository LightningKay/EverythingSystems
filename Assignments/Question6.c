/*Assignment 2
Now write a program that uses wait() to wait for the child process to finish in the parent.
What does wait() return? What happens if you use wait() in the child?
Answer -    The following function suspends the calling process using &waitpid.
            until a child process ends.
            waitpid() suspends the calling process until the system gets status information from the child.
            If the system already has a status information on an appropriate child, then it returns immediately.

 */
#define _POSIX_SOURCE
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>

main() {
  pid_t pid;
  time_t t;
  int status;

  if ((pid = fork()) < 0)
    perror("fork() error");
  else if (pid == 0) {
    sleep(5);
    exit(1);
  }
  else do {
    if ((pid = waitpid(pid, &status, WNOHANG)) == -1)
      perror("wait() error");
    else if (pid == 0) {
      time(&t);
      printf("child is still running at %s", ctime(&t));
      sleep(1);
    }
    else {
      if (WIFEXITED(status))
        printf("child exited with status of %d\n", WEXITSTATUS(status));
      else puts("child did not exit successfully");
    }
  } while (pid == 0);
}