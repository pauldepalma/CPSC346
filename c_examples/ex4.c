/*
Class: CPSC 346-01 & CPSC 346-02
Team Member 1: Paul De Palma
Team Member 2: N/A 
GU Username of project lead: depalma
Pgm Name: ex4.c
Pgm Desc: function call, dynamic allocation of character array with malloc
Usage: ./a.out 
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE 80

char* get_inp();

int main()
{
 char* inp = get_inp();

 printf("You entered %lu characters\n",strlen(inp));
 printf("%s\n",inp);

 free(inp);  //return dynamially allocated memory to the heap
 return 0;
}

char* get_inp()
{
 //dynamically allocate MAX_LINE bytes to be used as a 
 //character array to store a c-string
 char* inp = (char*)malloc(MAX_LINE); //dynamically allocate memory
 printf("Enter text <= 80 characters in length\n");
 scanf("%[^\n]s",inp); //while the input is not null terminator, read
 return inp;
}

  
 

