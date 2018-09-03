/*
Class: CPSC 346-01 & CPSC 346-02
Team Member 1: Paul De Palma
Team Member 2: N/A 
GU Username of project lead: depalma
Pgm Name: ex10.c
Pgm Desc: practice with pointers 
Usage: ./a.out a b 
*/


#include <stdio.h>
#include <stdlib.h>

void swap(char*,char*);

int main(int argc, char* argv[])
{
 char a,b;

 a = *argv[1];
 b = *argv[2];

 printf("original\n");
 printf("%c %c\n",a,b);

 swap(&a,&b);
 printf("swapped\n");
 printf("%c %c\n",a,b);

 return 0;
}

void swap(char*a, char* b)
{
 char c;
 
 c = *a;
 *a = *b;
 *b = c;
}
