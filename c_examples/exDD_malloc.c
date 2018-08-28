/*
Class: CPSC 346-01 & CPSC 346-02
Team Member 1: Paul De Palma
Team Member 2: N/A 
GU Username of project lead: depalma
Pgm Name: exDD_malloc.c
Pgm Desc: function call, dynamic allocation of an array of character arrays 
Usage: ./a.out 
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE 80
#define MAX 5 

char** get_inp();

int main()
{
 char** inp = get_inp();

 int i = 0;
 while (i < MAX)
 {
  printf("%s\n",inp[i]);
  i++;
 } 


 return 0;
}

char** get_inp()
{
 char** array = (char**)calloc(5,sizeof(char**)); 
 int i;
 for (i = 0; i < MAX; i++)
 {
  array[i] = (char*)malloc(MAX_LINE); //dynamically allocate memory
  printf("Enter text <= 80 characters in length\n");
  scanf("%[^\n]s",array[i]); //while the input is not null terminator, read
  getchar();
 } 
 return array;
}

  
 

