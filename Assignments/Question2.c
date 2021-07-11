/*
Write a program that opens a file (with the open() system call) and then calls fork() to create a new process.
Can both the child and parent access the file descriptor returned by open()? 
What happens when they are writing to the file concurrently, i.e., at the same time?
Answers - I have observed multiple things here, When the parent closes the Standard output file descriptor, then the child and parent process just appends to the same file (the order depends on the CPU Scheduling for the processes).
But if the file descriptor is closed again and opened a new file in the forked child process, then those appends are lost.
This shows us that the parent cannot access the child process file descriptor returned by child open() system call.
The child can access the same file descriptor returned by the parent. - Karthik Kolathumani
 */

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<assert.h>
#include<sys/wait.h>

int main(int argc, char *argv[]){

    close(STDOUT_FILENO);
    open("/Users/kkolathu/OperatingSystems/Assignments/Question2.output", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
    int rc = fork();
    if(rc < 0 ){
        fprintf(stderr,"fork failed\n");//failed.
        exit(1);
    }
    else if(rc == 0){
        // child: redirect standard output to a file
        //close(STDOUT_FILENO);
        //open("/Users/kkolathu/OperatingSystems/Assignments/Question2.output\n", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU); // These are file permissions, look for MAN pages for more details.
        printf("I am child trying to write");
    }
    else{
        // Parent goes down this path
        printf("I am parent trying to write concurrently to the same file descriptor\n");
    }
    return 0;
}