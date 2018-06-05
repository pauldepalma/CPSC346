/*
Class: CPSC 346-01 & CPSC 346-02
Team Member 1: Paul De Palma
Team Member 2: N/A 
GU Username of project lead: depalma
Pgm Name: exB_scanf.c
Pgm Desc: Reads and displays a string
Usage: ./a.out 
*/


#include <stdio.h>
#include <string.h>

int main()
{
 char stuff[80];

 printf("Enter your email address\n");
 scanf("%s",stuff);

 //lu is unsigned long, the return type of strlen
 printf("Your email address is %lu characters long\n",strlen(stuff));
 printf("%s\n",stuff);
 return 0;
}
 

