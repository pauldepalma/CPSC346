/*
Class: CPSC 346-01 & CPSC 346-02
Team Member 1: Paul De Palma
Team Member 2: N/A 
GU Username of project lead: depalma
Pgm Name: ex7.c
Pgm Desc: illustrates file operations by copying a file and transforming
          lower case characters to upper case
Usage: ./a.out input_file output_file 
*/
 

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
 FILE *ifp, *ofp;
 char c;

 ifp = fopen(argv[1],"r");
 ofp = fopen(argv[2],"w");

 //read a char, store it in a var, stop when end of file is encountered
 //notice getc instead of getchar
 while ((c = getc(ifp)) != EOF)
 {
  if (islower(c))
     c = toupper(c);
  putc(c,ofp);
 }

 fclose(ifp);
 fclose(ofp);
 return 0;
} 
