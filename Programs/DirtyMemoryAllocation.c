/**
 * This program just illustrates how a program can even run without any segmentation fault even when the memeory allocated for the string
 * isn't correct. Why does this happen? - the compiler probably might overwrite a variable that isnt used anymore but the program still is dirty and incorrect 
 * as we do not allocate enough memory for *dist which needs one more byte to store the end of string \0. Karthik Kolathumani
 * */
#include<stdio.h>
int main() {
    
    char *src = "hello";
    char *dst = (char *) malloc(strlen(src)); // too small!
    strcpy(dst, src); // work properly
    printf("%s", dst);
    return 0;
}