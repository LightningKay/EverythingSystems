/*
Write a program that calls fork() and then calls some form of exec() to run the program /bin/ls.
See if you can try all of the variants of exec(), including (on Linux) execl(), execle(), execlp(), execv(), execvp(), and execvpe().
Why do you think there are so many variants of the same basic call?
Answers -  - Karthik Kolathumani
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