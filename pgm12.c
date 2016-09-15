/*
manipulating the file pointer, argument checking 
Purpose: To demonstrate random access file operations, argument checking 
Usage: ./a.out input_file
Output: file is displayed in reverse 
*/

#include <stdio.h>
#include <stdlib.h>

FILE *my_open(char* fname, char* mode);
void check_args(int argc);

int main(int argc, char* argv[])
{
 char ch;
 FILE *ifp;

 check_args(argc);
 
 ifp = my_open(argv[1],"r"); 

 fseek(ifp, 0, SEEK_END); //go to the end of the file
 fseek(ifp, -1, SEEK_CUR); //back up one byte 
 while(ftell(ifp) > 0)
 {
  ch = getc(ifp);
  putchar(ch);  
  fseek(ifp, -2, SEEK_CUR); //back up one byte 
 }
 ch = getc(ifp); //read the remaining character
 putchar(ch);  
 printf("\n\n");
 return 0;
}

/*
Pre: argc is an int 
Post: if argc != 2, program displays an error message and exits 
*/ 
void check_args(int argc)
{
 if (argc != 2)
 {
  printf("There must be two command line arguments\n");
  exit(1);
 } 
}

/*
Pre: fname contains a valid file name.  mode contains a valid mode 
Post: if pre-conditions are met, returns a file pointer, else displays
      an error msg and exits.
*/ 
FILE *my_open(char* fname, char* mode)
{
 FILE  *ifp;
 if ((ifp = fopen(fname, mode)) == NULL)
 {
  printf("Can't open %s\n", fname);
  exit(1);
 }
  return ifp;
}
