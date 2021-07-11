/* This program illustrates how powerful fork() and exec() are and how they are being internally used by the OS to make things 
easy for the user. 
Consider this -> wc p3.c > newfile.txt
wc of the p3.c file is redirected to a file named newfile.txt instead of printing the result on the screen. 
The shell closes the standard output and opens the newfile.txt.
This program exactly does that - As we close the STDOUT_FILENO file descriptor, the output of printf() will be routed to the newly-opened file
instead of the screen.
(Pipes and Filters in Unix does the same thing, Output of one program is an input to another program(seprate child forked process)) */
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
        open("/Users/kkolathu/OperatingSystems/p4.output", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU); // These are file permissions, look for MAN pages for more details.
        // now exe "wc"..
        char *myArgs[3];
        myArgs[0] = strdup("wc");
        myArgs[1] = strdup("p4.c");
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