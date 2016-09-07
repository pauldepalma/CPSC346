//command line arguments
//This is essentially what you will be building in the first assignment

#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{
 int i = 0;
 while(i < argc)
  {
   //the 0th arg is the name of the executable
   //each arg is c-string
   printf("Argument %d is %d characters long\n",i,strlen(argv[i]));
   printf("%s\n",argv[i]);
   ++i;
  } 
 
 return 0;
}
 

