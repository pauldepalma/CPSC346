/*
Class: CPSC 346-01 & CPSC 346-02
Team Member 1: Paul De Palma
Team Member 2: N/A 
GU Username of project lead: depalma
Pgm Name: exC_calloc.c
Pgm Desc: function call, dynamic allocation of an array with calloc 
Usage: ./a.out 
*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 5 

int* get_inp();

int main()
{
 int* inp = get_inp();

 int i;
 for(i = 0; i < MAX; i++)
 {
  printf("%d",inp[i]);
  printf("%c",'\n');
 }

 free(inp);  //return dynamially allocated memory to the heap
 return 0;
}

int* get_inp()
{
 //allocate a block of ints of size MAX
 int* inp = (int*) calloc(MAX,sizeof(int));

 int i = 0;
 int int_in;
 while(i < MAX)
 {
  printf("Enter an integer\n");
  scanf("%d",&int_in); 
  inp[i++] = int_in;
 }
 return inp;
}

  
 

