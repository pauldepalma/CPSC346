#include <stdio.h>
#include <unistd.h>

#define MAX_LINE 80

int main()
{
  //A pointer to an array of pointers to char.  In essence, an array of 
  //arrays.  Each of the second level arrays is a c-string. These hold
  //the command line arguments entered by the user.
  char **args;  

  int more = 1;
  while (more)
  {
     printf("myShell> ");
     fflush(stdout);
     args = getInput(args);
     //if arg[0] holds 'quit', set more to 0, else invoke dispInput()
  }
   return 0;
}


//Reads input string from the key board.  Parses the input into arguments
//where an is any string of characters that either begin the input or is
//separated by the previous argument by a space
//In the following example, the user has entered three arguments
//myShell> ls -l cpsc346 
//and optons  
char* args getInput()
{
}  


//Displays the arguments entered by the user and parsed by getInput
void dispInput(char*[])
{
}  
