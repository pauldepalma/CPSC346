/*
File operations
Purpose: Demonstrate file operations by copying a file and transforming
  lower case characters to upper case.
Usage: ./a.out input_file output_file
Output: output_file is identical to input_file, except lowercase characters
  have been transformed to uppercase. 
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
