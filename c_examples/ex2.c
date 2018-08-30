/*
Class: CPSC 346-01 & CPSC 346-02
Team Member 1: Paul De Palma
Team Member 2: N/A 
GU Username of project lead: depalma
Pgm Name: ex2.c
Pgm Desc: Reads and displays a string
Usage: ./a.out 
*/


#include <stdio.h>
#include <string.h>

void disp_input(char*);

int main()
{
 char stuff[80];

 printf("Enter a string < 80 characters long\n");
 scanf("%s",stuff);

 //lu is unsigned long, the return type of strlen
 printf("Your string is %lu characters long\n",strlen(stuff));
 printf("Here it is: %s\n",stuff);
 disp_input(stuff);
 return 0;
}

void disp_input(char* stuff)
{
 printf("Here it is in reverse\n");
 int i;
 for (i = strlen(stuff) - 1; i >= 0; i--) 
   printf("%c\n", stuff[i]);
}
 

