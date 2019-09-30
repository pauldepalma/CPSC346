/*
Class: CPSC 346-01 & CPSC 346-02
Team Member 1: Paul De Palma
Team Member 2: N/A 
GU Username of project lead: depalma
Pgm Name: exA_hello_world.c
Pgm Desc: Displays text, illustrates command line arguments
Usage: ./a.out "hello world"
*/


#include <stdio.h>

int main(int argc, char* argv[])
{
 printf("There are %d arguments\n",argc);
 printf("Here is the second: %c\n",argv[1]); 
 return 0;
}
 

