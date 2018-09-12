/*
Purpose: To demonstrate fork and two kinds of self-suspension
Output: output could vary on subsequent exections  

  I'm the child
  I'll go to sleep for five seconds

  i'm the child about to exit
  i'll call my parent before i do, however

  i'm the parent.  My child has pid = 15406
  i'm going to wait for my child to exit

  i'm the parent about to exit
*/

#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
int main(void)
{
  int value, status;
  int ch_stat;

  if ((value = fork()) < 0)
     printf("Child could not be created\n");
  else
     if (value == 0) //fork returns 0 to child process
        {
	 //sleep(1);
         printf("I'm the child\n");
         printf("I'll go to sleep for five seconds\n\n");
         sleep(5);
        }
     else 
        {
         sleep(2);
         //fork returns pid of child to parent
         printf("i'm the parent.  My child has pid = %d\n",value);
         printf("i'm going to wait for my child to exit\n\n");
         status = wait(&ch_stat);
         //if parent is stopped and waiting for a child, status is pid of child 
	 printf("The parent was waiting for : %d\n",status);
        }
   if (value == 0)
     {
       printf("i'm the child about to exit\n");
       printf("i'll try waiting for my own children\n");
       status = wait(&ch_stat);
       if (status < 0)
	   printf("i'm the child, not yet reproducing\n"); 
     }
   else
      printf("i'm the parent about to exit\n\n");
   if (value == 0)
      printf("i'm the child and I'm finished\n\n");
   else
      printf("i'm the parent and i'm finished\n");
}
