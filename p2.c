/* In the previous example we were able to see how the output for the fork() system call can be non deterministic.
   To achieve determinism, we use another system call - wait() or its more complete sibling waitpid() LOL :P 
   This helps us to wait for the child process to finish first and then execute the parent process.
   Again, the wait system call doesnt gaurantee this, there are cases where the wait returns before the child exists.
   You gotta read the MAN pages for that! - Karthik Kolathumani*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[]){
    printf("This is parent process (pid:%d)\n", (int)getpid());
    fflush(stdout);
    int rc = fork();

    if(rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    else if (rc == 0){
        printf("This is the new child process (pid:%d)\n", (int)getpid());
    }
    else{
        int rc_wait = wait(NULL);
        printf("This is parent of %d (rc_wait:%d) (pid:%d)\n", rc, rc_wait, (int)getpid());
    }
    return 0;
}
