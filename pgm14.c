/*
Using execlp to overlay the memory space of a child    
Output: directory listing  
*/

#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
int main()
{
  pid_t pid; 

  pid = fork();

  if (pid < 0)  //fork failed
  {
   fprintf(stderr, "Fork Error");
   return 1;
  } 
  else
   if (pid == 0)  //child process
    execlp("/bin/ls", "ls", NULL); 
   else           //parent process
   {
    wait(NULL);
    fprintf(stdout, "Child complete");
   }
  return 0;
}
