/**
 * Question 5, 6
 * Write a program that creates an array of integers called data of size 100 using malloc; then, set data[100] to zero.
 * What happens when you run this program? What happens when you run this program using valgrind? Is the program correct?
 * */
#include<stdio.h>
#include<stdlib.h>
int main() {
    int *data;
    data = (int *) malloc(100 * sizeof(int)); // Dynamically assigning space for 100 intergers.
    data[100] = 0;
    free(data); // this is for question 6
    printf("%d", data[100]); // this is for question 6
    return 0;
}