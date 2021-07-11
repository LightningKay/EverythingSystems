/* In this program we use the execvp() system call. The purpose of this program is to demonstrate its purpose.
   When the fork() is called, it creates an almost similar process to its calling parent process. If we require to execute a 
   different process other than the parent one, we will use execvp(). The execvp() is a strange system call. Once it is called, it
   loads code from the executable (in this case wc - word count) and overwrites its current code segment (its current static data) with it
   the heap and the stack and other parts of the memory space of the program are reinitialized. Then the program simply runs that 
   program passing the required arguments. Thus, its safe to say that the execvp() system call modifies the p3 process(since we fork p3, we call it p3) - Karthik Kolathumani*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){
    printf("Parent process (pid:%d)\n", (int)getpid());
    fflush(stdout);
    int rc = fork();

    if(rc < 0){
        // fork failed
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    else if(rc == 0){
        // child process
        printf("This is child process (pid:%d)\n", (int)getpid());
        fflush(stdout);
        char *myArgs[3];
        myArgs[0] = strdup("wc");  // This is word count program
        myArgs[1] = strdup("p3.c");// Argument: file to count
        myArgs[2] = NULL; // marks end of array
        execvp(myArgs[0], myArgs); // runs word count
        printf("This will not print"); 
    }
    else{
        // parent goes down this path (original process)
        int wc = wait(NULL);
        printf("This is the parent process of %d (wc:%d) (pid:%d)\n", rc, wc, (int)getpid());
    }
    return 0;
}