//useful c-string functions 
//requires two arguments

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
 int x = strcmp(argv[1],argv[2]);

 if (x < 0)
   printf("%s comes before %s\n", argv[1], argv[2]); 
 if (x == 0)
   printf("%s is equal to  %s\n", argv[1], argv[2]); 
 if (x > 0)
   printf("%s comes after  %s\n", argv[1], argv[2]); 

 char* str = (char*)malloc(strlen(argv[0]));
 strcpy(str, argv[0]);
 printf("%s\n",argv[0]); 
 printf("%s\n",str); 
 
 free(str);  

 return 0;
}
 

