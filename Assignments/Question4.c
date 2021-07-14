/*
Write a program that calls fork() and then calls some form of exec() to run the program /bin/ls.
See if you can try all of the variants of exec(), including (on Linux) execl(), execle(), execlp(), execv(), execvp(), and execvpe().
Why do you think there are so many variants of the same basic call?
Answers - The exec family of function replaces the current process with new process image. The stack, heap and other data segments are reinitialized
          The exec() has a family of functions that follow the 'exec' prefix.
          -l execl(), execlp(), execle() - int execl(const char *pathname, const char *arg, ..., (char *) NULL);
                                           Takes in argument as a list of pointers to strings that are either binary executable or a script that starts with #!interpreter [optional-arg]
          -v execv(), execvp(), execvpe()- Takes in argument of array of one or more null terminated strings.
          -e execle(), execvpe() -  The environment of the nre process image is specified by the 'envp' argument -  int execvpe(const char *file, char *const argv[], char *const envp[]);
          -p execlp(), execvp(), execvpe() - These functions duplicate the actions of the shell in searching for an executable file if the specified filename does not contain the '/' character.
                                             The file is sought in the colon - separated list of directory pathnames specified in the PATH environment variable.
 */
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<assert.h>
#include<sys/wait.h>

int main(int argc, char *argv[]){
    int rc = fork();
    if(rc < 0 ){
        fprintf(stderr,"fork failed\n");//failed.
        exit(1);
    }
    else if(rc == 0){
        // child: redirect standard output to a file
        close(STDOUT_FILENO);
        open("/Users/kkolathu/OperatingSystems/Assignments/Question4.output", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU); // These are file permissions, look for MAN pages for more details.
        // now exe "ls"..
        char *myArgs[3];
        myArgs[0] = strdup("ls");
        myArgs[1] = strdup("/Users/kkolathu/OperatingSystems/Assignments/");
        myArgs[2] = NULL;
        execvp(myArgs[0], myArgs);
    }
    else{
        // Parent goes down this path
        int wc = wait(NULL);
        assert(wc >= 0);
    }
    return 0;
}