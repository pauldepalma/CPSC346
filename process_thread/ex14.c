//parent and child share file descriptors
//Uncontrolled access causes a race condition

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
//usage: ./a.out inp_file out_file wait_time

void rdwrt(int,int,int,int);
void spin(int);

int main(int argc, char* argv[])
{
  int fdrd, fdwt, pid; 

  if (argc != 4)
    {
     fprintf(stderr,"Must have three arguments\n");  
     exit(1);
    }

  if ((fdrd = open(argv[1], O_RDONLY)) == -1)
    {
     fprintf(stderr,"Error on open of input file\n");  
     exit(1);
    }

  if ((fdwt = creat(argv[2], 0666)) == -1)
    {
     fprintf(stderr,"Error on open of output file\n");  
     exit(1);
    }
    
  pid = fork();
  rdwrt(fdrd,fdwt,pid,atoi(argv[3]));
  close(fdrd);
  close(fdwt);

  return 0;
}

void rdwrt(int fdrd, int fdwt, int pid, int ct)
{
 char c, eol;

 if (pid > 0)
   spin(ct); 

  
 //access to input file depends on who gets there first
 if (pid > 0)
    printf("I'm the child about to read\n");
 else
    printf("I'm the parent about to read \n");
 if (read(fdrd, &c, 1) != 1)
    printf("error reading\n");
 else
    {
     read(fdrd, &eol,1);
     printf("successful read by %d\n",pid);
    }
 if (pid > 0)
    printf("I'm the child about to write \n");
 else
    printf("I'm the parent about to write\n");
 write(fdwt, &c, 1);
 if (pid > 0)
    printf("I'm the child about to exit\n");
 else
    printf("I'm the parent about to exit\n");
}

void spin(int ct)
{
 int i = 0;
 while(i++ < ct);
}
