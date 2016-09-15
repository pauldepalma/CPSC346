/*
Purpose: To demonstrate calloc,free, strcpy 
Usage: ./a.out hi
Output: hi
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* copy(char*);

int main(int argc, char* argv[])
{
 char* newStr = copy(argv[1]);
 printf("%s\n",newStr); 
 free (newStr);
 newStr = NULL; 
}

char* copy(char* strIn)
{
 char* strOut = calloc(strlen(strIn) + 1, sizeof(char));

 strcpy(strOut,strIn);
 return strOut;
}
