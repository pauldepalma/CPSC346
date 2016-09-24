//parent and child share file descriptors
//This could lead to a race condition

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

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

  return 0;
}

void rdwrt(int fdrd, int fdwt, int pid, int ct)
{
 char c;

 if (pid > 0)
   spin(ct);

 while(1)
   {
    if (pid > 0)
      printf("I'm the child\n");
    else
      printf("I'm the parent\n");
    if (read(fdrd, &c, 1) != 1)
      break;
    write(fdwt, &c, 1);
   }
}

void spin(int num)
{
 int ct = 0;
 while (ct++ < num); 
}
