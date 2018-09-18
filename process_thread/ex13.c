/*
Using execvp to overlay the memory space of a child    
Output: directory listing  
*/

#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define MAX_LINE 80

int main(int argc, char* argv[])
{
  pid_t pid; 

  char* args[MAX_LINE]; 

  args[0] = "/bin/ls";
  args[1] = "-l";
  args[2] = NULL;
 
  pid = fork();

  if (pid < 0)  //fork failed
  {
   fprintf(stderr, "Fork Error");
   return 1;
  } 
  else
   if (pid == 0)  //child process
     execvp(args[0],args);  //load args[0] into the child's address space 
   else           //parent process
   {
    wait(NULL);
    fprintf(stdout, "Child complete\n");
   }
  return 0;
}
