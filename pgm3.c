//function, dynamic memory

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE 80

char* get_inp();

int main()
{
 char* inp = get_inp();

 printf("You entered %d characters\n",strlen(inp));
 printf("%s\n",inp);

 free(inp);  //return dynamially allocated memory to the heap
 return 0;
}

char* get_inp()
{
 char* inp = (char*)malloc(MAX_LINE); //dynamically allocate memory
 printf("Enter text <= 80 characters in length\n");
 scanf("%s",inp);
 return inp;
}

  
 

