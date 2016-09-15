#include <stdio.h>
#include <unistd.h>

#define MAX_LINE 80

char** getInput();
void dispOutput(char**);

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
     args = getInput();
     dispOutput(args);
     //here accept input from the user 
     //set more to 0 if input == "quit"  (use strcmp)  
  }
   return 0;
}


//Reads input string from the key board.  Parses the input into argument 
//where an argument is any string of characters that either begins 
//the input or is
//separated by the previous argument by a space
//In the following example, the user has entered three arguments
//myShell> ls -l cpsc346 
char** getInput()
{
}  


//Displays the arguments entered by the user and parsed by getInput
void dispOutput(char** args)
{
}  
