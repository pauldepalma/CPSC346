/*
Class: CPSC 346-01 & CPSC 346-02
Team Member 1: Paul De Palma
Team Member 2: N/A 
GU Username of project lead: depalma
Pgm Name: ex10.c
Pgm Desc: practice with pointers and c-strings
Usage: ./a.out hello there 
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap(char*,char*);

int main(int argc, char* argv[])
{
 char* a = argv[1];
 char* b = argv[2];

 printf("original\n");
 printf("%s %s\n",a,b);

 swap(argv[1],argv[2]);
 printf("swapped\n");
 printf("%s %s\n",a,b);

 return 0;
}

void swap(char* a, char* b)
{
 char* c = (char*) malloc(strlen(a) + 1);

 //how would you write strcpy? 
 strcpy(c, a); 
 strcpy(a,b); 
 strcpy(b,c); 

 free(c);
}
