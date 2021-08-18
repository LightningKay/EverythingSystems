/**
* Simple program to illustrate virtual addressing of the memory.
* From this, you can see that code comes first in the address space, then the heap, and the stack is all the way at the other end of this large virtual space. 
* All of these addresses are virtual, and will be translated by the OS and hardware in order to fetch values from their true physical locations.
*/
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[]) {
   printf("location of code : %p\n", main);
   printf("location of heap : %p\n", malloc(100e6));
   int x = 3;
   printf("location of stack: %p\n", &x);
   return x;
}